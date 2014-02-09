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
 * Address object for resume builder.
 */

#ifndef _HPP_ADDRESS
#define _HPP_ADDRESS

#include <memory>
#include <string>

namespace fr {

  namespace resumetron {

    class address {

      // US Style Address, since I've never really been
      // exposed to anything else. If I get a lot of
      // interest in the project from outside the US,
      // I can always make different classes of them
      // and expand these bits.

      std::string street1;
      std::string city;
      std::string state;
      std::string zip;

      // I also like to include these
      std::string phone;
      std::string email;

      // I don't have a street2 but I guess enough people do that
      // I see it on most web sites when I need to enter my
      // address, so I'll make one.
      std::string street2;

    public:

      typedef std::shared_ptr<address> pointer;

      // Put street2 last so I can make it default to empty string
      address(const std::string &street1, const std::string &city, const std::string &state, const std::string &zip, const std::string &phone = "", const std::string email = "", const std::string street2 = "") : street1(street1), city(city), state(state), zip(zip), phone(phone), email(email), street2(street2)
      {
      }

      // Running the default initializer on all the strings is fine
      address()
      {
      }

      // Once you construct the object you can't change it anymore.
      // If you need a different address, make a new object.

      const std::string get_street1() const
      {
	return street1;
      }

      const std::string get_street2() const
      {
	return street2;
      }

      const std::string get_city() const
      {
	return city;
      }

      const std::string get_state() const
      {
	return state;
      }

      const std::string get_zip() const
      {
	return zip;
      }

      const std::string get_phone() const
      {
	return phone;
      }

      const std::string get_email() const
      {
	return email;
      }

    };

  }

}

#endif
