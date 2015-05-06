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
	void _handlePopupSetupMenu(cocos2d::Node* sender);
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
	bool m_isSilence;

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









