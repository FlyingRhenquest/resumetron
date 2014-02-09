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
 * Pulls everything together into an object
 */

#ifndef _HPP_RESUME
#define _HPP_RESUME

#include "address.hpp"
#include "education.hpp"
#include <memory>
#include "position.hpp"
#include <string>

namespace fr {

  namespace resumetron {

    class resume {
      std::string name; // candidate name
      address current_address;
      education::vector education_list;
      position::vector positions;

    public:
      typedef std::shared_ptr<resume> pointer;
      
      resume(std::string name, const address current_address) : name(name), current_address(current_address)
      {
      }

      resume()
      {
      }

      ~resume()
      {
      }

      void add(education::pointer item)
      {
	education_list.push_back(item);
      }

      void add(position::pointer item)
      {
	positions.push_back(item);
      }

      std::string get_name() const
      {
	return name;
      }

      address get_address() const
      {
	return current_address;
      }

      education::vector get_education() const
      {
	return education_list;
      }

      position::vector get_positions() const
      {
	return positions;
      }
      
    };

  }

}

#endif
