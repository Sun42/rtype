#ifndef KEYBOARDINPUT_H_
#define KEYBOARDINPUT_H_

#include <list>

#include <SFML/Graphics.hpp>

#include "Arrows.h"
#include "Action.h"

class	KeyboardInput
{
 public:
  KeyboardInput();
  KeyboardInput(const KeyboardInput& rhs);
  ~KeyboardInput();

  KeyboardInput& operator=(const KeyboardInput& rhs);

  void	checkKeys(std::list<Action*>& actions);

 private:
  Arrows			_arrows;
  Arrows			_prevArrows;
};

typeShip	getShipType(unsigned int shipid);

#endif //! KEYBOARDINPUT_H_
