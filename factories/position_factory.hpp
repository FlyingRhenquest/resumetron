/**
 * Position factory -- breaks all positios out of the resume XML,
 * constructs objects for them and signals their availability.
 */

#ifndef _HPP_POSITION_FACTORY
#define _HPP_POSITION_FACTORY

#include <boost/signals2.hpp>
#include "position.hpp"
#include <stdexcept>
#include <memory>
#include "position.hpp"
#include <string>
#include "string_converts.hpp"
#include <sys/time.h>
#include "xml_node.hpp"
#include "xml_node_factory.hpp"

namespace fr {

  namespace resumetron {

    class position_factory : public xml_node_factory {

      cppxml::xml_node::pointer doc;
      
      const std::string Achievement = "achievement";
      const std::string Achievements = "achievements";
      const std::string Company = "company";
      const std::string Description = "description";
      const std::string Employment = "employment";
      const std::string End = "end";
      const std::string Location = "location";
      const std::string Position = "position";
      const std::string Responsibility = "responsibility";
      const std::string Skill = "skill";
      const std::string Skills = "skills";
      const std::string Start = "start";
      const std::string Title = "title";

    public:

      boost::signals2::signal<void(const position &)> available;

      position_factory(cppxml::xml_node::pointer doc) : doc(doc)
      {
      }

      ~position_factory()
      {
      }

      void run()
      {
	cppxml::xml_node::pointer employment = doc->find_child(Employment);
	if (nullptr == employment.get()) {
	  // Technically this is valid, but will make finding a job
	  // a huge pain in the ass.
	  std::cerr << "Warning: No employment records found." << std::endl;
	  return;
	}
	cppxml::child_vector positions = employment->find_children(Position);
	
	for (cppxml::xml_node::pointer position : positions) {
	  std::shared_ptr<std::string> company = position->find_attribute(Company);
	  if (nullptr == company.get()) {
	    std::string err("A position tag exists without a company name attribute, which is required.");
	    throw std::logic_error(err);
	  }
	  std::string title = get_node_text(position, Title);
	  std::string location = get_node_text(position, Location);
	  timeval start = fr::time::string_to<timeval>()(adj_time_string(get_node_text(position, Start)));
	  timeval end = fr::time::string_to<timeval>()(adj_time_string(get_node_text(position, End)));
	  std::string description = get_node_text(position, Description);
	  cppxml::child_vector all_skills = position->find_children(Skill);
	  cppxml::child_vector all_achievements = position->find_children(Achievement);
	  cppxml::child_vector all_resp = position->find_children(Responsibility);
	  fr::resumetron::position retval(title, location, *company, start.tv_sec, end.tv_sec, description);
	  for (cppxml::xml_node::pointer skill : all_skills) {
	    retval.add_skill(skill->get_text());
	  }
	  for (cppxml::xml_node::pointer achievement : all_achievements) {
	    retval.add_achievement(achievement->get_text());
	  }
	  for (cppxml::xml_node::pointer responsibility : all_resp) {
	    retval.add_responsibility(responsibility->get_text());
	  }
	  
	  available(retval);
	}
      }

    };

  }

}

#endif
