#ifndef PLAYER2_H
#define PLAYER2_H

#include "Ship.h"
#include "Scenario.h"

class Player2 : public  Ship
{
 public:
	Player2(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
    ~Player2();
    Player2(const Player2& rhs);
    Player2& operator=(const Player2& rhs);
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
SpriteEntity*	BuilderPlayer2(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
# endif // !_WIN32


#endif //PLAYER2_H
