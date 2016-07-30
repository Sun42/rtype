#ifndef MOVE_H_

# define MOVE_H_

#include <map>

#include "SpriteEntity.h"

class	Move
{
public:
	typedef	void	(Move::*ptrMoveMethod)(SpriteEntity*, float);

	Move();
	Move(Move const & rhs);
	Move& operator=(Move const & rhs);
	~Move();
	void	dontMove(SpriteEntity* sprite, float elapsedTime);
	void	moveUp(SpriteEntity* sprite, float elapsedTime);
	void	moveDown(SpriteEntity* sprite, float elapsedTime);
	void	moveLeft(SpriteEntity* sprite, float elapsedTime);
	void	moveRight(SpriteEntity* sprite, float elapsedTime);
	void	moveUpLeft(SpriteEntity* sprite, float elapsedTime);
	void	moveUpRight(SpriteEntity* sprite, float elapsedTime);
	void	moveDownLeft(SpriteEntity* sprite, float elapsedTime);
	void	moveDownRight(SpriteEntity* sprite, float elapsedTime);
	void	execMove(SpriteEntity* sprite);
private:
	std::map<char, ptrMoveMethod>	_movePtr;
};

#endif //! MOVE_H_