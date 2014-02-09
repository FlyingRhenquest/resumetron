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
 * Contains functiosn common to the factories in this directory.
 */

#ifndef _HPP_XML_NODE_FACTORY
#define _HPP_XML_NODE_FACTORY

#include "adj_time.hpp"
#include <string>
#include <string_converts.hpp>
#include <vector>
#include "xml_node.hpp"

namespace fr {

  namespace resumetron {

    class xml_node_factory : public adj_time {

    protected:

      // Get text from the node, or throws an error that it doesn't exist and
      // is mandatory
      
      std::string get_node_text(cppxml::xml_node::pointer to_search, const std::string &node_name, bool mandatory = true )
      {
        cppxml::xml_node::pointer retptr = to_search->find_child(node_name);
        std::string retval;
        if (nullptr == retptr.get() && mandatory) {
          std::string err("Node ");
          err.append(node_name);
          err.append(" not found as a child of this XML node.");
          throw std::logic_error(err);
        } else if (nullptr != retptr.get()) {
          retval = retptr->get_text();
        }
        return retval;
      }

    public:

      xml_node_factory()
      {
      }

      virtual ~xml_node_factory()
      {
      }

    };

  }

}

#endif
