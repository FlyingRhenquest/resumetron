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
 * Education object for resume builder
 */

#ifndef _HPP_EDUCATION
#define _HPP_EDUCATION

#include <memory>
#include <string>
#include <vector>
#include <ctime>

namespace fr {

  namespace resumetron {

    class education {
      std::string institution;
      std::string maj;
      std::string degree;
      // These usually seem to want to be more freeform than a straight
      // number would allow
      std::string gpa;

      std::time_t start_time;
      std::time_t end_time;
      
    public:
      typedef std::shared_ptr<education> pointer;
      typedef std::vector<pointer> vector;

      education(const std::string &institution, const std::string &maj, const std::string &degree, const std::string gpa, std::time_t start_time = 0l, std::time_t end_time = 0l) : institution(institution), maj(maj), degree(degree), gpa(gpa), start_time(start_time), end_time(end_time)
      {
      }

      std::string get_institution() const
      {
	return institution;
      }

      std::string get_major() const
      {
	return maj;
      }

      std::string get_degree() const
      {
	return degree;
      }

      std::string get_gpa() const
      {
	return gpa;
      }
      
      time_t get_start_time() const
      {
	return start_time;
      }

      time_t get_end_time() const
      {
	return end_time;
      }

    };

  }

}

#endif
