#include <sstream>
#include "Weapon2.h"

#ifdef _WIN32
SpriteEntity*	BuilderWeapon2(unsigned int idOwner, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Weapon2(timeOfCreation, posXOnMap, posYOnMap, idOwner));
}

float Weapon2::getFrequency()
{
  return (0.3f);
}

#else
extern "C"
{
typeWeapon	GetType()
{
  return (WEAPON2);
}

SpriteEntity*	Builder(unsigned int idOwner, float timeOfCreation, float posXOnMap, float posYOnMap)
{
  return (new Weapon2(timeOfCreation, posXOnMap, posYOnMap, idOwner));
}

}
#endif


Weapon2::Weapon2(float timeOfCreation, float posXOnMap,
		 float posYOnMap, unsigned int ownerId):
  Weapon(500, timeOfCreation, posXOnMap, posYOnMap, "./sprites/r-typesheet30a.png",
	 1, ownerId), _scenario()
{
  this->setWidthHeight(34, 34);
  this->_sprite.SetScale(0.8, 0.8);
  this->setPosOnSprite(0, 0);
  this->fillSprite();
}

Weapon2::~Weapon2()
{

}

Weapon2::Weapon2(const Weapon2& rhs):
Weapon(rhs), _scenario(rhs._scenario)
{
}

Weapon2& Weapon2::operator=(const Weapon2&)
{
	return (*this);
}

void	Weapon2::insert_action(Action* action,  float time,
		      std::list< std::pair<Action *, float> >& actions)
{
  std::pair<Action *, float> act;
  act.first = action;
  act.second = time;
  actions.push_back(act);
}

void	Weapon2::pop_actions(unsigned int /*id*/, float time,
			     std::list< std::pair<Action *, float> >& actions)
{
  //
  std::stringstream params;
  params << "d " << this->getId();
  std::string str = params.str();
  insert_action(new Action(MOVE, TYPEWEAPON, WEAPON2, str, this->_owner), (time += 0.1), actions);
  str[0] = 'l';
  insert_action(new Action(MOVE, TYPEWEAPON, WEAPON2, str, this->_owner), (time += 0.1), actions);
//   str[0] = 'l';
//   insert_action(new Action(MOVE, TYPEWEAPON, WEAPON2, str, this->_owner), (time += 0.1), actions);
  str[0] = 'u';
  insert_action(new Action(MOVE, TYPEWEAPON, WEAPON2, str, this->_owner), (time += 0.1), actions);
}

//utilite de la fonction = ??
void	Weapon2::scenarioCreator(std::list< std::pair<Action *, float> >& actions)
{
  float time  = 0;
  pop_actions(1/*??*/ , time, actions);
}

void				Weapon2::fillSprite()
{
  std::list< std::pair<Action *, float> > & myActions = this->_scenario.addActions();
  scenarioCreator(myActions);
}

void		Weapon2::execActions(float currentTime)
{
  std::list<std::pair<Action *, float> >::iterator  it = this->_scenario.addActions().begin();
  std::list<std::pair<Action *, float> >::iterator  save;
  while (it != this->_scenario.addActions().end() && (*it).second < currentTime)
    {
      if ((*it).second <= (currentTime - this->_timeOfCreation))
	{
	  save = it;
	  (*save).first->execAction();
	  ++it;
	  this->_scenario.addActions().remove(*save);
	}
      else
	++it;
    }
}

void				Weapon2::spriteUp()
{
  this->setPosOnSprite(0, 0);
}

void				Weapon2::spriteDown()
{
  this->setPosOnSprite(0, 0);
}

void				Weapon2::spriteLeft()
{
  this->setPosOnSprite(0, 0);
}

void				Weapon2::spriteRight()
{
  this->setPosOnSprite(0, 0);
}

