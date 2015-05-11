#include "WinLayer.h"
#include "cocos2d.h"
#include "VisibleRect.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "SoundsController.h"
#include "LoadingScene.h"
#include "SoundsDef.h"
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;


WinLayer::WinLayer():
m_callback(nullptr),
m_callbackListener(nullptr),
m_scenario(ScenarioEnum::Default),
m_subScenario(SubScenarioEnum::LVcounts)
{

}

WinLayer::~WinLayer(){

}
WinLayer* WinLayer::create(ScenarioEnum scenario, SubScenarioEnum subscenario){
	WinLayer* scene = new (std::nothrow)WinLayer;
	if (scene && scene->init(scenario, subscenario))
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return scene;

}

Scene* WinLayer::createScene(cocos2d::RenderTexture* sqr, ScenarioEnum scenario, SubScenarioEnum subscenario){
	Scene* scene = Scene::create();
	WinLayer* winlayer = WinLayer::create(scenario, subscenario);
	winlayer->setTag(99);
	scene->addChild(winlayer, 1);

	Sprite* fakeSprite = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	fakeSprite->setPosition(VisibleRect::center());
	fakeSprite->setFlippedY(true);
	fakeSprite->setColor(Color3B::GRAY);
	scene->addChild(fakeSprite, 0);
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_14.c_str());
	return scene;
}
void WinLayer::__loadPicFromCSB(){
	Node* rootNode = CSLoader::createNode("passpage/passpage.csb");
	Button* reloadButton = static_cast<Button*>(rootNode->getChildByTag(2)->getChildByTag(6));
	Button* nextButton = static_cast<Button*>(rootNode->getChildByTag(2)->getChildByTag(7));
	Button* backButton = static_cast<Button*>(rootNode->getChildByTag(2)->getChildByTag(8));

	if (m_scenario == ScenarioEnum::Sewer && m_subScenario ==SubScenarioEnum::LV3)
	{
		nextButton->setBright(false);
	}

	reloadButton->addClickEventListener(CC_CALLBACK_1(WinLayer::onReloadButtonClicked, this));
	nextButton->addClickEventListener(CC_CALLBACK_1(WinLayer::onNextButtonClicked, this));
	backButton->addClickEventListener(CC_CALLBACK_1(WinLayer::onBackButtonClicked, this));
	this->addChild(rootNode);
}

bool WinLayer::init(ScenarioEnum scenario, SubScenarioEnum subscenario){
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
	m_scenario = scenario;
	m_subScenario = subscenario;

	__unlockScenario();
	__loadPicFromCSB();
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
	LayerColor::onEnter();
}

void WinLayer::onBackButtonClicked(cocos2d::Ref*){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_19.c_str());
	auto scene = ChooseGameScene::createScene();
	Director::getInstance()->replaceScene(scene);
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_1.c_str(),true);
}

void WinLayer::onReloadButtonClicked(cocos2d::Ref*){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_18.c_str());
	auto scene = GameScene::createScene(m_scenario, m_subScenario);
	Director::getInstance()->replaceScene(scene);
}

void WinLayer::onNextButtonClicked(cocos2d::Ref*){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_18.c_str());
	Scene* scene = nullptr;
	if (m_subScenario < SubScenarioEnum::LV3)
	{
		int i = static_cast<int>(m_subScenario);
		i++;
		m_subScenario = static_cast<SubScenarioEnum>(i);
		scene = LoadingScene::createScene(m_scenario, m_subScenario);
	}
	else if (m_scenario != ScenarioEnum::Sewer){
		int k = static_cast<int>(m_scenario);
		k++;
		m_scenario = static_cast<ScenarioEnum>(k);
		m_subScenario = SubScenarioEnum::LV1;
		scene = LoadingScene::createScene(m_scenario, m_subScenario);
		SoundsController::getInstance()->stopBackgroundMusic(m_scenario);
		
	}
	else{
		//Over game
	}
	Director::getInstance()->replaceScene(scene);
}

void WinLayer::__unlockScenario(){
	User &user = JsonUtility::getInstance()->user;
	if (m_subScenario < SubScenarioEnum::LV3)
	{
		int i = static_cast<int>(m_scenario);
		int j = static_cast<int>(m_subScenario);
		user.Clear_BlockID[i][j + 1] = 1;
	}
	else if (m_scenario != ScenarioEnum::Sewer)
	{
		int i = static_cast<int>(m_scenario);
		user.Clear_BlockID[i + 1][0] = 1;
	}
	else
	{
		//game over
	}
}