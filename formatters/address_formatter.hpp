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
 * Formats address. For plain text version this will be right justified.
 */

#ifndef _HPP_ADDRESS_FORMATTER
#define _HPP_ADDRESS_FORMATTER

#include "address.hpp"
#include "formatter_interface.hpp"
#include <iomanip>
#include <memory>
#include "resume.hpp"
#include <stdexcept>
#include <string>
#include <sstream>

namespace fr {

  namespace resumetron {

    class address_formatter : public formatter_interface {
    public:

      typedef std::shared_ptr<address_formatter> pointer;

    protected:

      resume::pointer my_resume;

    public:

      address_formatter(resume::pointer my_resume) : my_resume(my_resume) 
      {
      }

      virtual ~address_formatter()
      {
      }

      std::string section_header() const override
      {
	std::string retval("");
	return retval;
      }

      std::string section_footer() const override
      {
	std::string retval("");
	return retval;
      }

      std::string my_text() const override
      {
	std::stringstream output_stream;
	address current_address = my_resume->get_address();
	output_stream << my_resume->get_name() << std::endl << current_address.get_street1() << std::endl;
	if (!current_address.get_street2().empty()) {
	  output_stream << current_address.get_street2() << std::endl;
	}
	output_stream << current_address.get_city() << ", " << current_address.get_state() << " " << current_address.get_zip() << std::endl;
	if (!current_address.get_phone().empty()) {
	  output_stream << "Phone: " << current_address.get_phone() << std::endl;
	}
	if (!current_address.get_email().empty()) {
	  output_stream << "Email: " << current_address.get_email() << std::endl;
	}
	return output_stream.str();
      }


    };

  }

}

#endif
