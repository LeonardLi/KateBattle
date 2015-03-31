#ifndef __KateBattle__ControllerMoveBase__
#define __KateBattle__ControllerMoveBase__

#include "cocos2d.h"
#include "JoyStick.h"
#include "Entity.h"

#define SPEED 1

class ControllerMoveBase:public cocos2d::Node{
public:
	ControllerMoveBase();
	~ControllerMoveBase();
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);
	void simpleMove(JoystickEnum direction);
	bool init(Entity* entity);
	static ControllerMoveBase* create(Entity* entity);
	virtual void update(float dt);
protected:
	Entity* m_entity;
	bool m_isMoving;
	JoystickEnum heroDirection;
};
#endif