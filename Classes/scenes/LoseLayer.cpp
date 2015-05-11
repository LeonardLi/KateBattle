#include "LoseLayer.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "VisibleRect.h"
#include "SoundsController.h"
#include "SoundsDef.h"
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;


LoseLayer::LoseLayer(){

}

LoseLayer::~LoseLayer(){

}

LoseLayer* LoseLayer::create(ScenarioEnum scenario, SubScenarioEnum subscenario)
{
	LoseLayer* layer = new (std::nothrow)LoseLayer;
	if (layer && layer->init(scenario, subscenario))
	{
		layer->autorelease();
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return layer;
}

Scene* LoseLayer::createScene(cocos2d::RenderTexture* sqr, ScenarioEnum scenario, SubScenarioEnum subscenario)
{
	Scene* scene = Scene::create();
	LoseLayer* loseLayer = LoseLayer::create(scenario, subscenario);
	scene->addChild(loseLayer, 1);

	Sprite* fakeSprite = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	fakeSprite->setPosition(VisibleRect::center());
	fakeSprite->setFlippedY(true);
	fakeSprite->setColor(Color3B::GRAY);
	scene->addChild(fakeSprite, 0);
	return scene;
}

void LoseLayer::__loadPicFromCSB()
{
	Node* root = CSLoader::createNode("failpage/failpage.csb");
	Button* backMenuButton = static_cast<Button*>(root->getChildByTag(1)->getChildByTag(5));
	Button* reloadButton = static_cast<Button*>(root->getChildByTag(1)->getChildByTag(4));

	backMenuButton->addClickEventListener(CC_CALLBACK_1(LoseLayer::__onBackMenuButtonClicked, this));
	reloadButton->addClickEventListener(CC_CALLBACK_1(LoseLayer::__onReloadButtonClicked, this));

	this->addChild(root);
}

bool LoseLayer::init(ScenarioEnum scenario, SubScenarioEnum subscenario)
{
	if (!PopupLayer::init())
	{
		return false;
	}
	//delegate the Touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(LoseLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(LoseLayer::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(LoseLayer::onTouchMoved, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	m_scenario = scenario;
	m_subScenario = subscenario;
    __loadPicFromCSB();
	return true;
}

bool LoseLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	return true;
}

void LoseLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){

}
void LoseLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){

}

void LoseLayer::onEnter(){
	LayerColor::onEnter();
}

void LoseLayer::__onBackMenuButtonClicked(cocos2d::Ref*)
{
	auto scene = ChooseGameScene::createScene();
	Director::getInstance()->replaceScene(scene);
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_1.c_str(),true);
    
}

void LoseLayer::__onReloadButtonClicked(cocos2d::Ref*)
{
	auto scene = GameScene::createScene(m_scenario, m_subScenario);
	Director::getInstance()->replaceScene(scene);
}
