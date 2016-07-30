#ifndef H_ARROWS_H
# define H_ARROWS_H

#include <string>

#include <SFML/Graphics.hpp>

struct Arrows
{
  Arrows();
  void	manageShoot(sf::Event& Event);
  void	manageArrows(sf::Event& Event);
  Arrows&	operator=(const Arrows& rhs);
  std::string getDirection();

  bool	left;
  bool	right;
  bool	up;
  bool	down;
  bool	shoot;
};

#endif //H_ARROWS_H
