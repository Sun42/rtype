#include "Arrows.h"
//todo :ptr sur fonction
Arrows::Arrows() : left(false), right(false), up(false), down(false), shoot(false)
{
}

Arrows&	Arrows::operator=(const Arrows& rhs)
{
  if (this != &rhs)
    {
      this->left = rhs.left;
      this->right = rhs.right;
      this->up = rhs.up;
      this->down = rhs.down;
      this->shoot = rhs.shoot;
    }
  return (*this);
}
void	Arrows::manageArrows(sf::Event& Event)
{
  bool ret = (Event.Type == sf::Event::KeyPressed ? true : false);
  if (Event.Key.Code == sf::Key::Up)
    this->up = ret;
  if (Event.Key.Code == sf::Key::Down)
    this->down = ret;
  if (Event.Key.Code == sf::Key::Left)
    this->left = ret;
  if (Event.Key.Code == sf::Key::Right)
    this->right = ret;
}

void	Arrows::manageShoot(sf::Event& Event)
{
  if (Event.Key.Code == sf::Key::Space)
    {
      if (Event.Type == sf::Event::KeyPressed)
	this->shoot = true;
      if (Event.Type == sf::Event::KeyReleased)
	this->shoot = false;
    }
}

std::string	Arrows::getDirection()
{
  if (this->left && this->up)
    return "l";
  if (this->left && this->down)
    return "d";
  if (this->right && this->up)
    return "u";
  if (this->right && this->down)
    return "r";
  if (this->left)
    return "L";
  if (this->right)
    return "R";
  if (this->up)
    return "U";
  if (this->down)
    return "D";
  return "0";
}
