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
 * Uses cppxml to build a resume. See the test/sample_resume.xml for
 * format.
 */

#ifndef _HPP_RESUME_FACTORY
#define _HPP_RESUME_FACTORY

#include "address_factory.hpp"
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include "education_factory.hpp"
#include "node_engine.hpp"
#include "position_factory.hpp"
#include "resume.hpp"
#include <string>
#include "xml_node.hpp"
#include "xml_node_factory.hpp"

namespace fr {

  namespace resumetron {

    class resume_factory : public xml_node_factory {
      std::string resume_file;
      // I could do SAX style processing on this but DOM-style
      // is a little easier. So I'll just get the doc out and
      // find the bits I need.
      cppxml::xml_node::pointer doc;
      
      void populate_address(const address &addr, address *to_populate)
      {
	*to_populate = addr;
      }

      void add_education(resume *res, const education &e)
      {
	res->add(std::make_shared<education>(e));
      }

      void add_position(resume *res, const position &p)
      {
	res->add(std::make_shared<position>(p));
      }

      const std::string Candidate = "candidate";

    public:

      // There should only be one per XML file.
      boost::signals2::signal<void(const resume &)> available;

      resume_factory(const std::string &resume_file) : resume_file(resume_file)
      {
	cppxml::node_engine doc_factory(resume_file);
	doc = doc_factory.get_document();
      }

      ~resume_factory()
      {	
      }

      void run()
      {
	address addr;
	std::string name = get_node_text(doc, Candidate);
	address_factory af(doc);
	af.available.connect(boost::bind(&resume_factory::populate_address, this, _1, &addr));
	af.run();
	resume retval(name, addr);
	education_factory ef(doc);
	position_factory pf(doc);

	ef.available.connect(boost::bind(&resume_factory::add_education, this, &retval, _1));
	pf.available.connect(boost::bind(&resume_factory::add_position, this, &retval, _1));
	ef.run();
	pf.run();
	available(retval);
      }
      
    };
    
  }

}

#endif
