/**
 *
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
 * A position for my resume object. This contains title, the location
 * of the position (Which can be city, state or whatever,) company the
 * position was with, start and end dates, a list of skills, a list of
 * responsibilities and a list of achievements.
 *
 * Start and End Dates should be in the format MMM YYYY (IE: Jan 2013)
 * which my code will convert to a POSIX time. It will use Midnight
 * of the first day of the month as the start and end times.
 *
 * Try to keep your skill names consistent, so I can accumulate
 * total time spent with a skill by using string compares.
 */

#ifndef _HPP_POSITION
#define _HPP_POSITION

#include <ctime>
#include <memory>
#include <string>
#include <sys/time.h>
#include <vector>

namespace fr {

  namespace resumetron {

    class position {
    public:
      typedef std::shared_ptr<position> pointer;
      typedef std::vector<pointer> vector;

      typedef std::vector<std::string> attribute_list;
    private:
      std::string title;
      std::string location;
      std::string company;
      std::time_t start_date;
      std::time_t end_date;
      std::string description;
      attribute_list skills;
      attribute_list responsibilities;
      attribute_list achievements;

    public:
      position(const std::string &title, const std::string &location, const std::string &company, std::time_t start_date, std::time_t end_date, const std::string &description) : title(title), location(location), company(company), start_date(start_date), end_date(end_date), description(description)
      {
      }

      const std::string get_title() const
      {
	return title;
      }

      const std::string get_location() const
      {
	return location;
      }

      const std::string get_company() const
      {
	return company;
      }

      const std::time_t get_start_date() const
      {
	return start_date;
      }

      // Setting end-date in the future from now should cause "current"
      // to be printed in position formatters
      const std::time_t get_end_date() const
      {
	return end_date;
      }

      // If end_date is greater than now, end_date is set to now for
      // duration calculation
      const std::time_t get_duration() const
      {
	timeval tv;
	gettimeofday(&tv, nullptr);
	time_t effective_end_date = end_date;
	if (effective_end_date > tv.tv_sec) {
	  effective_end_date = tv.tv_sec;
	}
	return effective_end_date - start_date;
      }

      const std::string get_description() const
      {
	return description;
      }

      void add_skill(const std::string &skill)
      {
	skills.push_back(skill);
      }

      void add_responsibility(const std::string &responsibility)
      {
	responsibilities.push_back(responsibility);
      }

      void add_achievement(const std::string &achievement)
      {
	achievements.push_back(achievement);
      }

      const attribute_list &get_skills() const
      {
	return skills;
      }

      const attribute_list &get_responsibilities() const
      {
	return responsibilities;
      }

      const attribute_list &get_achievements() const
      {
	return achievements;
      }

    };

  }

}

#endif
