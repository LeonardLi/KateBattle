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
#include "SoundsDef.h"
#include "SoundsController.h"

#define INTRODUCTION 14
#define SCENARIO     35
#define MODE		 36
#define SETUP		 37
#define QUIT		 38
USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;

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

	SoundsController::getInstance()->playBackgroundMusic(MUSIC_1.c_str());
	loadCSBFromfile();

	return true;

}

void MenuScene::menuCloseCallback(Ref* pSender)
{
	auto scene = ChooseGameScene::createScene();//创建待切换的场景
	auto transition = TransitionCrossFade::create(0.5f, scene);//给场景包装动画特效 
	Director::getInstance()->replaceScene(transition);//运用导演类来进行切换场景

}

void MenuScene::loadCSBFromfile(){
	Node* rootNode = CSLoader::createNode("mainmenu/mainmenu.csb");
	ActionTimeline* timeline = CSLoader::createTimeline("mainmenu/mainmenu.csb");
	timeline->gotoFrameAndPlay(0, 30, true);
	rootNode->runAction(timeline);

	Button* IntroButton = static_cast<Button*>(rootNode->getChildByTag(INTRODUCTION));
	Button* ScenarioButton = static_cast<Button*>(rootNode->getChildByTag(SCENARIO));
	Button* ModeButton = static_cast<Button*>(rootNode->getChildByTag(MODE));
	Button* setupButton = static_cast<Button*>(rootNode->getChildByTag(SETUP));
	Button* quitButton = static_cast<Button*>(rootNode->getChildByTag(QUIT));


	IntroButton->addClickEventListener(CC_CALLBACK_1(MenuScene::onButtonClicked, this));
	ScenarioButton->addClickEventListener(CC_CALLBACK_1(MenuScene::onButtonClicked, this));
	ModeButton->addClickEventListener(CC_CALLBACK_1(MenuScene::onButtonClicked, this));
	setupButton->addClickEventListener(CC_CALLBACK_1(MenuScene::onButtonClicked, this));
	quitButton->addClickEventListener(CC_CALLBACK_1(MenuScene::onButtonClicked, this));
	this->addChild(rootNode);
}

void MenuScene::onButtonClicked(Ref* ButtonClicked){
	Button* button = static_cast<Button*>(ButtonClicked);
	log("%d",button->getTag());

	switch (button->getTag())
	{
	case INTRODUCTION:
		 _playCG();
		break;
	case SCENARIO:
		_ChooseScenario();
		break;
	case MODE:

		break;
	case SETUP:
		_showSetup();
		break;
	case QUIT:
		_quit();
		break;
	default:
		break;
	}
}

void MenuScene::_playCG(){
}

void MenuScene::_ChooseScenario(){
	auto scene = ChooseGameScene::createScene();
	auto transition = TransitionCrossFade::create(3.0f, scene);
	Director::getInstance()->replaceScene(scene);
}

void MenuScene::_showSetup(){
	SetupLayer* setup = SetupLayer::create();
	this->addChild(setup, 2);
}

void MenuScene::_quit(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}