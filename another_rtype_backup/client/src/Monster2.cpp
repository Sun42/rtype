#include <sstream>
#include "Monster2.h"


#ifdef _WIN32
SpriteEntity*	BuilderMonster2(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Monster2(id, timeOfCreation, posXOnMap, posYOnMap));
}
#else
extern "C"
{
typeShip	GetType()
{
  return (MONSTER2);
}

  SpriteEntity*	Builder(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
  {
    return (new Monster2(id, timeOfCreation, posXOnMap, posYOnMap));
  }
}
#endif

Monster2::Monster2(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap):
  Ship(id, 100, timeOfCreation, posXOnMap, posYOnMap, "./sprites/Monster2.png", 10), _scenario()
{
  this->setWidthHeight(50.f, 50.f);
  this->setPosOnSprite(0.f, 0.f);
  this->fillSprite();
  this->_sprite.SetScale(2.f, 2.f);
}

Monster2::~Monster2()
{

}

Monster2::Monster2(const Monster2& rhs):
Ship(rhs), _scenario(rhs._scenario)
{
}

Monster2& Monster2::operator=(const Monster2&)
{
	return (*this);
}

void	Monster2::insert_action(Action* action,  float time,
		      std::list< std::pair<Action *, float> >& actions)
{
  std::pair<Action *, float> act;
  act.first = action;
  act.second = time;
  actions.push_back(act);
}

void	Monster2::create_shoot(float time,  std::list< std::pair<Action *, float> >& actions)
{
  insert_action(new Action(SHOOT, TYPEWEAPON, WEAPON3, "-5 20", this->getId()), time, actions);
}

void	Monster2::pop_actions(unsigned int /*id*/, float time, std::list< std::pair<Action *, float> >& actions)
{
  this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER2, "L 0 0"), time, actions);
  this->create_shoot(time, actions);
  time += 5;
  this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER2, "0 0 0"), time, actions);
  time += 2;
  this->create_shoot(time, actions);
  time += 3;
  this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER2, "R 0 0"), time, actions);
  time += 2;
  this->create_shoot(time, actions);
  time += 3;
  this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER2, "D 0 0"), time, actions);
  time += 2;
  this->create_shoot(time, actions);
  time += 3;
  this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER2, "l 0 0"), time, actions);
  time += 3;
  this->create_shoot(time, actions);
  this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER2, "D 0 0"), time, actions);
  time += 2;
  this->create_shoot(time, actions);
  this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER2, "L 0 0"), time, actions);
}

void	Monster2::scenarioCreator(std::list< std::pair<Action *, float> >& actions)
{
  float time  = 0;
  pop_actions(1 , time, actions);
}

void				Monster2::fillSprite()
{
  std::list< std::pair<Action *, float> > & myActions = this->_scenario.addActions();
  scenarioCreator(myActions);
}

void		Monster2::execActions(float currentTime)
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

void				Monster2::spriteUp()
{
  this->setPosOnSprite(3, 0);
}

void				Monster2::spriteDown()
{
  this->setPosOnSprite(4, 0);
}

void				Monster2::spriteLeft()
{
  this->setPosOnSprite(3, 0);
}

void				Monster2::spriteRight()
{
  this->setPosOnSprite(6, 0);
}

