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
#include "SetupLayer.h"
#include "AboutLayer.h"
#include "VideoPlay.h"

#define INTRODUCTION 14
#define SCENARIO     35
#define ABOUT		 36
#define SETUP		 37
#define QUIT		 38
USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;
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

	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_1.c_str(),true);
	loadCSBFromfile();
	m_isSilence = false;
	return true;

}

void MenuScene::menuCloseCallback(Ref* pSender)
{
	auto scene = ChooseGameScene::createScene();//¥¥Ω®¥˝«–ªªµƒ≥°æ∞
	auto transition = TransitionFadeBL::create(2.f, scene);//∏¯≥°æ∞∞¸◊∞∂Øª≠Ãÿ–ß 
	Director::getInstance()->replaceScene(transition);//‘À”√µº—›¿‡¿¥Ω¯––«–ªª≥°æ∞

}

void MenuScene::loadCSBFromfile(){
	Node* rootNode = CSLoader::createNode("mainmenu/mainmenu.csb");
	ActionTimeline* timeline = CSLoader::createTimeline("mainmenu/mainmenu.csb");
	timeline->gotoFrameAndPlay(0, 30, true);
	rootNode->runAction(timeline);

	Button* IntroButton = static_cast<Button*>(rootNode->getChildByTag(INTRODUCTION));
	Button* ScenarioButton = static_cast<Button*>(rootNode->getChildByTag(SCENARIO));
	Button* ModeButton = static_cast<Button*>(rootNode->getChildByTag(ABOUT));
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
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_1.c_str());
		 _playCG();
		break;
	case SCENARIO:
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_1.c_str());
		_ChooseScenario();
		break;
	case ABOUT:
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_1.c_str());
        _showAbout();
		break;
	case SETUP:
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_1.c_str());
		_showSetup();
		break;
	case QUIT:
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_2.c_str());
		_quit();
		break;
	default:
		break;
	}
}

void MenuScene::_playCG(){
	Scene* video = VideoPlay::createScene();
	Director::getInstance()->replaceScene(video);
}

void MenuScene::_ChooseScenario(){
	auto scene = ChooseGameScene::createScene();
	auto transition = TransitionPageTurn::create(2.0f, scene, false);
	Director::getInstance()->replaceScene(transition);
}

void MenuScene::_showSetup(){
	RenderTexture* fakeBackground = RenderTexture::create(1280, 720);
	fakeBackground->begin();
	this->getParent()->visit();
	fakeBackground->end();
	Scene* setupLayer = SetupLayer::createScene(fakeBackground, m_isSilence);
	SetupLayer* setup = static_cast<SetupLayer*>(setupLayer->getChildByTag(99));
	setup->setCallbackFunc(this, callfuncN_selector(MenuScene::__handlePopupSetupMenu));
	Director::getInstance()->pushScene(setupLayer);
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

void MenuScene::__handlePopupSetupMenu(Node* sender){
	if (m_isSilence){
		m_isSilence = false;
	}
	else{
		m_isSilence = true;
	}
}

void MenuScene::_showAbout(){
    auto about = AboutLayer::create();
    this->addChild(about);
}

