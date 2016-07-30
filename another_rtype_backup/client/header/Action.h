#ifndef __H_ACTION_H__
#define __H_ACTION_H__

#include <vector>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "SpriteFactory.h"
#include "WindowManager.h"
#include "Cmd.h"

enum typeAction
  {
    CREATE,
    MOVE,
    JUMP,
    DESTROY,
    SHOOT
  };

class	Action
{
 public:
  Action();
  //surcharge pour ship
  Action(unsigned int spriteid, typeAction typeaction,
	 typeSpriteEntity typeSprite, typeShip typeship,
	 std::string param);

  //surcharge pour weapon
  Action(typeAction typeaction, typeSpriteEntity typeSprite,
	 typeWeapon typeweapon,	 std::string param, unsigned int ownerid);

  //surcharge pour les decors
  Action(unsigned int spriteid, typeAction typeaction,
	 typeSpriteEntity typeSprite, typeDecor typedecor,
	 std::string param);

  Action(const Action& rhs);
  ~Action();
  Action& operator=(const Action& rhs);
  void	execAction();

 private:
  void		move();
  void		jump();
  void		create();
  void		destroy();
  void		del();
  void		shoot();

  void	fillMapPtr();
  friend class boost::serialization::access;
  template<class Archive>
    void	serialize(Archive& ar, const unsigned int)
    {
      ar & BOOST_SERIALIZATION_NVP(_spriteId)
	& BOOST_SERIALIZATION_NVP(_typeAction)
	& BOOST_SERIALIZATION_NVP(_typeSpriteEntity)
	& BOOST_SERIALIZATION_NVP(_typeShip)
	& BOOST_SERIALIZATION_NVP(_typeWeapon)
	& BOOST_SERIALIZATION_NVP(_typeDecor)
	& BOOST_SERIALIZATION_NVP(_params);
        //& BOOST_SERIALIZATION_NVP(_weaponOwnerId);
    }

  typedef void			(Action::*methodPtr)();
  unsigned int			_spriteId;
  typeAction			_typeAction;
  typeSpriteEntity		_typeSpriteEntity;
  typeShip			_typeShip;
  typeWeapon			_typeWeapon;
  typeDecor			_typeDecor;
  std::string			_params;
  std::vector<methodPtr>	_mPtr;
  unsigned int			_weaponOwnerId;
};

#endif // __H_ACTION_H__
