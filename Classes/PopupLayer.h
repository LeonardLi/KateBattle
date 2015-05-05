/************************************************************************/
/*
Name: PopupLayer
Author: xiaoDe
Function: basic class for popuplayer
Date: 2015/4/10
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"

class PopupLayer :public cocos2d::LayerColor{
public:


protected:
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void __loadPicFromCSB();

};