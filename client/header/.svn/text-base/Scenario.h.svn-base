#ifndef H_SCENARIO_H
#define H_SCENARIO_H

#include <list>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>

#include "Action.h"

class	Scenario
{
 public:
  Scenario();
  Scenario(const Scenario& r);
  ~Scenario();
  Scenario& operator=(const Scenario& r);

  std::list< std::pair<Action *, float> >& addActions();

 private:
  friend class boost::serialization::access;
  template<class Archive>
    void	serialize(Archive& ar, const unsigned int)
    {
      ar & BOOST_SERIALIZATION_NVP(_actions);
    }

  std::list< std::pair<Action *, float> > _actions;
};

#endif //H_SCENARIO_H
