#ifndef PLAYER3_H
#define PLAYER3_H

#include "Ship.h"
#include "Scenario.h"

class Player3 : public  Ship
{
 public:
	Player3(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
    ~Player3();
    Player3(const Player3& rhs);
    Player3& operator=(const Player3& rhs);
	void				execActions(float);
	void				spriteMove(unsigned int numCol, unsigned int numRow);
	void				spriteUp();
	void				spriteDown();
	void				spriteLeft();
	void				spriteRight();

 private:
	 Scenario		_scenario;
};

# ifdef _WIN32
SpriteEntity*	BuilderPlayer3(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
# endif // !_WIN32


#endif //PLAYER3_H
