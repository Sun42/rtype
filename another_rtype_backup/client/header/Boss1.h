#ifndef BOSS1_H
#define BOSS2_H

#include <list>
#include "Action.h"

#include "Ship.h"
#include "Scenario.h"

class Boss1 : public  Ship
{
 public:
  Boss1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
  ~Boss1();
  Boss1(const Boss1& rhs);
  Boss1& operator=(const Boss1& rhs);
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
SpriteEntity*	BuilderBoss1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
#endif


#endif //BOSS1_H
