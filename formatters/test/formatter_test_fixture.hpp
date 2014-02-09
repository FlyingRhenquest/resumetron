/**
 * Hold some of the common code I noticed I was writing in all my tests.
 */

#ifndef _HPP_FORMATTER_TEST
#define _HPP_FORMATTER_TEST

#include <boost/bind.hpp>
#include <cppunit/extensions/HelperMacros.h>
#include <memory>
#include "resume.hpp"
#include "resume_factory.hpp"

class formatter_test_fixture : public CppUnit::TestFixture {

private:

  void got_resume(const fr::resumetron::resume &res, fr::resumetron::resume::pointer *populate)
  {
    *populate = std::make_shared<fr::resumetron::resume>(res);
  }

protected:

  fr::resumetron::resume::pointer resume_from_xml(std::string xml)
  {
    fr::resumetron::resume_factory factory(xml);
    fr::resumetron::resume::pointer retval;
    factory.available.connect(boost::bind(&formatter_test_fixture::got_resume, this, _1, &retval));
    factory.run();    
    return retval;
  }

public:

};

#endif
