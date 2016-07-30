#ifndef WEAPON3_H
#define WEAPON3_H

#include <list>

#include "Action.h"
#include "Weapon.h"
#include "Scenario.h"

class Weapon3 : public Weapon
{
public:
  Weapon3(float timeOfCreation, float posXOnMap,
	  float posYOnMap, unsigned int idOwner);
  ~Weapon3();
  Weapon3(const Weapon3& rhs);
  Weapon3& operator=(const Weapon3& rhs);
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
SpriteEntity*	BuilderWeapon3(unsigned int ownerId, float timeOfCreation,
	       float posXOnMap, float posYOnMap);
#endif


#endif //WEAPON3_H
