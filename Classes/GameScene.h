#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h" 
#include "Equipment.h"
#include "JsonUtility.h"
#include "cocostudio/CocoStudio.h"
class Hero;
class MonsterManager;
class Joystick;
class ControllerMoveBase;
enum class JoystickEnum;
enum class InventoryEnum;

enum class ScenarioEnum{	
	Port,
	Market,
	Sewer,
	ScenarioCounts,
	Default
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
	void _handlePopupSetupMenu(cocos2d::Node* sender);
	void _handlePopupBagLayer(cocos2d::Node* sender);
	void _handlePopupWinLayer(cocos2d::Node* sender);
private:

	bool init(ScenarioEnum scenario, SubScenarioEnum subscenario);

	cocos2d::Node* loadCSB(ScenarioEnum scenario, SubScenarioEnum subscenario);

	cocos2d::Layer* loadControlLayer();

	void __createStickBar();
	void __updateHero();

	void __useInventory(InventoryEnum);
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


	/*Joystick callback*/
	void onDirectionChange(JoystickEnum);

	void postScreen1IsClear();
	void postWinMessage(float dt);
	void postLoseMessage(float dt);


	void postAttackNotification(float dt);
	void postUseSkillNotification(float dt);
	void postBossAttackNotification(float dt);
	void postBossUseSkillNotification(float dt);

	//update
	void updateBar(float dt);

	Hero* m_hero;
	Joystick* m_stick;
	MonsterManager* m_monsterMgr;
	cocos2d::Sprite* m_map;
	bool m_isSilence;
	ScenarioEnum m_scenario;
	SubScenarioEnum m_subscenario;
	ControllerMoveBase* m_controller;
	CC_SYNTHESIZE(cocos2d::ui::Text* ,m_coinsNum,CoinNumber);
	cocos2d::Label* m_label;
	int m_coin;
	int m_showcoin;
	bool m_lock;
	cocos2d::Label* bloodNum;


	cocos2d::Vec2 m_position;
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









