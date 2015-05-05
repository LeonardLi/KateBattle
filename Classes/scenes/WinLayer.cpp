#include "WinLayer.h"
#include "cocos2d.h"
USING_NS_CC;

WinLayer::WinLayer():
m_callback(nullptr),
m_callbackListener(nullptr)
{

}

WinLayer::~WinLayer(){

}

void WinLayer::__loadPicFromCSB(){

}

bool WinLayer::init(){
	if (!PopupLayer::init())
	{
		return false;
	}
	//delegate the Touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(WinLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(WinLayer::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(WinLayer::onTouchMoved, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void WinLayer::setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun){
	m_callbackListener = target;
	m_callback = callFun;
}

bool WinLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	return true;
}

void WinLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){

}
void WinLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){

}

void WinLayer::onEnter(){

}