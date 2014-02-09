/**
 * Formatter to print skills with latex markup.
 */

#ifndef _HPP_LATEX_SKILL_FORMATTER
#define _HPP_LATEX_SKILL_FORMATTER

#include "skill_formatter.hpp"

namespace fr {

  namespace resumetron {

    class latex_skill_formatter : public skill_formatter {
      int columns;
      long filter_less_than;


    public:
      typedef std::shared_ptr<latex_skill_formatter> pointer;

      // Filter skills that have less time than filter_less_than. Maybe
      // you don't need to show everything you worked 2 months in.
      // Default is show everything
      latex_skill_formatter(resume::pointer my_resume, int columns = 3, long filter_less_than = 0l) : skill_formatter(my_resume), columns(columns), filter_less_than(filter_less_than)
      {
      }

      virtual ~latex_skill_formatter()
      {
      }

      std::string section_header() const override
      {
	std::string retval("\\section*{Skills:}\n");
	return retval;
      }

      std::string my_text() const override
      {
	std::stringstream output_stream;
	output_stream << std::fixed;
	skill_vector all_skills = accumulate_skills(my_resume->get_positions());
	
	output_stream << "\\begin{multicols}{" << columns << "}" << std::endl;
	
	for (skill_pair skill : all_skills) {
	  if (skill.second > filter_less_than) {
	    double years = ((double) skill.second) / (60.0 * 60.0 * 24.0 * 365.25);
	    output_stream << skill.first << ": " << std::setprecision(1) << years << " years\\par" << std::endl;
	  }
	}
	
	output_stream << "\\end{multicols}" << std::endl;
	return output_stream.str();
      }

    };

  }

}

#endif
