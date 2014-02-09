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
 * Formats positions out. This one does plain text.
 */

#ifndef _HPP_POSITION_FORMATTER
#define _HPP_POSITION_FORMATTER

#include <algorithm>
#include "formatter_interface.hpp"
#include <iomanip>
#include <map>
#include <memory>
#include "position.hpp"
#include "resume.hpp"
#include <stdexcept>
#include <string>
#include "string_converts.hpp"
#include <sys/time.h>
#include <sstream>
#include <vector>

namespace fr {

  namespace resumetron {

    class position_formatter : public formatter_interface {

    public:

      typedef std::shared_ptr<position_formatter> pointer;

    protected:

      resume::pointer my_resume;

    public:

      position_formatter(resume::pointer my_resume) : my_resume(my_resume)
      {
      }

      virtual ~position_formatter()
      {
      }

      std::string section_header() const override
      {
	std::string retval("Work Experience:\n");
	return retval;
      }

      std::string section_footer() const override
      {
	std::string retval("\n");
	return retval;
      }

      // This one's just doing a summary

      std::string my_text() const override
      {
	std::stringstream output_stream;
	position::vector all_positions = my_resume->get_positions();
	timeval tv;
	gettimeofday(&tv, nullptr);

	// Since this is by-copy I can sort it without violating constness
	std::sort(all_positions.begin(), all_positions.end(), [](position::pointer left, position::pointer right) { return left->get_start_date() > right->get_start_date(); });
	for (position::pointer one_position : all_positions) {
	  output_stream << time_to_string(one_position->get_start_date()) << " to ";	  
	  if (one_position->get_end_date() > tv.tv_sec) {
	    output_stream << " Present";
	  } else {
	    output_stream << time_to_string(one_position->get_end_date());
	  }
	  output_stream << " " << one_position->get_company() << ", " << one_position->get_location() << " - " << one_position->get_title() << std::endl;
	}
	return output_stream.str();
      }

    };

  }

}

#endif
