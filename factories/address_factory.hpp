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
 * Returns address objets given an XML node.
 */

#ifndef _HPP_ADDRESS_FACTORY
#define _HPP_ADDRESS_FACTORY

#include "address.hpp"
#include <boost/signals2.hpp>
#include <string>
#include <stdexcept>
#include "xml_node.hpp"
#include "xml_node_factory.hpp"

namespace fr {

  namespace resumetron {

    class address_factory : public xml_node_factory {
      cppxml::xml_node::pointer doc;

      const std::string Address = "address";
      const std::string Street1 = "street1";
      const std::string Street2 = "street2";
      const std::string City = "city";
      const std::string State = "state";
      const std::string Zip = "zip";
      const std::string Phone = "phone";
      const std::string Email = "email";

    public:
      // Signals availability of an address.
      boost::signals2::signal<void(const address &)> available;
      
      // I could make a constructor that takes a filename and builds
      // a cppxml node_engine, too, but I only ever plan to construct
      // this from resume_factory right now, so I can just pass
      // the doc it gets from there.

      // Takes xml_node resume document 

      address_factory(cppxml::xml_node::pointer doc) : doc(doc)
      {
      }

      ~address_factory()
      {
      }

      // Run builds the object(s) and calls the available signal when
      // they're built. Factory allows more than one but it will probably
      // confuse the emitters.

      void run()
      {
	cppxml::child_vector addresses = doc->find_children(Address);
	bool not_mandatory = false;
	for (cppxml::xml_node::pointer address : addresses) {
	  std::string street1, street2, city, state, zip, phone, email;
	  street1 = get_node_text(address, Street1);
	  street2 = get_node_text(address, Street2, not_mandatory);
	  city = get_node_text(address, City);
	  state = get_node_text(address, State);
	  zip = get_node_text(address, Zip);
	  phone = get_node_text(address, Phone, not_mandatory);
	  email = get_node_text(address, Email, not_mandatory);
	  fr::resumetron::address retval(street1, city, state, zip, phone, email, street2);
	  available(retval);
	}
      }

    };

  }

}

#endif
