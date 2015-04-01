#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
class Hero;
enum class JoystickEnum;
class Joystick;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(HelloWorld);



private:
	void menuCloseCallback(cocos2d::Ref* pSender);

	void onDirectionChange(JoystickEnum);

	Hero* m_hero;

	Joystick* m_stick;


};

#endif // __HELLOWORLD_SCENE_H__
