#ifndef INPUT_H_
#define INPUT_H_

#include <list>

#include "KeyboardInput.h"

class Input
{
 public:
  Input();
  Input(const Input& r);
  ~Input();

  Input&	operator=(const Input& r);

  void		fillActions();
  void		execActions();

 private:
  KeyboardInput			_keyInput;
  std::list<Action*>		_inputActions;
};
#endif //! INPUT_H_
