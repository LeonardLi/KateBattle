#include "SetupLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"
USING_NS_CC;
using namespace ui;
SetupLayer::SetupLayer(){
}

SetupLayer::~SetupLayer(){

}

bool SetupLayer::init(){
	if (!PopupLayer::init())
	{
		return false;
	}
	//delegate the Touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SetupLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(SetupLayer::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(SetupLayer::onTouchMoved, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	__loadPicFromCSB();
	return true;
}

void SetupLayer::__loadPicFromCSB(){
	Node* rootNode = CSLoader::createNode("Node.csb");
	rootNode->setPosition(VisibleRect::center());
	Button* backButton = static_cast<Button*>(rootNode->getChildByName("Button"));
	backButton->addClickEventListener(CC_CALLBACK_1(SetupLayer::onBackButtonClick, this));

	this->addChild(rootNode);
}

bool SetupLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	return true;
}

void SetupLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){

}

void SetupLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){

}

void SetupLayer::onBackButtonClick(cocos2d::Ref* sender){
	this->removeFromParent();
	Director::getInstance()->resume();
}
