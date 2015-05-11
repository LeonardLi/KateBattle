/************************************************************************/
/*
Name: LoseLayer
Author: xiaoDe
Function: show something when you win
Date: 2015/4/10
*/
/************************************************************************/

#include "PopupLayer.h"
#include "cocos2d.h"

enum class ScenarioEnum;
enum class SubScenarioEnum;
class LoseLayer : public PopupLayer
{
public:
	LoseLayer();
	~LoseLayer();
	static LoseLayer* create(ScenarioEnum, SubScenarioEnum);
	static cocos2d::Scene* createScene(cocos2d::RenderTexture* sqr, ScenarioEnum, SubScenarioEnum);


private:
	bool init(ScenarioEnum, SubScenarioEnum);
	virtual void onEnter();

	//touchÊ±¼àÌý£¬ÆÁ±ÎÏòÏÂ´¥Ãþ
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void __loadPicFromCSB();
	void __onBackMenuButtonClicked(cocos2d::Ref*);
	void __onReloadButtonClicked(cocos2d::Ref*);
	
	ScenarioEnum m_scenario;
	SubScenarioEnum m_subScenario;
};