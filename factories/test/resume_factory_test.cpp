/**
 * Verify our factory can get a resume.
 */

#include <boost/bind.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include "resume.hpp"
#include "resume_factory.hpp"

class resume_factory_test : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(resume_factory_test);
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
    factory.available.connect(boost::bind(&resume_factory_test::got_resume, this, _1, &res));
    factory.run();
    CPPUNIT_ASSERT(res.get_name() == "John Smith");
    CPPUNIT_ASSERT(res.get_education().size() > 0);
    CPPUNIT_ASSERT(res.get_positions().size() > 0);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(resume_factory_test);
