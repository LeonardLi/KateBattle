#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include "Equipment.h"
#include "JsonUtility.h"
class Hero;
class MonsterManager;
class Joystick;
enum class JoystickEnum;
enum class InventoryEnum;
enum class ScenarioEnum{	
	Port,
	Market,
	Sewer,
	ScenarioCounts
};
enum class SubScenarioEnum{
	LV1,
	LV2,
	LV3,
	LVcounts
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
	static cocos2d::Scene* createScene(ScenarioEnum, SubScenarioEnum);

	static GameScene* create(ScenarioEnum, SubScenarioEnum);

	virtual void update(float dt);

	GameScene();
	~GameScene();


	/*handle the message conveyed from the popup menu*/
	void _handlePopupSetupmMenu(cocos2d::Node* sender);
	void _handlePopupBagLayer(cocos2d::Node* sender);
	void _handlePopupWinLayer(cocos2d::Node* sender);
private:

	bool init(ScenarioEnum scenario, SubScenarioEnum subscenario);

	cocos2d::Node* loadCSB(ScenarioEnum scenario, SubScenarioEnum subscenario);

	cocos2d::Layer* loadControlLayer();

	void __createStickBar();
/////////////////////////////////////////////////////////////////////////CALLBACK

	/*control callback*/
	void menuCloseCallback(cocos2d::Ref* pSender);
	void attackBtnOnClick(cocos2d::Ref* pSender);
	void skillBtn1OnClick(cocos2d::Ref* pSender);
	void skillBtn2OnClick(cocos2d::Ref* pSender);
	void skillBtn3OnClick(cocos2d::Ref* pSender);


	/*perform popup menu callback, show the popup menu*/

	void _popupSetupMenu(cocos2d::Ref* sender);
	void _popupBagLayer(cocos2d::Ref* sender);
	void _popupWinLayer(cocos2d::Ref* sender);


	/*Joystick callback*/
	void onDirectionChange(JoystickEnum);

	void postAttackNotification(float dt);
	void postUseSkillNotification(float dt);
	void postBossAttackNotification(float dt);
	void postBossUseSkillNotification(float dt);

	Hero* m_hero;
	Joystick* m_stick;
	MonsterManager* m_monsterMgr;
	cocos2d::Sprite* m_map;

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

	void __loadCSB(ScenarioEnum);

	void onBackButtonClicked(cocos2d::Ref*);

	void onScenarioChosenClicked(cocos2d::Ref*);

	void onSubScenarioChooseCallback(cocos2d::Ref*, ScenarioEnum);
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


protected:
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void __loadPicFromCSB();

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
	static cocos2d::Scene* createScene(cocos2d::RenderTexture* sqr);
	static BagLayer* create();
	BagLayer();
	~BagLayer();
	
	void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);

private:
	void __loadPicFromCSB();
	bool init();

	void __handleEquipmentDetailLayer(cocos2d::Node*);
	void __handleInventoryDetailLayer(cocos2d::Node*);
	virtual void onEnter();

	//touch时监听，屏蔽向下触摸
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	
	void onInventoryClickedListener(cocos2d::Ref*);
	void onEquipmentClickedListener(cocos2d::Ref*);
	void onBackButtonClickListener(cocos2d::Ref*);

	bool __initFromFile();
	Equipment* __matchPic(int);

	void __playAnimation();

	cocos2d::Ref* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;

	cocos2d::Vector<Equipment*> m_equipmentVec;
	User m_user;
	cocos2d::EventListenerTouchOneByOne* m_listener;
	cocos2d::EventDispatcher* m_dispatcher;
};

/************************************************************************/
/*
Name: DetailLayer
Author: xiaoDe
Function: show detail information for the entity that clicked
Date: 2015/4/27
*/
/************************************************************************/
class DetailLayer : public PopupLayer{
public:
	DetailLayer();
	~DetailLayer();
    static DetailLayer* create(Equipment*);
	static DetailLayer* create(InventoryEnum);
	void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);
    
private:
    void __loadPicFromCSB(Equipment*);
	void __loadPicFromCSB(InventoryEnum type);
	

    bool init(Equipment*);
	bool init(InventoryEnum);
	virtual void onEnter();

	//touch时监听，屏蔽向下触摸
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


	void onUseButtonClicked(cocos2d::Ref*);
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

	virtual void __loadPicFromCSB();
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
	virtual void __loadPicFromCSB();
	cocos2d::Ref* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;
	virtual bool init();

	//touch时监听，屏蔽向下触摸
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void onBackButtonClick(cocos2d::Ref*);
};


