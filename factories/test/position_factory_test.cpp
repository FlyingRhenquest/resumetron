/**
 * Verify position factory can create positions from sample XML
 */

#include <boost/bind.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include "node_engine.hpp"
#include "position.hpp"
#include "position_factory.hpp"
#include <vector>
#include "xml_node.hpp"

class position_factory_test : public CppUnit::TestFixture {

  CPPUNIT_TEST_SUITE(position_factory_test);
  CPPUNIT_TEST(basic_test);
  CPPUNIT_TEST_SUITE_END();

  typedef std::vector<fr::resumetron::position> position_vector;

  void populate_positions(const fr::resumetron::position &pos, position_vector *to_populate)
  {
    to_populate->push_back(pos);
  }

public:

  void basic_test()
  {
    cppxml::node_engine node_factory("../../test/sample_resume.xml");
    cppxml::xml_node::pointer doc = node_factory.get_document();
    position_vector positions;
    fr::resumetron::position_factory factory(doc);
    factory.available.connect(boost::bind(&position_factory_test::populate_positions, this, _1, &positions));
    factory.run();
    CPPUNIT_ASSERT(positions.size() > 0);
    CPPUNIT_ASSERT(positions[0].get_company() == "BIM");
    CPPUNIT_ASSERT(positions[0].get_title() == "Junior Hydration Engineer Assistant");
    CPPUNIT_ASSERT(positions[0].get_location() == "Somewhere, FL");
    CPPUNIT_ASSERT(positions[0].get_start_date() > 0l);
    CPPUNIT_ASSERT(positions[0].get_end_date() > 0l);
    CPPUNIT_ASSERT(positions[0].get_skills().size() > 0);
    CPPUNIT_ASSERT(positions[0].get_achievements().size() > 0);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(position_factory_test);
