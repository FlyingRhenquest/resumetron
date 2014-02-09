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
 * Interface all formatters should support
 */

#ifndef _HPP_FORMATTER_INTERFACE
#define _HPP_FORMATTER_INTERFACE

#include <ctime>
#include <memory>
#include <string>
#include "string_converts.hpp"
#include <sys/time.h>
#include <vector>

namespace fr {

  namespace resumetron {    

    class formatter_interface {      
    public:
      typedef std::shared_ptr<formatter_interface> pointer;

    protected:

      typedef std::vector<pointer> vector;
      vector child_formatters;

      // I'll be using this enough to put it in the base class
      std::string time_to_string(std::time_t at_time, std::string fmt="%b %Y") const
      {
	struct timeval t;
	t.tv_sec = at_time;
	t.tv_usec = 0;
	std::string retval = fr::time::to_string<timeval>()(t, fmt);
	return retval;
      }

    public:

      formatter_interface()
      {
      }

      virtual ~formatter_interface()
      {
      }

      // Add a child formatter which will be called while
      // formatting text
      void add(pointer child_formatter)
      {
	child_formatters.push_back(child_formatter);
      }

      // Note that you don't actually need to use all this stuff
      // I'm setting up if you want to do something differently;
      // just override format_text and write your own code.
      // Otherwise you may be able to get away with just overriding
      // the section header, maybe the footer and my_text
      // and format_text should do the right thing.

      // I could make this pure-virtual and force the programmer
      // to override it, but it's not really mandatory to use in
      // your format-text call, so it'll just return empty text
      // in this class
      virtual std::string section_header() const
      {
	return std::string("");
      }
      
      virtual std::string section_footer() const
      {
	return std::string("");
      }

      // Text this formatter is responsible for.
      virtual std::string my_text() const
      {
	return std::string("");
      }

      // Returns the formatted text this formatter should be
      // in charge of (including its child formatters.)
      virtual std::string format_text() const
      {
	// Start with the section header
	std::string retval(section_header());
	retval.append(my_text());
	for (pointer child : child_formatters) {
	  retval.append(child->format_text());
	}
	retval.append(section_footer());
	return retval;
      }

    };

  }
}

#endif
