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
 * Latex resume formatter takes the other formatters and ties them
 * together into a latex-formatted resume
 */

#ifndef _HPP_LATEX_RESUME_FORMATTER
#define _HPP_LATEX_RESUME_FORMATTER

#include "latex_address_formatter.hpp"
#include "resume_formatter.hpp"
#include "string_converts.hpp"
#include <sys/time.h>

namespace fr {

  namespace resumetron {
    
    class latex_resume_formatter : public resume_formatter {

    public:
      typedef std::shared_ptr<latex_resume_formatter> pointer;

      latex_resume_formatter(resume::pointer my_resume) : resume_formatter(my_resume)
      {
	// Rewrite the plain text formatter put in by last class with
	// latex version (Really should offload this to a virtual
	// get_address_formatter function eh?)
	this->format_address = std::make_shared<latex_address_formatter>(my_resume);
      }

      latex_resume_formatter(const latex_resume_formatter &copy) = delete;

      virtual ~latex_resume_formatter()
      {
      }

      std::string section_header() const override
      {
	timeval tv;
	gettimeofday(&tv, nullptr);
	std::string retval("\\documentclass[11pt]{article}\n");
	// Multicol for skill listing
	retval.append("\\usepackage{multicol}\n");
	// Fullepage makes more reasonable margins
	retval.append("\\usepackage[cm]{fullpage}\n");
	// Apparently the cleanest way to get page x of y in a page footer
	// Gives us LastPage reference
	retval.append("\\usepackage{lastpage}\n");
	// Gives us the ability to redefine headers and footers
	retval.append("\\usepackage{fancyhdr}\n");
	// Set header size for copyright
	retval.append("\\setlength{\\headheight}{13.6pt}\n");
	// Actually enables fancy headers and footers
	retval.append("\\pagestyle{fancy}\n");
	// Clears the default headers and footers
	retval.append("\\fancyhf{}\n");
	// Removes the fancyhdr hrule from the top of the page
	retval.append("\\renewcommand{\\headrulewidth}{0pt}\n");
	// Sets copyright in header -- if some recruter submits your resume
	// somewhere without your permission and you're not considered for
	// a direct application because of that, you might want to sue
	// them.
	retval.append("\\chead{{\\fontsize{8}{11}\\selectfont Copyright \\copyright ");
	// Convert date to year (to_string<timeval> can optional take a
	// strftime string)
	retval.append(fr::time::to_string<timeval>()(tv,"%Y"));
	retval.append(" ");
	retval.append(my_resume->get_name());
	retval.append(". All rights reserved. Distribution of this document without prior permission is strictly forbidden.}}\n");
	// Set footer to page x of total_pages
	retval.append("\\cfoot{\\thepage\\ of \\pageref{LastPage} }\n");
	retval.append("\\begin{document}\n");

	return retval;
      }

      std::string section_footer() const override
      {
	std::string retval("\\end{document}\n");
	return retval;
      }

      std::string my_text() const override
      {
	std::stringstream output_stream;
	if (format_address.get() != nullptr) {
	  output_stream << format_address->format_text() << std::endl;
	}
	output_stream << "\\centerline{\\textbf{Resum\\'e: " << my_resume->get_name() << "}}" << std::endl;
	return output_stream.str();
      }

    };

  }

}

#endif
