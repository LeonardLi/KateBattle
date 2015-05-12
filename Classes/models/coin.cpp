#include "cocos2d.h"
#include "coin.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SoundsDef.h"
#include "SoundsController.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;


Coin::Coin(){
}

Coin::~Coin(){
}

Coin* Coin::create(ScenarioEnum scenario){
	auto coin = new(std::nothrow)Coin;
	if (coin && coin->init(scenario))
	{
		coin->autorelease();
		return coin;
	}
	CC_SAFE_DELETE(coin);
	return coin;
}

bool Coin::init(ScenarioEnum scenario){
	if (!Node::init())
	{
		return false;
	}
	m_scenario = scenario;
	__createCoin();
	__loadCSB();
	return true;
}

void Coin::__loadCSB(){
	Node* root = CSLoader::createNode("gold/gold.csb");
	m_click = static_cast<Button*>(root->getChildByTag(6));
	m_armature = static_cast<Armature*>(root->getChildByTag(19));
	m_armature->getAnimation()->play("stand");
	m_click->addClickEventListener(CC_CALLBACK_1(Coin::onCoinClicked, this));
	this->addChild(root);
}

void Coin::onCoinClicked(Ref*){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_29.c_str());
    m_click->setEnabled(false);
	User& user = JsonUtility::getInstance()->user;
	user.UserGoldsNumber = user.UserGoldsNumber + m_coin;
	auto callfuncPlay = CallFunc::create([=](){
		m_armature->getAnimation()->play("jump", -1, 0);
	});
	auto callfuncRemove = CallFunc::create([=](){
		this->removeFromParent();
	});
	this->runAction(Sequence::create(callfuncPlay, DelayTime::create(1.0f), callfuncRemove, NULL));
}

void Coin::__createCoin(){

	float percent = RandomHelper::random_real(0.8f, 1.2f);
	int number;
	switch (m_scenario)
	{
	case ScenarioEnum::Port:
		number = (int)(percent * 50);
		break;
	case ScenarioEnum::Market:
		number = (int)(percent * 100);
		break;
	case ScenarioEnum::Sewer:
		number = (int)(percent * 180);
		break;	
	default:
		break;
	}
	setCoinNumber(number);
}