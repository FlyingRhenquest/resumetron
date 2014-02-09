/**
 * An interface for formatter factories. Formatter factories return
 * a resume_formatter with the appropriate children formatters for a
 * specific format.
 */

#ifndef _HPP_FORMATTER_FACTORY_INTERFACE
#define _HPP_FORMATTER_FACTORY_INTERFACE

#include "formatter_interface.hpp"
#include <memory>

namespace fr {

  namespace resumetron {

    class formatter_factory_interface {

    public:

      typedef std::shared_ptr<formatter_factory_interface> pointer;

      formatter_factory_interface()
      {
      }

      virtual ~formatter_factory_interface()
      {
      }

      // Should build a resume_formatter with the children of that format
      // style.
      virtual formatter_interface::pointer get_formatter() = 0;

    };

  }

}

#endif
