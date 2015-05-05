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

	//touchÊ±¼àÌý£¬ÆÁ±ÎÏòÏÂ´¥Ãþ
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void onBackButtonClick(cocos2d::Ref*);
};
