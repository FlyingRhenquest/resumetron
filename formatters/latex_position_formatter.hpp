/**
 * Formats position with Latex markup
 */

#ifndef _HPP_LATEX_POSITION_FORMATTER
#define _HPP_LATEX_POSITION_FORMATTER

#include <climits>
#include "position_formatter.hpp"
#include <sys/time.h>

namespace fr {

  namespace resumetron {

    class latex_position_formatter : public position_formatter {
      long collapse_older;
      bool list_achievements; // For chatty listings
      bool list_responsibilities; // for chatty listings
      time_t now;

      // Just format the essentials, which should remain
      // the same whether this is chatty or terse
      std::string format_title(position::pointer job) const
      {
	std::stringstream out;
	out << "\\noindent\\textbf{" << time_to_string(job->get_start_date()) << " to ";
	if (job->get_end_date() > now) {
	  out << " Present";
	} else {
	  out << time_to_string(job->get_end_date());
	} 
	out << ":} " << job->get_company() << ", " << job->get_location() << " -- " << job->get_title() << "\\par" << std::endl;
	return out.str();
      }

      std::string chatty_work_history(position::pointer job) const
      {
	std::stringstream out;	
	
	out << format_title(job);

	out << "Description: " << job->get_description() << "\\par" << std::endl;
	out << "Skills used: ";
	bool first_skill = true;
	for (std::string skill : job->get_skills()) {
	  if (!first_skill) {
	    out << ", ";
	  }
	  first_skill = false;
	  out << skill;
	}
	out << "\\par" << std::endl;
	if (list_responsibilities) {
	  out << "Responsibilities:" << std::endl;
	  out << "\\begin{itemize}" << std::endl;
	  for (std::string resp : job->get_responsibilities()) {
	    out << "\\item " << resp << std::endl;
	  }
	  out << "\\end{itemize}" << std::endl;
	}
	if (list_achievements) {
	  out << std::endl << "Achievements:" << std::endl;
	  out << "\\begin{itemize}" << std::endl;
	  for (std::string achievement : job->get_achievements()) {
	    out << "\\item " << achievement << std::endl;
	  }
	  out << "\\end{itemize}" << std::endl;
	}
	return out.str();
      }

      std::string terse_work_history(position::pointer job) const
      {
	return format_title(job);
      }

    public:

      typedef std::shared_ptr<latex_position_formatter> pointer;

      /**
       * Anything with an end_date - now less than collapse_older
       * will be collapsed down to just a company, a title, a start
       * date and an end date. Maybe your recruiter doesn't want to
       * read about how you were a roadie for Bon Jovi in the 80s.
       * Computing time_now minus a few years (5, 7, 10 maybe)
       * might be a good thing to set this to.
       */

      latex_position_formatter(resume::pointer my_resume, long collapse_older = LONG_MIN, bool list_achievements = true, bool list_responsibilities = true) : position_formatter(my_resume), collapse_older(collapse_older), list_achievements(list_achievements), list_responsibilities(list_responsibilities)
      {
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	now = tv.tv_sec;
      }

      virtual ~latex_position_formatter()
      {
      }

      std::string section_header() const override
      {
	std::string retval("\\section*{Work History:}\n");
	return retval;
      }

      std::string my_text() const override
      {
	std::stringstream output_stream;
	position::vector all_positions = my_resume->get_positions();
	std::sort(all_positions.begin(), all_positions.end(), [](position::pointer left, position::pointer right) { return left->get_start_date() > right->get_start_date(); });
	for(position::pointer job : all_positions) {
	  if (job->get_end_date() < collapse_older) {
	    output_stream << terse_work_history(job) << std::endl;
	  } else {
	    output_stream << chatty_work_history(job) << std::endl;
	  }
	}
	return output_stream.str();
      }

    };

  }

}

#endif
