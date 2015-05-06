#include "SetupLayer.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"
#include "SoundsController.h"
#include "MenuScene.h"
USING_NS_CC;
using namespace CocosDenshion;
using namespace ui;
SetupLayer::SetupLayer(){
}

SetupLayer::~SetupLayer(){

}

Scene* SetupLayer::createScene(cocos2d::RenderTexture* sqr, bool isSilence){
	Scene* scene = Scene::create();
	SetupLayer* baglayer = SetupLayer::create(isSilence);
	baglayer->setTag(99);
	scene->addChild(baglayer, 1);

	Sprite* fakeSprite = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	fakeSprite->setPosition(VisibleRect::center());
	fakeSprite->setFlippedY(true);
	fakeSprite->setColor(Color3B::GRAY);
	scene->addChild(fakeSprite, 0);
	return scene;
}

SetupLayer* SetupLayer::create(bool isSilence){
	auto setup = new (std::nothrow)SetupLayer;
	if (setup && setup->init(isSilence))
	{
		setup->autorelease();
		return setup;
	}
	CC_SAFE_DELETE(setup);
	return setup;
}

bool SetupLayer::init(bool isSilence){
	if (!LayerColor::init())
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
	m_isSilence = isSilence;
	__loadPicFromCSB();
	return true;
}

void SetupLayer::__loadPicFromCSB(){
	Node* rootNode = CSLoader::createNode("gamemenu/gamemenu.csb");
	//ImageView* image = static_cast<ImageView*>(rootNode->getChildByTag(2)->getChildByTag(5));
	Button* backButton = static_cast<Button*>(rootNode->getChildByTag(2)->getChildByTag(7));
	Button* backMenu = static_cast<Button*>(rootNode->getChildByTag(2)->getChildByTag(3));
	m_soundControl = static_cast<Button*>(rootNode->getChildByTag(2)->getChildByTag(6));
	m_slider = static_cast<Slider*>(rootNode->getChildByTag(2)->getChildByTag(4));
	
	__flushSlider();
    float origin = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
	m_slider->setPercent((int)(origin * 100));

	m_slider->addEventListener(CC_CALLBACK_2(SetupLayer::onSlider, this));
	backButton->addClickEventListener(CC_CALLBACK_1(SetupLayer::onBackButtonClick, this));
	backMenu->addClickEventListener(CC_CALLBACK_1(SetupLayer::onBackMenuButtonClicked, this));
	m_soundControl->addClickEventListener(CC_CALLBACK_1(SetupLayer::onSoundControlButtonClicked, this));

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
	Director::getInstance()->popScene();
}

void SetupLayer::onSlider(cocos2d::Ref* sender, Slider::EventType type){
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(sender);
		int out = slider->getPercent();
		float percent = (float)out / 100;
		SoundsController::getInstance()->setMusicVolum(percent);
		//log("==== %f =====", percent);
	}
}

void SetupLayer::onSoundControlButtonClicked(cocos2d::Ref* sender){
	Node* node = static_cast<Node*>(sender);
	if (m_callback && m_callbackListener)
	{
		(m_callbackListener->*m_callback)(node);
	}
	if (m_isSilence){
		m_isSilence = false;
		m_slider->setPercent(50);
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
	}
	else{
		m_isSilence = true;
		m_slider->setPercent(0.0f);
		//SoundsController::getInstance()->pauseBackgroundMusic();
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	__flushSlider();

}

void SetupLayer::onBackMenuButtonClicked(cocos2d::Ref*){
    auto scene = MenuScene::createScene();
    Director::getInstance()->replaceScene(scene);

}

void SetupLayer::setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun){
	this->m_callback = callFun;
	this->m_callbackListener = target;
}

void SetupLayer::__flushSlider(){
	if (m_isSilence){
		m_soundControl->loadTextures("gamemenu/7.png", "gamemenu/7.png");
	}
	else{
		m_soundControl->loadTextures("gamemenu/8.png", "gamemebu/8.png");
	}
}