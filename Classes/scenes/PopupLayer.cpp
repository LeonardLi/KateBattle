#include "PopupLayer.h"
#include "cocos2d.h"
USING_NS_CC;
void PopupLayer::onEnter(){
	Layer::onEnter();
}

void PopupLayer::onExit(){
	Layer::onExit();
}

bool PopupLayer::init(){
	log("========= PopupLayer ========== init");
	if (!LayerColor::init())
	{
		return false;
	}
	//cover other layer
	setColor(Color3B::BLACK);
	setOpacity(128);
	return true;
}

void PopupLayer::__loadPicFromCSB(){
}
