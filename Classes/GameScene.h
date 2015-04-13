#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 


class Hero;
class MonsterManager;
class Joystick;
enum class JoystickEnum;

/************************************************************************/
/* 
Name: GameScene
Author: xiaoDe
Function: main scene for the game
Date: 
*/
/************************************************************************/
class GameScene : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();

    CREATE_FUNC(GameScene);

	virtual void update(float dt);


private:

	virtual bool init();

/////////////////////////////////////////////////////////////////////////CALLBACK

	/*control callback*/
	void menuCloseCallback(cocos2d::Ref* pSender);
	void attackBtnOnClick(cocos2d::Ref* pSender,cocos2d::ui::Widget::TouchEventType type);
	void skillBtn1OnClick(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void skillBtn2OnClick(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void skillBtn3OnClick(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);


	/*perform popup menu callback, show the popup menu*/
    void _popupEquipmentMenu(cocos2d::Ref* sender);
	void _popupSetupMenu(cocos2d::Ref* sender);
	void _popupInventoryMenu(cocos2d::Ref* sender);
	void _popupWinLayer(cocos2d::Ref* sender);

	/*handle the message conveyed from the popup menu*/
	void _handlePopupEquipmentMenu(cocos2d::Node* sender);

	/*Joystick callback*/
	void onDirectionChange(JoystickEnum);

	void postAttackNotification(float dt);
	void postUseSkillNotification(float dt);
	void postBossAttackNotification(float dt);
	void postBossUseSkillNotification(float dt);

	Hero* m_hero;
	Joystick* m_stick;
	MonsterManager* m_monsterMgr;

};

/************************************************************************/
/* 
Name: GameScene
Author: xiaoDe
Function: Scene for choosing the Chapter
Date:
*//************************************************************************/
class ChooseGameScene :public cocos2d::Layer{


};

/************************************************************************/
/*
Name: PopupLayer
Author: xiaoDe
Function: basic class for popuplayer
Date: 2015/4/10
*//************************************************************************/
class PopupLayer :public cocos2d::LayerColor{
public: 	

	virtual void loadPicFromCSB(std::string) = 0;
protected:
	virtual bool init();
	virtual void onEnter();
    virtual void onExit();
    
};

/************************************************************************/
/*
Name: EquipmentLayer
Author: xiaoDe
Function: EquipmentLayer
Date: 2015/4/10
*//************************************************************************/
class EquipmentLayer : public PopupLayer{
public:
	virtual void loadPicFromCSB(std::string csbfile);

	CREATE_FUNC(EquipmentLayer);

	virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    //touch时监听，屏蔽向下触摸
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void _ClickCallBack(cocos2d::Ref* sender);
    void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);
    
private:
	EquipmentLayer();
	~EquipmentLayer();
    
    cocos2d::Ref* m_callbackListener;
    cocos2d::SEL_CallFuncN m_callback;
};

/************************************************************************/
/*
Name: IventoryLayer
Author: xiaoDe
Function: InventoryLayer
Date: 2015/4/10
*//************************************************************************/
class InventoryLayer : public PopupLayer{

};

/************************************************************************/
/*
Name: WinLayer
Author: xiaoDe
Function: show something when you win
Date: 2015/4/10
*//************************************************************************/
class WinLayer : public PopupLayer{

};



