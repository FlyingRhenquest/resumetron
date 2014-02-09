/**
 * Verify our education factory can read the education data in our
 * sample resume.
 */

#include <boost/bind.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include "education.hpp"
#include "education_factory.hpp"
#include "node_engine.hpp"
#include <stdexcept>
#include <vector>

class education_factory_test : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(education_factory_test);
  CPPUNIT_TEST(test_education);
  CPPUNIT_TEST_SUITE_END();

  void got_education(const fr::resumetron::education &edu, std::vector<fr::resumetron::education> *populate)
  {
    populate->push_back(edu);
  }

public:

  void test_education()
  {
    cppxml::node_engine node_factory("../../test/sample_resume.xml");
    cppxml::xml_node::pointer doc = node_factory.get_document();
    std::vector<fr::resumetron::education> education_vector;
    fr::resumetron::education_factory factory(doc);
    factory.available.connect(boost::bind(&education_factory_test::got_education, this, _1, &education_vector));
    try {
      factory.run();
    } catch (std::exception &e) {
      CPPUNIT_FAIL(e.what());
    } catch(std::string e) {
      CPPUNIT_FAIL(e);
    }
    CPPUNIT_ASSERT(education_vector.size() > 0);
    CPPUNIT_ASSERT(education_vector[0].get_institution() == "Sanford Technical and Financial University");
    CPPUNIT_ASSERT(education_vector[0].get_major() == "CS");
    CPPUNIT_ASSERT(education_vector[0].get_degree() == "BS");
    CPPUNIT_ASSERT(education_vector[0].get_gpa() == "2.9");
    CPPUNIT_ASSERT(education_vector[0].get_start_time() > 0);
    CPPUNIT_ASSERT(education_vector[0].get_end_time() > 0);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(education_factory_test);
