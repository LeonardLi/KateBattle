//
//  MenuScene.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//
#include "cocos2d.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

Scene* MenuScene::createScene(){
	Scene* scene = Scene::create();

	Layer* layer = MenuScene::create();

	scene->addChild(layer);

	return scene;
}

bool MenuScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(MenuScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;

}

void MenuScene::menuCloseCallback(Ref* pSender)
{
	auto scene = ChooseGameScene::createScene();//创建待切换的场景
	auto transition = TransitionPageTurn::create(2.0f, scene, true);//给场景包装动画特效 
	Director::getInstance()->replaceScene(transition);//运用导演类来进行切换场景

}

void MenuScene::loadCSBFromfile(std::string csbfile){
	auto rootNode = CSLoader::createNode(csbfile);
	this->addChild(rootNode);
}