#ifndef PLAYER4_H
#define PLAYER4_H

#include "Ship.h"
#include "Scenario.h"

class Player4 : public  Ship
{
 public:
	Player4(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
    ~Player4();
    Player4(const Player4& rhs);
    Player4& operator=(const Player4& rhs);
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
SpriteEntity*	BuilderPlayer4(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
# endif // !_WIN32


#endif //PLAYER4_H
