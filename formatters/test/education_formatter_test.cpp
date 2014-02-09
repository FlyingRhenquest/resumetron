/**
 * Verify education formatter works
 */

#include <boost/bind.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include "education_formatter.hpp"
#include <memory>
#include "resume.hpp"
#include "resume_factory.hpp"
#include <string>

class education_formatter_test : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(education_formatter_test);
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
    factory.available.connect(boost::bind(&education_formatter_test::got_resume, this, _1, &res));
    factory.run();
    fr::resumetron::resume::pointer res_ptr = std::make_shared<fr::resumetron::resume>(res);
    fr::resumetron::education_formatter::pointer formatter = std::make_shared<fr::resumetron::education_formatter>(res_ptr);
    std::string formatter_text = formatter->my_text();

    CPPUNIT_ASSERT(formatter_text.find("Jun") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("Dec") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("CS") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("2.9") != std::string::npos);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(education_formatter_test);
