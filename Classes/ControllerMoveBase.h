#pragma once
#include "cocos2d.h"

enum class JoystickEnum;
class Hero;

class ControllerMoveBase{
public:

	ControllerMoveBase();

	~ControllerMoveBase();

	void simpleMove(JoystickEnum direction);

	static ControllerMoveBase* create(Hero* hero);

private:

	bool init(Hero* hero);
	bool m_isMoving;
	CC_SYNTHESIZE(int, m_iSpeed, iSpeed);
	Hero* m_hero;
	JoystickEnum heroDirection;
};
