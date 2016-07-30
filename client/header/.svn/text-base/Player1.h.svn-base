#ifndef PLAYER1_H
#define PLAYER1_H

#include "Ship.h"
#include "Scenario.h"

class Player1 : public  Ship
{
 public:
	Player1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
    ~Player1();
    Player1(const Player1& rhs);
    Player1& operator=(const Player1& rhs);
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
SpriteEntity*	BuilderPlayer1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
# endif // !_WIN32


#endif //PLAYER1_H
