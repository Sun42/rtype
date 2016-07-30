#ifndef WEAPON4_H
#define WEAPON4_H

#include <list>

#include "Action.h"
#include "Weapon.h"
#include "Scenario.h"

class Weapon4 : public Weapon
{
public:
  Weapon4(float timeOfCreation, float posXOnMap,
	  float posYOnMap, unsigned int idOwner);
  ~Weapon4();
  Weapon4(const Weapon4& rhs);
  Weapon4& operator=(const Weapon4& rhs);
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
    return (0.15f);
  }
#else
	static float getFrequency();
#endif
private:
  Scenario			_scenario;
};

#ifdef _WIN32
SpriteEntity*	BuilderWeapon4(unsigned int ownerId, float timeOfCreation,
	       float posXOnMap, float posYOnMap);
#endif


#endif //WEAPON4_H
