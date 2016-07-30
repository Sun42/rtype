#ifndef WEAPON2_H
#define WEAPON2_H

#include <list>

#include "Action.h"
#include "Weapon.h"
#include "Scenario.h"

class Weapon2 : public Weapon
{
public:
  Weapon2(float timeOfCreation, float posXOnMap,
	  float posYOnMap, unsigned int idOwner);
  ~Weapon2();
  Weapon2(const Weapon2& rhs);
  Weapon2& operator=(const Weapon2& rhs);
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
    return (0.2f);
  }
#else
	static float getFrequency();
#endif
private:
  Scenario		_scenario;
};

#ifdef _WIN32
SpriteEntity*	BuilderWeapon2(unsigned int ownerId, float timeOfCreation,
	       float posXOnMap, float posYOnMap);
#endif


#endif //WEAPON2_H
