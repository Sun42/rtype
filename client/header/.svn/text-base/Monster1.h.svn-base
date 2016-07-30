#ifndef MONSTER1_H
#define MONSTER1_H

#include <list>
#include "Action.h"

#include "Ship.h"
#include "Scenario.h"

class Monster1 : public  Ship
{
 public:
  Monster1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
  ~Monster1();
  Monster1(const Monster1& rhs);
  Monster1& operator=(const Monster1& rhs);
  void				fillSprite();
  void				scenarioCreator(std::list< std::pair<Action *, float> >& actions);
  void				pop_actions(unsigned int id, float time, std::list< std::pair<Action *, float> >& actions);
  void				create_shoot(float time, std::list< std::pair<Action *, float> >& actions);
  void				insert_action(Action* action,  float time,
					      std::list< std::pair<Action *, float> >& actions);
  void				execActions(float currentTime);
  void				spriteUp();
  void				spriteDown();
  void				spriteLeft();
  void				spriteRight();

 private:
  Scenario	_scenario;
  //Weapon* ;
};

#ifdef _WIN32
SpriteEntity*	BuilderMonster1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
#endif


#endif //MONSTER1_H
