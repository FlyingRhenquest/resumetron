/**
 * Returns a formatter for a plain text resume.
 */

#ifndef _HPP_TEXT_FORMATTER_FACTORY
#define _HPP_TEXT_FORMATTER_FACTORY

#include "formatter_factory_interface.hpp"
#include "address_formatter.hpp"
#include "education_formatter.hpp"
#include "position_formatter.hpp"
#include "resume.hpp"
#include "resume_formatter.hpp"
#include "skill_formatter.hpp"

namespace fr {

  namespace resumetron {

    class text_formatter_factory : public formatter_factory_interface {

      resume::pointer res;

    public:

      text_formatter_factory(resume::pointer res) : res(res)
      {	
      }

      virtual ~text_formatter_factory()
      {
      }

      formatter_interface::pointer get_formatter() override
      {
	resume_formatter::pointer res_frmt = std::make_shared<resume_formatter>(res);
	// Now you have some choice about how you want your sections
	// to fall out. If you want them to be arranged differently,
	// you'll need to rearrange these formatters to your liking.
	// They'll be listed on the resume in the order they're added.
	res_frmt->add(std::make_shared<skill_formatter>(res));
	res_frmt->add(std::make_shared<position_formatter>(res));
	res_frmt->add(std::make_shared<education_formatter>(res));
	return res_frmt;
      }

    };

  }

}

#endif
