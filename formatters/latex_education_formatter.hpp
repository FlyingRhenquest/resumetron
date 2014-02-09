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
 * Latex markup formatter for education
 */

#ifndef _HPP_LATEX_EDUCATION_FORMATTER
#define _HPP_LATEX_EDUCATION_FORMATTER

#include "education_formatter.hpp"

namespace fr {

  namespace resumetron {

    class latex_education_formatter : public education_formatter {

    public:

      typedef std::shared_ptr<latex_education_formatter> pointer;

      latex_education_formatter(resume::pointer my_resume) : education_formatter(my_resume)
      {
      }

      virtual ~latex_education_formatter()
      {
      }

      std::string section_header() const override
      {
	std::string retval("\\section*{Education:}\n");
	return retval;
      }

      std::string my_text() const override
      {
	std::stringstream output_stream;
	education::vector all_education = my_resume->get_education();
	std::sort(all_education.begin(), all_education.end(), [](education::pointer left, education::pointer right) { return left->get_start_time() > right->get_start_time(); });
	output_stream << "\\begin{itemize}" << std::endl;
	for (education::pointer school : all_education) {
	  output_stream << "\\item ";
	  output_stream << time_to_string(school->get_start_time()) << " to " << time_to_string(school->get_end_time()) << ": " << school->get_institution() << " Major: " << school->get_major();
	  if (!school->get_degree().empty()) {
	    output_stream << " Degree: " << school->get_degree();
	  }
	  if (!school->get_gpa().empty()) {
	    output_stream << " GPA: " << school->get_gpa() << std::endl;
	  }
	  output_stream << std::endl;
	}
	output_stream << "\\end{itemize}" << std::endl;
	return output_stream.str();
      }

    };

  }

}

#endif
