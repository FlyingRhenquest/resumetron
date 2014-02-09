/**
 * Resume formatter really doesn't have a lot of functionality on its
 * own but I thought I should test it anyway.
 */

#include <cppunit/extensions/HelperMacros.h>
#include "education_formatter.hpp"
#include "formatter_test_fixture.hpp"
#include "position_formatter.hpp"
#include "resume.hpp"
#include "resume_factory.hpp"
#include "resume_formatter.hpp"
#include "skill_formatter.hpp"

class resume_formatter_test : public formatter_test_fixture {
  CPPUNIT_TEST_SUITE(resume_formatter_test);
  CPPUNIT_TEST(basic_test);
  CPPUNIT_TEST(full_doc_test);
  CPPUNIT_TEST_SUITE_END();

public:

  void basic_test()
  {
    fr::resumetron::resume::pointer res = resume_from_xml("../../test/sample_resume.xml");
    // This should create an address formatter on the fly
    fr::resumetron::resume_formatter::pointer formatter = std::make_shared<fr::resumetron::resume_formatter>(res);
    
    std::string formatter_text = formatter->my_text();

    CPPUNIT_ASSERT(formatter_text.find("Somewhere, FL") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("Resume: John") != std::string::npos);
  }

  // Build the full text-mode document and see how it turns out.
  void full_doc_test()
  {
    fr::resumetron::resume::pointer res = resume_from_xml("../../test/sample_resume.xml");
    fr::resumetron::resume_formatter::pointer formatter = std::make_shared<fr::resumetron::resume_formatter>(res);
    // You can rearrange what you display first by changing when you add
    // a formatter. So if you want education first, you can add that
    // formatter first (One could easily bundle this into a formatter
    // factory.)
    fr::resumetron::skill_formatter::pointer skill_fmt = std::make_shared<fr::resumetron::skill_formatter>(res);
    fr::resumetron::position_formatter::pointer pos_fmt = std::make_shared<fr::resumetron::position_formatter>(res);    
    fr::resumetron::education_formatter::pointer edu_fmt = std::make_shared<fr::resumetron::education_formatter>(res);
    formatter->add(skill_fmt);
    formatter->add(pos_fmt);
    formatter->add(edu_fmt);
    std::string formatter_text = formatter->format_text();

    CPPUNIT_ASSERT(formatter_text.find("Phone:") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("Resume") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("Skills") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("Work Experience") != std::string::npos);
    CPPUNIT_ASSERT(formatter_text.find("Education") != std::string::npos);
  }

};

CPPUNIT_TEST_SUITE_REGISTRATION(resume_formatter_test);
