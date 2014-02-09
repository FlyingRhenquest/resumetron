/**
 * Copyright 2014 Bruce Ide
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * The skill formatter's a little more complex than the others since it
 * has to iterate skills and accumulate total time with each skill.
 * This will happen no matter what kind of text we're outputting.
 */

#ifndef _HPP_SKILL_FORMATTER
#define _HPP_SKILL_FORMATTER

#include <algorithm>
#include "formatter_interface.hpp"
#include <iomanip>
#include <map>
#include <memory>
#include "position.hpp"
#include "resume.hpp"
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

namespace fr {

  namespace resumetron {

    class skill_formatter : public formatter_interface {
    public:
      typedef std::shared_ptr<skill_formatter> pointer;

    protected:
      typedef std::pair<std::string, long> skill_pair;
      typedef std::vector<skill_pair> skill_vector;
      typedef std::map<std::string, long> skill_map;

      resume::pointer my_resume;

      skill_vector accumulate_skills(const position::vector &positions) const
      {
	skill_map skills;
	// build skill map
	for (position::pointer pos : positions) {
	  for (std::string skill : pos->get_skills()) {
	    try {
	      // This will throw a std::out_of_range if it doesn't exist
	      long duration = skills.at(skill);
	      duration += pos->get_duration();
	      skills[skill] = duration;
	    } catch (std::out_of_range &e) {
	      skills[skill] = pos->get_duration();
	    }
	  }
	}
	skill_vector retval;
	// Flatten to vector for sorted output (by total skill duration)
	for (skill_map::iterator it = skills.begin(); it != skills.end(); ++it) {
	  retval.push_back(*it);
	}
	std::sort(retval.begin(), retval.end(), [](skill_pair left, skill_pair right) { return left.second > right.second; });
	return retval;
      }      

    public:

      skill_formatter(resume::pointer my_resume) : my_resume(my_resume)
      {
      }

      virtual ~skill_formatter()
      {
      }

      // This object will do plain text
      std::string section_header() const override
      {
	std::string retval("Skills:\n");
	return retval;
      }

      std::string section_footer() const override
      {
	std::string retval("\n");
	return retval;
      }

      std::string my_text() const override
      {
	std::stringstream skill_stream;	
	skill_stream << std::fixed;
	skill_vector all_skills = accumulate_skills(my_resume->get_positions());
	for (skill_pair skill : all_skills) {
	  double years = ((double) skill.second) / (60.0 * 60.0 * 24.0 * 365.25);
	  skill_stream << skill.first << ": " << std::setprecision(2) << years << " years" << std::endl;
	}
	return skill_stream.str();
      }      

    };

  }

}

#endif
