/**
 * Verify the address facory can create at least one address.
 *
 * Yup, I've gone back to the full cppunit thing. I've memorized it now,
 * so may as well type it out.
 */

#include "address.hpp"
#include "address_factory.hpp"
#include <boost/bind.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include "node_engine.hpp"
#include <stdexcept>
#include "xml_node.hpp"

class address_factory_test : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(address_factory_test);
  CPPUNIT_TEST(test_address);
  CPPUNIT_TEST_SUITE_END();

  void got_address(const fr::resumetron::address &received, fr::resumetron::address *store)
  {
    *store = received;
  }

public:

  void test_address()
  {
    cppxml::node_engine node_factory("../../test/sample_resume.xml");
    cppxml::xml_node::pointer doc = node_factory.get_document();
    fr::resumetron::address_factory factory(doc);
    fr::resumetron::address addr;
    factory.available.connect(boost::bind(&address_factory_test::got_address, this, _1, &addr));
    try {
      factory.run();
    } catch (std::exception &e) {
      CPPUNIT_FAIL(e.what());
    } catch (std::string &e) {
      // Some of the old things can throw string.
      // I'm going to go back and replace them all
      // with logic errors one of these days. Pretty
      // much anything that throws a string is a logic
      // error.
      CPPUNIT_FAIL(e);
    }
    CPPUNIT_ASSERT(addr.get_street1() == "12345 Sixth Street");
    CPPUNIT_ASSERT(addr.get_street2().length() == 0);
    CPPUNIT_ASSERT(addr.get_city() == "Somewhere");
    CPPUNIT_ASSERT(addr.get_state() == "Florida");
    CPPUNIT_ASSERT(addr.get_zip() == "12345");
    CPPUNIT_ASSERT(addr.get_phone() == "(800) 555-1212 (cell)");
    CPPUNIT_ASSERT(addr.get_email() == "jsmith@jsmith.info");
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(address_factory_test);
