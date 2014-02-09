/**
 * Format education (plain text version)
 */

#ifndef _HPP_EDUCATION_FORMATTER
#define _HPP_EDUCATION_FORMATTER

#include <algorithm>
#include "education.hpp"
#include "formatter_interface.hpp"
#include <iomanip>
#include <memory>
#include "resume.hpp"
#include <stdexcept>
#include <sstream>
#include <vector>

namespace fr {

  namespace resumetron {

    class education_formatter : public formatter_interface {

    public:
      typedef std::shared_ptr<education_formatter> pointer;

    protected:
      resume::pointer my_resume;

    public:

      education_formatter(resume::pointer my_resume) : my_resume(my_resume)
      {
      }

      virtual ~education_formatter()
      {
      }

      std::string section_header() const override
      {
	std::string retval("Education:\n");
	return retval;
      }

      std::string section_footer() const override
      {
	std::string retval("\n");
	return retval;
      }

      std::string my_text() const override
      {
	std::stringstream output_stream;
	education::vector all_education = my_resume->get_education();
	std::sort(all_education.begin(), all_education.end(), [](education::pointer left, education::pointer right) { return left->get_start_time() > right->get_start_time(); });
	for (education::pointer one_school : all_education) {
	  output_stream << time_to_string(one_school->get_start_time()) << " to " << time_to_string(one_school->get_end_time()) << ": " << one_school->get_institution() << " Major: " << one_school->get_major() << " Degree: " << one_school->get_degree() << " GPA: " << one_school->get_gpa() << std::endl;
	}
	return output_stream.str();
      }

    };

  }

}

#endif
