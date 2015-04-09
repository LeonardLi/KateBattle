#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 
class Hero;
class MonsterManager;
class Joystick;
enum class JoystickEnum;


class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();



    CREATE_FUNC(GameScene);

	virtual void update(float dt);


private:

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	void attackBtnOnClick(cocos2d::Ref* pSender,cocos2d::ui::Widget::TouchEventType type);

	void skillBtn1OnClick(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void skillBtn2OnClick(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void skillBtn3OnClick(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	void onDirectionChange(JoystickEnum);

	Hero* m_hero;

	Joystick* m_stick;

	MonsterManager* m_monsterMgr;

};


