#pragma once
#include "cocos2d.h"

enum class JoystickEnum;
class Hero;

class ControllerMoveBase{
public:

	ControllerMoveBase();

	~ControllerMoveBase();

	void simpleMove(JoystickEnum direction);

	void judgeBlock();

	void blockHeroDirection();

	void resetHeroDirection();

	static ControllerMoveBase* create(Hero* hero, cocos2d::Sprite* map);

private:
	
	bool init(Hero* hero, cocos2d::Sprite* map);

	void __rollmapForward();
	void __rollmapBackward();
public:
	bool isAllowToLeft;
	bool isAllowToRight;
	bool isAllowToUp;
	bool isAllowToDown;
	bool isAllowToLeftUp;
	bool isAllowToLeftDown;
	bool isAllowToRightUp;
	bool isAllowToRightDown;

private:


	bool m_isMoving;
	CC_SYNTHESIZE(float, m_iSpeed, iSpeed);
	Hero* m_hero;
	cocos2d::Sprite* m_map;
	JoystickEnum heroDirection;
};
