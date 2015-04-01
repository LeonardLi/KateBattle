#ifndef __KateBattle__ControllerMoveBase__
#define __KateBattle__ControllerMoveBase__

#include "cocos2d.h"



enum class JoystickEnum;
class Entity;

class ControllerMoveBase{
public:
	ControllerMoveBase();
	~ControllerMoveBase();
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);
	void simpleMove(JoystickEnum direction);
	bool init(Entity* entity);
	static ControllerMoveBase* create(Entity* entity);
protected:
	Entity* m_entity;
	bool m_isMoving;
	JoystickEnum heroDirection;
};
#endif