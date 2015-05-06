/************************************************************************/
/*
Name: SetupLayer
Author: xiaoDe
Function: show something when you win
Date: 2015/4/14
*/
/************************************************************************/
#include "PopupLayer.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"


class SetupLayer : public PopupLayer{
public:
	SetupLayer();
	~SetupLayer();
	static cocos2d::Scene* createScene(cocos2d::RenderTexture* sqr, bool isSilence);
	static SetupLayer* create(bool isSilence);
	void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);

private:
	virtual void __loadPicFromCSB();
	cocos2d::Ref* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;
	bool init(bool isSilence);

	//touchÊ±¼àÌý£¬ÆÁ±ÎÏòÏÂ´¥Ãþ
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void onBackButtonClick(cocos2d::Ref*);
	void onSlider(cocos2d::Ref*, cocos2d::ui::Slider::EventType type);
	void onSoundControlButtonClicked(cocos2d::Ref*);
	void onBackMenuButtonClicked(cocos2d::Ref*);
	void __flushSlider();

	bool m_isSilence;
	cocos2d::ui::Button* m_soundControl;
	cocos2d::ui::Slider* m_slider;
};
