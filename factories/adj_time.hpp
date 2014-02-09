/**
 * adj_time_string function proves useful elsewhere...
 */

#ifndef _HPP_ADJ_TIME
#define _HPP_ADJ_TIME

#include <string>
#include <stdexcept>
#include "string_converts.hpp"
#include <vector>

namespace fr {

  namespace resumetron {

    class adj_time {
    protected:

      // Mangle date in the form "Mmm YYYY" to a time format my time
      // parser can understand. It's not so much that it's in this exact
      // format (though doing so saves me having to write another regex)
      // but it does need all the fields. It doesn't have a provision
      // to include defaults for fields that aren't included.
      //
      // For the purposes of time tracking, this assumes you started
      // on midnight of the day you started and ended on midnight
      // of the day you ended. That should actually be pretty accurate
      // for estimating how many years of a particular skill you have.

      std::string adj_time_string(const std::string &ts)
      {
	std::vector<std::string> months{"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	
	std::string mmm = ts.substr(0,3);
	std::string yyyy = ts.substr(4,4);
        std::string retval(yyyy);
	int month_num = -1;
	for (int i = 0; i < 12; ++i) {
	  if (mmm == months.at(i)) {
	    month_num = i + 1; // Since we start at 0...
	    // Funnily the time conversion code is just going to subtract
	    // one from it later
	  }	  
	}
	if (-1 == month_num) {
	  std::string err("Month ");
	  err.append(mmm);
	  err.append(" not found in my months list.");
	  throw std::logic_error(err);
	}
	std::string month_string = fr::time::to_string<int>()(month_num);
	retval.append("-");
	if (month_string.length() == 1) {
	  retval.append("0");
	}
	retval.append(month_string);
	retval.append("-01T00:00:00.000000Z"); // Which technically specifies GMT but the duration will be the same no matter what.
	return retval;
      }

    };

    // I don't want everything that inherits from adj_time to get operator(),
    // but I do want to export a class that has it.
    class adj_time_sauce : public adj_time {
      
    public:

      std::string operator()(const std::string &to_adjust) {
	return adj_time_string(to_adjust);
      }
      
    };

  }

}

#endif
