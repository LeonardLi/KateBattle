/************************************************************************/
/*
Name: WinLayer
Author: xiaoDe
Function: show something when you win
Date: 2015/4/10
*/
/************************************************************************/
#include "PopupLayer.h"
#include "cocos2d.h"

enum class ScenarioEnum;
enum class SubScenarioEnum;
class WinLayer : public PopupLayer{
public:
	WinLayer();
	~WinLayer();
	static WinLayer* create(ScenarioEnum, SubScenarioEnum);
	static cocos2d::Scene* createScene(cocos2d::RenderTexture* sqr, ScenarioEnum, SubScenarioEnum);
	void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);

private:
	virtual bool init(ScenarioEnum, SubScenarioEnum);
	virtual void onEnter();

	//touchÊ±¼àÌý£¬ÆÁ±ÎÏòÏÂ´¥Ãþ
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void onReloadButtonClicked(cocos2d::Ref*);
	void onNextButtonClicked(cocos2d::Ref*);
	void onBackButtonClicked(cocos2d::Ref*);

	virtual void __loadPicFromCSB();
	cocos2d::Ref* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;

	ScenarioEnum m_scenario;
	SubScenarioEnum m_subScenario;
};
