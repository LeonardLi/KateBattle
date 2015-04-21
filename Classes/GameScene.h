#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 


class Hero;
class MonsterManager;
class Joystick;
enum class JoystickEnum;
enum class ScenarioEnum{	
	Port,
	Market,
	Sewer,
	ScenarioCounts
};
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

	GameScene();
	~GameScene();
private:

	virtual bool init();

	cocos2d::Node* loadCSB(std::string csbfile);

	void __createStickBar();
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
	void _handlePopupSetupmMenu(cocos2d::Node* sender);
	void _handlePopupInventoryMenu(cocos2d::Node* sender);
	void _handlePopupWinLayer(cocos2d::Node* sender);

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
Name: ChooseGameScene
Author: xiaoDe
Function: Scene for choosing the Chapter
Date:
*/
/************************************************************************/
class ChooseGameScene :public cocos2d::Layer{

public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(ChooseGameScene);

private:
	virtual bool init();

	cocos2d::Node* loadCSB();

	void onBackButtonClicked(cocos2d::Ref*);
	void onScenarioChosenClicked(cocos2d::Ref*);

};

/************************************************************************/
/*
Name: GameScene
Author: xiaoDe
Function: Scene for choosing the Chapter
Date:
*/
/************************************************************************/
class SubChooseGameScene : public cocos2d::Layer{

public:
	SubChooseGameScene();
	~SubChooseGameScene();
	static cocos2d::Scene* createScene(ScenarioEnum);

	static SubChooseGameScene* create(ScenarioEnum);

private:
	bool init(ScenarioEnum);

	void __loadCSB(std::string);

	void onBackButtonClicked(cocos2d::Ref*);

	void onScenarioChosenClicked(cocos2d::Ref*);

};

/************************************************************************/
/*
Name: PopupLayer
Author: xiaoDe
Function: basic class for popuplayer
Date: 2015/4/10
*/
/************************************************************************/
class PopupLayer :public cocos2d::LayerColor{
public: 	

	virtual void loadPicFromCSB(std::string) = 0;
protected:
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;

};

/************************************************************************/
/*
Name: EquipmentLayer
Author: xiaoDe
Function: EquipmentLayer
Date: 2015/4/10
*/
/************************************************************************/
class EquipmentLayer : public PopupLayer{
public:

	EquipmentLayer();
	~EquipmentLayer();

	CREATE_FUNC(EquipmentLayer);    

    void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);
    
private:
	//touch时监听，屏蔽向下触摸
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void _ClickCallBack(cocos2d::Ref* sender);
	
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual void loadPicFromCSB(std::string csbfile);

    
    cocos2d::Ref* m_callbackListener;
    cocos2d::SEL_CallFuncN m_callback;
};

/************************************************************************/
/*
Name: InventoryLayer
Author: xiaoDe
Function: InventoryLayer
Date: 2015/4/10
*/
/************************************************************************/
class InventoryLayer : public PopupLayer{
public:
	InventoryLayer();
	~InventoryLayer();
	void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);
	CREATE_FUNC(InventoryLayer);

private:
	virtual bool init();
	virtual void onEnter();

	virtual void loadPicFromCSB(std::string);

	//touch时监听，屏蔽向下触摸
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	
	cocos2d::Ref* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;
};

/************************************************************************/
/*
Name: BagLayer
Author: xiaoDe
Function: show bag
Date: 2015/4/14
*/
/************************************************************************/

class BagLayer : public PopupLayer{
public:
	BagLayer();
	~BagLayer();
	CREATE_FUNC(BagLayer);
	void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);

private:
	virtual void loadPicFromCSB(std::string);
	virtual bool init();
	virtual void onEnter();

	//touch时监听，屏蔽向下触摸
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	cocos2d::Ref* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;
};

/************************************************************************/
/*
Name: WinLayer
Author: xiaoDe
Function: show something when you win
Date: 2015/4/10
*/
/************************************************************************/
class WinLayer : public PopupLayer{
public:
	WinLayer();
	~WinLayer();
	CREATE_FUNC(WinLayer);
	void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);

private:
	virtual bool init();
	virtual void onEnter();

	//touch时监听，屏蔽向下触摸
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	virtual void loadPicFromCSB(std::string);
	cocos2d::Ref* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;
};

/************************************************************************/
/*
Name: SetupLayer
Author: xiaoDe
Function: show something when you win
Date: 2015/4/14
*/
/************************************************************************/
class SetupLayer : public PopupLayer{
public:
	SetupLayer();
	~SetupLayer();
	CREATE_FUNC(SetupLayer);
	

private:
	virtual void loadPicFromCSB(std::string);
	cocos2d::Ref* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;
	virtual bool init();

	//touch时监听，屏蔽向下触摸
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void onBackButtonClick(cocos2d::Ref*);
};


