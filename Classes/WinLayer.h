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

class WinLayer : public PopupLayer{
public:
	WinLayer();
	~WinLayer();
	CREATE_FUNC(WinLayer);
	void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);

private:
	virtual bool init();
	virtual void onEnter();

	//touchÊ±¼àÌý£¬ÆÁ±ÎÏòÏÂ´¥Ãþ
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	virtual void __loadPicFromCSB();
	cocos2d::Ref* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;
};
