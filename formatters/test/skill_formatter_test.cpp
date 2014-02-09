/**
 * Verify skill format formats skills
 */

#include <boost/bind.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "resume.hpp"
#include "resume_factory.hpp"
#include "skill_formatter.hpp"
#include <string>

class skill_formatter_test : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(skill_formatter_test);
  CPPUNIT_TEST(test_with_test_resume);
  CPPUNIT_TEST_SUITE_END();

  void got_resume(const fr::resumetron::resume &res, fr::resumetron::resume *populate)
  {
    *populate = res;
  }

public:

  // Test with the sample resume in ../../test. It only has one
  // position, though, so I really need more to validate
  // skill aggregation.

  void test_with_test_resume()
  {
    fr::resumetron::resume_factory factory("../../test/sample_resume.xml");
    fr::resumetron::resume res;
    factory.available.connect(boost::bind(&skill_formatter_test::got_resume, this, _1, &res));
    factory.run();
    // Make a shared_ptr copy of resume (This is a little awkward but
    // should be less so in the main program.)
    fr::resumetron::resume::pointer res_ptr = std::make_shared<fr::resumetron::resume>(res);

    // Formatter's designed to run in a tree but the nice thing
    // about this is I can instantiate them individually for testing
    fr::resumetron::skill_formatter::pointer formatter = std::make_shared<fr::resumetron::skill_formatter>(res_ptr);
    std::string formatter_text = formatter->my_text();

    // Should suitably determine that all skills were found...
    CPPUNIT_ASSERT(formatter_text.find("delivery device") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("Time") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("n: 4.2") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("t: 4.2") != std::string::npos);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(skill_formatter_test);
