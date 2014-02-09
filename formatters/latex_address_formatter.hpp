/**
 * Formats address for LaTeX. This puts the address at the top, left-hand
 * side of the first page.
 */

#ifndef _HPP_LATEX_ADDRESS_FORMATTER
#define _HPP_LATEX_ADDRESS_FORMATTER

#include "address_formatter.hpp"

namespace fr {

  namespace resumetron {

    class latex_address_formatter : public address_formatter {

    public:
      typedef std::shared_ptr<latex_address_formatter> pointer;

      latex_address_formatter(resume::pointer my_resume) : address_formatter(my_resume)
      {
      }

      virtual ~latex_address_formatter()
      {
      }

      std::string my_text() const override
      {
	std::stringstream output_stream;
	address current_address = my_resume->get_address();
	output_stream << my_resume->get_name() << "\\par" << std::endl;
	output_stream << current_address.get_street1() << "\\par" << std::endl;
	if (!current_address.get_street2().empty()) {
	  output_stream << current_address.get_street2() << "\\par" << std::endl;	  
	}
	output_stream << current_address.get_city() << ", " << current_address.get_state() << " " << current_address.get_zip() << "\\par" << std::endl;
	if (!current_address.get_phone().empty()) {
	  output_stream << current_address.get_phone() << "\\par" << std::endl;
	}
	if (!current_address.get_email().empty()) {
	  output_stream << current_address.get_email() << "\\par" << std::endl;
	}
	return output_stream.str();
      }

    };

  }

}

#endif
