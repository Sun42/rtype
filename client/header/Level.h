#ifndef H_LEVEL_H
#define H_LEVEL_H

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <SFML/Graphics.hpp>
#include "Scenario.h"

class	Level
{
 public:
  Level();
  Level(int idLevel);
  ~Level();
  Level(const Level& r);

  Level&	operator=(const Level& r);

  float		getTime() const;

  void		startScenario();
  void		execScenario();
  void		fillLevel();

 private:
  friend class boost::serialization::access;
  template<class Archive>
    void	serialize(Archive& ar, const unsigned int)
    {
      ar & BOOST_SERIALIZATION_NVP(_idLevel)  & BOOST_SERIALIZATION_NVP(_scenario);
    }

  int			_idLevel;
  sf::Clock		_clock;
  Scenario		_scenario;
};

#endif //H_LEVEL_H
