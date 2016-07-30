#ifndef EXPLOSION1_H
#define EXPLOSION1_H

#include <list>

#include "Action.h"
#include "Decor.h"
#include "Scenario.h"

class Explosion1 : public Decor
{
public:
  Explosion1(unsigned int idDecor, float timeOfCreation, float posXOnMap,
	  float posYOnMap);
  ~Explosion1();
  Explosion1(const Explosion1& rhs);
  Explosion1& operator=(const Explosion1& rhs);
  void				fillSprite();
  void				scenarioCreator(std::list< std::pair<Action *, float> >& actions);
  void				pop_actions(unsigned int id, float time, std::list< std::pair<Action *, float> >& actions);
  void				insert_action(Action* action,  float time,
					      std::list< std::pair<Action *, float> >& actions);
  unsigned int		touched(float currentTime);
  void				execActions(float currentTime);
  void				spriteUp();
  void				spriteDown();
  void				spriteLeft();
  void				spriteRight();

private:
  Scenario			_scenario;
  int				_cptImg;
  float				_lastImgTime;
};

#ifdef _WIN32
SpriteEntity*	BuilderExplosion1(unsigned int ownerId, float timeOfCreation,
	       float posXOnMap, float posYOnMap);
#endif


#endif //EXPLOSION1_H
