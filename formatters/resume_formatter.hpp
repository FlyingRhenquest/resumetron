/**
 * Resume formatter takes all the other formatters and ties them together
 * to format an entire resume.
 */

#ifndef _HPP_RESUME_FORMATTER
#define _HPP_RESUME_FORMATTER

#include "address_formatter.hpp"
#include "formatter_interface.hpp"
#include <memory>
#include "resume.hpp"
#include <stdexcept>
#include <string>
#include <sstream>

namespace fr {

  namespace resumetron {

    /**
     * In order for addresses to format correctly (At least in plain
     * text) I'll need to treat the address formatter specially,
     * and take them separately. The other formatters I can just
     * add via the formatter interface add method, but I plan to
     * just iterate through them. The resume formatter on its own
     * really won't do that much other than print the address and 
     * the master document title ("Resume"). I'll probably end up
     * constructing the formatter with another factory.
     */

    class resume_formatter : public formatter_interface {

    public:
      typedef std::shared_ptr<resume_formatter> pointer;

    protected:

      resume::pointer my_resume;
      formatter_interface::pointer format_address;

    public:
      
      resume_formatter(resume::pointer my_resume, formatter_interface::pointer format_address = address_formatter::pointer()) : my_resume(my_resume), format_address(format_address)
      {
	if (nullptr == format_address.get()) {
	  this->format_address = std::make_shared<address_formatter>(my_resume);
	}
      }
      
      resume_formatter(const resume_formatter &rf) = delete;

      virtual ~resume_formatter()
      {
      }

      // This should really be all there is to it. Format_text should
      // build the rest of it from the other formatters, which
      // should have been added to this one.

      std::string my_text() const override
      {
	std::stringstream output_stream;
	// Output address first
	if (format_address.get() != nullptr) {
	  output_stream << format_address->my_text();
	}
	output_stream << std::endl << "Resume: " << my_resume->get_name() << std::endl;
	return output_stream.str();
      }

    };

  }
}

#endif
