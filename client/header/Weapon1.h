#ifndef WEAPON1_H
#define WEAPON1_H

#include <list>

#include "Action.h"
#include "Weapon.h"
#include "Scenario.h"

class Weapon1 : public Weapon
{
public:
  Weapon1(float timeOfCreation, float posXOnMap,
	  float posYOnMap, unsigned int idOwner);
  ~Weapon1();
  Weapon1(const Weapon1& rhs);
  Weapon1& operator=(const Weapon1& rhs);
  void	fillSprite();
  void	scenarioCreator(std::list< std::pair<Action *, float> >& actions);
  void	pop_actions(unsigned int id, float time, std::list< std::pair<Action *, float> >& actions);
  void	insert_action(Action* action,  float time,
		      std::list< std::pair<Action *, float> >& actions);
  void	execActions(float currentTime);
  void	spriteUp();
  void	spriteDown();
  void	spriteLeft();
  void	spriteRight();
#ifndef _WIN32
  static float getFrequency()
  {
    return (0.3f);
  }
#else
	static float getFrequency();
#endif
private:
  Scenario			_scenario;
};

#ifdef _WIN32
SpriteEntity*	BuilderWeapon1(unsigned int ownerId, float timeOfCreation,
	       float posXOnMap, float posYOnMap);
#endif


#endif //WEAPON1_H
