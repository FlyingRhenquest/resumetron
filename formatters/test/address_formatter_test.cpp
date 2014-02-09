/**
 * Verify address formatter works
 */

#include "address.hpp"
#include "address_formatter.hpp"
#include <boost/bind.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include "resume.hpp"
#include "resume_factory.hpp"
#include <string>

class address_formatter_test : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(address_formatter_test);
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
    factory.available.connect(boost::bind(&address_formatter_test::got_resume, this, _1, &res));
    factory.run();
    fr::resumetron::resume::pointer res_ptr = std::make_shared<fr::resumetron::resume>(res);
    fr::resumetron::address_formatter::pointer formatter = std::make_shared<fr::resumetron::address_formatter>(res_ptr);
    std::string formatter_text = formatter->my_text();

    CPPUNIT_ASSERT(formatter_text.find("Smith") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("Sixth") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("FL") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("Somewhere") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("(800)") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("jsmith") != std::string::npos);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(address_formatter_test);
