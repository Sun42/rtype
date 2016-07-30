#ifndef MONSTER2_H
#define MONSTER2_H

#include <list>
#include "Action.h"

#include "Ship.h"
#include "Scenario.h"

class Monster2 : public  Ship
{
 public:
  Monster2(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
  ~Monster2();
  Monster2(const Monster2& rhs);
  Monster2& operator=(const Monster2& rhs);
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
SpriteEntity*	BuilderMonster2(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
#endif


#endif //MONSTER2_H
