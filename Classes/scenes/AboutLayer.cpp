//
//  AboutLayer.cpp
//  KateBattle
//
//  Created by Leonard on 15/5/13.
//
//
#include "AboutLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

AboutLayer::AboutLayer(){

}

AboutLayer::~AboutLayer(){

}

AboutLayer* AboutLayer::create(){
    AboutLayer* layer = new (std::nothrow)AboutLayer;
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return layer;
}

bool AboutLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    //delegate the Touch event
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(AboutLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(AboutLayer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(AboutLayer::onTouchMoved, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    __loadCSB();

    return true;
}


bool AboutLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
    return true;
}

void AboutLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){
}

void AboutLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
}

void AboutLayer::__loadCSB(){
    Layer* layer = static_cast<Layer*>(CSLoader::createNode("about/about.csb"));
    Button* back =static_cast<Button*>(layer->getChildByTag(23));
    back->addClickEventListener(CC_CALLBACK_1(AboutLayer::onBackClicked, this));
    this->addChild(layer);
}

void AboutLayer::onBackClicked(Ref* sender ){
    this->removeFromParent();
}