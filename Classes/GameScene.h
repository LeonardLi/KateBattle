#pragma once
#include "cocos2d.h"

class Hero;
enum class JoystickEnum;
class Joystick;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);



private:
	void menuCloseCallback(cocos2d::Ref* pSender);

	void onDirectionChange(JoystickEnum);

	Hero* m_hero;

	Joystick* m_stick;


};


