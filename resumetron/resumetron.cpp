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
 * Provides an executable with a command line interface to build available
 * resume formatters, set collapse dates, etc.
 */

#include "adj_time.hpp"
#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <climits>
#include "formatter_factory_interface.hpp"
#include <iostream>
#include "latex_formatter_factory.hpp"
#include "resume.hpp"
#include "resume_factory.hpp"
#include <stdexcept>
#include "string_converts.hpp" // From fr::time
#include <sys/time.h>
#include "text_formatter_factory.hpp"

// Normally I don't like using namespace but I've been typing these things
// unqualified in the namespace for a couple of weeks and I'm going to
// make a lot of typos if I don't include it.
using namespace fr::resumetron;

void got_resume(const resume &res, resume::pointer *pop)
{
  *pop = std::make_shared<resume>(res);
}

int main(int argc, char *argv[])
{
  bool list_achievements; // For chatty position listings
  bool list_responsibilities; // For chatting position listings

  // Can't just default this to 0l, some people might have jobs older
  // than 1970.
  long collapse_older_positions = LONG_MIN; // Collapse positions older than this
  std::string collapse_string; // String representation (Give it month year like in the resume format)
  std::string resume_filename;
  std::string output_format;
  boost::program_options::options_description desc("Usage:");
  desc.add_options()
    ("help,h", "Print help")
    ("input_file,i",
     boost::program_options::value<std::string>(&resume_filename)->required(),
     "Input filename")
    ("format,f",
     boost::program_options::value<std::string>(&output_format)->default_value(std::string("latex")),
     "Output format (can be text or latex)")
    ("collapse,c",
     boost::program_options::value<std::string>(&collapse_string)->default_value(std::string("")),
     "Collapse positions older than this. Use \"Mon Year\" format like resume. You'll need to put the date string in quotes.")
    ("achievements,a",
     boost::program_options::value<bool>(&list_achievements)->default_value(true),
     "List achievements in uncollapsed positions")
    ("responsibilities,r",
     boost::program_options::value<bool>(&list_responsibilities)->default_value(true),
     "List responsibilities in uncollapsed positions");
  boost::program_options::variables_map vm;
  try {
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
  } catch (std::exception &e) {
    std::cerr << "Caught exception trying to parse options:" << std::endl;
    std::cerr << e.what() << std::endl;
    std::cerr << "Try -h for help" << std::endl;
    exit(1);
  }

  if (vm.count("help")) {
    std::cerr << desc << std::endl;
    exit(1);
  }

  try {
    boost::program_options::notify(vm);
  } catch (std::exception &e) {
    std::cerr << "Caught exception reading program options:" << std::endl;
    std::cout << e.what() << std::endl;
    std::cout << "Try -h for help" << std::endl;
    exit(1);
  }

  // There's really not a whole lot preventing my time parser from shitting
  // itself if you give it a badly-formatted time
  if (!collapse_string.empty()) {
    // So if I crash here this is a reasonable clue why...
    std::cerr << "Parsing provided time: " << collapse_string << std::endl;
    timeval tv;
    tv = fr::time::string_to<timeval>()(adj_time_sauce()(collapse_string));
    collapse_older_positions = tv.tv_sec;
  }

  resume::pointer res;
  resume_factory factory(resume_filename);
  factory.available.connect(boost::bind(&got_resume, _1, &res));
  try {
    factory.run();
  } catch (std::exception &e) {
    std::cerr << "Exception caught reading resume" << std::endl;
    std::cerr << e.what() << std::endl;
  } catch (std::string &e) {
    // cppxml probably still throws some strings
    std::cerr << "Exception caught reading resume" << std::endl;
    std::cerr << e << std::endl;
  } catch(...) {
    std::cerr << "Unknown exception caught reading resume" << std::endl;
  }

  if (res.get() == nullptr) {
    std::cerr << "Unable to read resume" << std::endl;
    exit(1);
  }

  formatter_interface::pointer formatter;
  
  if (output_format == "latex") {
    latex_formatter_factory frmt_factory(res, collapse_older_positions, list_achievements, list_responsibilities);
    formatter = frmt_factory.get_formatter();
  } else { // Default/unknown gets plain text
    text_formatter_factory frmt_factory(res);
    formatter = frmt_factory.get_formatter();
  }

  std::cout << formatter->format_text() << std::endl;
  return(0);
}
