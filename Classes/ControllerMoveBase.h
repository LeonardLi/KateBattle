#pragma once
#include "cocos2d.h"

enum class JoystickEnum;
enum class ScenarioEnum;
enum class SubScenarioEnum;
class Hero;

class ControllerMoveBase{
public:

	ControllerMoveBase();

	~ControllerMoveBase();

	void simpleMove(JoystickEnum direction);

	void judgeBlock();

	void blockHeroDirection();

	void resetHeroDirection();

	void setBoundary();

	static ControllerMoveBase* create(Hero* hero, cocos2d::Sprite* map, ScenarioEnum, SubScenarioEnum);

private:
	
	bool init(Hero* hero, cocos2d::Sprite* map, ScenarioEnum, SubScenarioEnum);

	void __rollmapForward();
	void __rollmapBackward();
public:
	
	bool leftOrRight;
private:


	bool m_isMoving;	
	CC_SYNTHESIZE(bool, m_isAllowToLeft, isAllowToLeft);
	CC_SYNTHESIZE(bool, m_isAllowToRight, isAllowToRight);
	CC_SYNTHESIZE(bool, m_isAllowToUp, isAllowToUp);
	CC_SYNTHESIZE(bool, m_isAllowToDown, isAllowToDown);
	CC_SYNTHESIZE(bool, m_isAllowToLeftDown, isAllowToLeftDown);
	CC_SYNTHESIZE(bool, m_isAllowTLeftUp, isAllowToLeftUp);
	CC_SYNTHESIZE(bool, m_isAllowToRightUp, isAllowToRightUp);
	CC_SYNTHESIZE(bool, m_isAllowToRightDown, isAllowToRightDown);
	Hero* m_hero;
	cocos2d::Sprite* m_map;
	JoystickEnum heroDirection;

	bool m_isRight;
	bool m_isLeft;
	bool m_isStand;
	bool m_isUp;
	bool m_isDown;
	float m_rightBoundary;
	float m_leftBoundary;
	ScenarioEnum m_scenario;
	SubScenarioEnum m_subscenario;
};
