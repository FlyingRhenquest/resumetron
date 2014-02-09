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
 * Constructs education objects from an XML doc.
 */

#ifndef _HPP_EDUCATION_FACTORY
#define _HPP_EDUCATION_FACTORY

#include "education.hpp"
#include <boost/signals2.hpp>
#include <stdexcept>
#include <string>
#include "string_converts.hpp"
#include <sys/time.h>
#include "xml_node.hpp"
#include "xml_node_factory.hpp"

namespace fr {

  namespace resumetron {

    class education_factory : public xml_node_factory {

      cppxml::xml_node::pointer doc;
      
      const std::string Degree = "degree";
      const std::string Education = "education";
      const std::string End = "end";
      const std::string Gpa = "gpa";
      const std::string Institution = "institution";
      const std::string Major = "major";
      const std::string Name = "name";
      const std::string Start = "start";
      
    public:

      // Signals the availability of an education object
      boost::signals2::signal<void(const education &)> available;
      
      education_factory(cppxml::xml_node::pointer doc) : doc(doc)
      {
      }

      ~education_factory()
      {
      }

      // Run builds the object(s) and calls available when they're
      // built.

      void run()
      {
	cppxml::child_vector schools = doc->find_children(Institution);
	bool not_mandatory = false;
	for (cppxml::xml_node::pointer school : schools) {
	  std::shared_ptr<std::string> name = school->find_attribute(Name);
	  if (nullptr == name.get()) {
	    std::string err("An institution in this document does not have a name attribute, and they are required");
	    throw std::logic_error(err);
	  }
	  std::string major = get_node_text(school, Major);
	  std::string degree = get_node_text(school, Degree);
	  std::string gpa = get_node_text(school, Gpa, not_mandatory);
	  timeval start = fr::time::string_to<timeval>()(adj_time_string(get_node_text(school, Start)));
	  timeval end = fr::time::string_to<timeval>()(adj_time_string(get_node_text(school, End)));
	  education edu(*name, major, degree, gpa, start.tv_sec, end.tv_sec);
	  available(edu);
	}
	
      }

    };

  }

}

#endif
