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
 * Returns a formatter for a latex resume
 */

#ifndef _HPP_LATEX_FORMATTER_FACTORY
#define _HPP_LATEX_FORMATTER_FACTORY

#include <climits>
#include "formatter_factory_interface.hpp"
#include "latex_address_formatter.hpp"
#include "latex_education_formatter.hpp"
#include "latex_position_formatter.hpp"
#include "resume.hpp"
#include "latex_resume_formatter.hpp"
#include "latex_skill_formatter.hpp"

namespace fr {

  namespace resumetron {

    class latex_formatter_factory : public formatter_factory_interface {

      resume::pointer res;
      long collapse_older;
      bool list_achievements;
      bool list_responsibilities;

    public:

      // If you don't want your entire work history to be chatty, you
      // can specify collapse_older to be now - some fraction of your
      // career (Like 5 years.) This is a POSIX time in seconds.
      // Anything older than collapse_older will only have the dates,
      // job_title and company listed. If you want no job collapsing,
      // make it long_min. If you want all of them collapsed, make it
      // long_max.
      // list_achievements and list_responsibilities affects uncollapsed
      // jobs only.

      latex_formatter_factory(resume::pointer res, long collapse_older = LONG_MIN, bool list_achievements = true, bool list_responsibilities = true) : res(res), collapse_older(collapse_older), list_achievements(list_achievements), list_responsibilities(list_responsibilities)
      {
      }

      virtual ~latex_formatter_factory()
      {
      }

      formatter_interface::pointer get_formatter() override
      {
	latex_resume_formatter::pointer res_frmt = std::make_shared<latex_resume_formatter>(res);
	res_frmt->add(std::make_shared<latex_skill_formatter>(res));
	res_frmt->add(std::make_shared<latex_position_formatter>(res, collapse_older, list_achievements, list_responsibilities));
	res_frmt->add(std::make_shared<latex_education_formatter>(res));
	return res_frmt;
      }

    };

  }

}

#endif
