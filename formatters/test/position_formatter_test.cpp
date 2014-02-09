/**
 * Verify positions are formatted
 */

#include <boost/bind.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include "position_formatter.hpp"
#include "resume.hpp"
#include "resume_factory.hpp"
#include <string>

class position_formatter_test : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(position_formatter_test);
  CPPUNIT_TEST(basic_test);
  CPPUNIT_TEST_SUITE_END();

  void got_resume(const fr::resumetron::resume &res, fr::resumetron::resume *populate)
  {
    *populate = res;
  }

public:

  void basic_test()
  {
    fr::resumetron::resume_factory factory("../../test/sample_resume.xml");
    fr::resumetron::resume res;
    factory.available.connect(boost::bind(&position_formatter_test::got_resume, this, _1, &res));
    factory.run();
    
    fr::resumetron::resume::pointer res_ptr = std::make_shared<fr::resumetron::resume>(res);
    fr::resumetron::position_formatter::pointer formatter = std::make_shared<fr::resumetron::position_formatter>(res_ptr);
    std::string formatter_text = formatter->my_text();

    // I could search for the entire strings but I'd have to change the test
    // if I change my date formatting around a little. Not sure I need that
    // level of validation. I'm just making sure the jobs I put in the test
    // resume are there.
    CPPUNIT_ASSERT(formatter_text.find("Hydration") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("BACME") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("BIM") != std::string::npos);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(position_formatter_test);
