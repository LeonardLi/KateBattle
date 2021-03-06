#include "cocos2d.h"
#include "GameScene.h"
#include "SetupLayer.h"
#include "BagLayer.h"
#include "ControllerMoveBase.h"
#include "Hero.h"
#include "MonsterManager.h"
#include "JoyStick.h"
#include "I_State.h"
#include "WinLayer.h"
#include "LoseLayer.h"
#include "MenuScene.h"
#include "SoundsController.h"
#include "SoundsDef.h"
#include "Inventory.h"
#include "TreasureBox.h"
#include "VisibleRect.h"
#include "LoadingScene.h"
#include "JsonUtility.h"
#include "coin.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

#define SKILL1COLDTIME 20
#define SKILL2COLDTIME 30
#define SKILL3COLDTIME 40

GameScene::GameScene():
m_hero(nullptr),
m_stick(nullptr),
m_monsterMgr(nullptr),
m_map(nullptr),
m_isSilence(false),
m_lock(false),
bloodNum(nullptr)
{

}

GameScene::~GameScene(){
}

Scene* GameScene::createScene(ScenarioEnum scenario,SubScenarioEnum subscenario)
{
    auto scene = Scene::create();
	auto layer = GameScene::create(scenario, subscenario);
    scene->addChild(layer);
    return scene;
}

GameScene* GameScene::create(ScenarioEnum scenario, SubScenarioEnum subscenario){
	GameScene* gameScene = new GameScene();
	if (gameScene && gameScene->init(scenario, subscenario))
	{
		gameScene->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(gameScene);
	}
	return gameScene;
}

bool GameScene::init(ScenarioEnum scenario, SubScenarioEnum subscenario)
{
    if ( !Layer::init() )
    {
        return false;
    }

	m_scenario = scenario;
	m_subscenario = subscenario;
	auto rootnode = loadCSB(scenario, subscenario);

	this->addChild(rootnode, 0);
	
	auto controllayer = loadControlLayer();
	this->addChild(controllayer, 1);

	m_hero = Hero::create();
	m_hero->setPosition(300, 200);

	auto bar = static_cast<LoadingBar*>(controllayer->getChildByTag(7));
	m_hero->bloodBar = bar;

	m_map = static_cast<Sprite*>(rootnode->getChildByTag(80));	
	m_map->addChild(m_hero, 10);
	
	m_controller = ControllerMoveBase::create(m_hero, m_map,  m_scenario, m_subscenario);
	m_hero->setMoveController(m_controller);

	__createStickBar();
    
	bloodNum = Label::create(" ","fonts/Marker Felt.ttf",30);
	bloodNum->setPosition(Vec2(360, 640));
	bloodNum->setColor(Color3B::WHITE);
	this->addChild(bloodNum,3);

	m_monsterMgr = MonsterManager::createWithLevel(m_scenario,m_subscenario);
	m_hero->m_heroMonsterList.clear();
	m_hero->m_heroMonsterList = m_monsterMgr->m_showedMonsterList;
	m_map->addChild(m_monsterMgr);

	this->scheduleUpdate();	
	this->scheduleOnce(schedule_selector(GameScene::postAttackNotification), 1.0f);
	this->scheduleOnce(schedule_selector(GameScene::postBossAttackNotification), 1.0f);
	this->schedule(schedule_selector(GameScene::updateBar), 0, kRepeatForever, 0);
	return true;
}

Node* GameScene::loadCSB(ScenarioEnum scenario, SubScenarioEnum subscenario){
	Node* rootNode = nullptr;
	ActionTimeline* actionTime = nullptr;
	switch (scenario)
	{
	case ScenarioEnum::Port:
		switch (subscenario)
		{
		case SubScenarioEnum::LV1:
			rootNode = CSLoader::createNode("gangkou1/gangkou1.csb");
			actionTime = CSLoader::createTimeline("gangkou1/gangkou1.csb");
			break;
		case SubScenarioEnum::LV2:
			rootNode = CSLoader::createNode("gangkou2/gangkou2.csb");
			actionTime = CSLoader::createTimeline("gangkou2/gangkou2.csb");
			break;
		case SubScenarioEnum::LV3:
			rootNode = CSLoader::createNode("gangkou3/gangkou3.csb");
			actionTime = CSLoader::createTimeline("gangkou3/gangkou3.csb");

			break;
		default:
			break;
		}
		break;
	case ScenarioEnum::Market:
		switch (subscenario)
		{
		case SubScenarioEnum::LV1:
			rootNode = CSLoader::createNode("jishi1/jishi1.csb");
			actionTime = CSLoader::createTimeline("jishi1/jishi1.csb");
			break;
		case SubScenarioEnum::LV2:
			rootNode = CSLoader::createNode("jishi2/jishi2.csb");
			actionTime = CSLoader::createTimeline("jishi2/jishi2.csb");
			break;
		case SubScenarioEnum::LV3:
			rootNode = CSLoader::createNode("jishi3/jishi3.csb");
			actionTime = CSLoader::createTimeline("jishi3/jishi3.csb");
			break;
		default:
			break;
		}
		break;
	case ScenarioEnum::Sewer:
		switch (subscenario)
		{
		case SubScenarioEnum::LV1:
			rootNode = CSLoader::createNode("xiashuidao1/xiashuidao1.csb");
			actionTime = CSLoader::createTimeline("xiashuidao1/xiashuidao1.csb");
			break;
		case SubScenarioEnum::LV2:
			rootNode = CSLoader::createNode("xiashuidao2/xiashuidao2.csb");
			actionTime = CSLoader::createTimeline("xiashuidao2/xiashuidao2.csb");
			break;
		case SubScenarioEnum::LV3:
			rootNode = CSLoader::createNode("xiashuidao3/xiashuidao3.csb");
			actionTime = CSLoader::createTimeline("xiashuidao3/xiashuidao3.csb");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
	
	actionTime->gotoFrameAndPlay(0, 60, true);
	rootNode->runAction(actionTime);
	return rootNode;
}

Layer* GameScene::loadControlLayer(){
	Layer* control = static_cast<Layer*>(CSLoader::createNode("renwujiemian/renwujiemian.csb"));
	Button* setupButton = static_cast<Button*>(control->getChildByTag(9));
	Button* bagButton = static_cast<Button*>(control->getChildByTag(8));
	Text* m_coinsNum = static_cast<Text*>(control->getChildByTag(19));
    Text* bonesNumber = static_cast<Text*>(control->getChildByTag(18));
	m_coin = JsonUtility::getInstance()->user.UserGoldsNumber;
    int bones = JsonUtility::getInstance()->user.UserBonesNumber;
	bonesNumber->setFontName("fonts/Marker Felt.ttf");
    bonesNumber->setString(std::to_string(bones));
   
	m_showcoin = m_coin;
	
	m_position = m_coinsNum->getPosition();
    m_coinsNum->removeFromParentAndCleanup(true);
    
	m_label = Label::create(std::to_string(m_showcoin), "fonts/Marker Felt.ttf", 30);
    m_label->setPosition(m_position);
    control->addChild(m_label);
	setupButton->addClickEventListener(CC_CALLBACK_1(GameScene::_popupSetupMenu, this));
	bagButton->addClickEventListener(CC_CALLBACK_1(GameScene::_popupBagLayer, this));

	auto attackButton = static_cast<Button*>(control->getChildByTag(10));
	attackButton->addClickEventListener(CC_CALLBACK_1(GameScene::attackBtnOnClick, this));

	auto SkillButton1 = static_cast<Button*>(control->getChildByTag(12));
	SkillButton1->addClickEventListener(CC_CALLBACK_1(GameScene::skillBtn1OnClick, this));


	auto SkillButton2 = static_cast<Button*>(control->getChildByTag(13));
	SkillButton2->addClickEventListener(CC_CALLBACK_1(GameScene::skillBtn2OnClick, this));

	auto SkillButton3 = static_cast<Button*>(control->getChildByTag(14));
	SkillButton3->addClickEventListener(CC_CALLBACK_1(GameScene::skillBtn3OnClick, this));
	control->setTag(99);
	return control;

	
}

void GameScene::onDirectionChange(JoystickEnum direction){
	m_hero->ChangeDirection(direction);
}

void GameScene::__createStickBar(){
	m_stick = Joystick::create("caozonggan1.png", "caozonggan2.png");
	this->addChild(m_stick, 0);
	m_stick->setPosition(Vec2(200, 200));
	m_stick->setDieRadius(120);
	m_stick->setFailRadius(0);
	m_stick->onDirection = CC_CALLBACK_1(GameScene::onDirectionChange, this);
	m_stick->onRun();
}

void GameScene::attackBtnOnClick(Ref* Sender){
	Button* button = static_cast<Button*>(Sender);
	if (m_hero->getisDead() == false&&m_hero->getStun()==NOTSTUN&&m_hero->m_canControl==true)
	{
		button->setTouchEnabled(false);
		m_hero->attack();
		auto callfunc = CallFunc::create([=](){
			button->setTouchEnabled(true);
		});
		button->runAction(Sequence::create(DelayTime::create(1.683-m_hero->getcurAttackSpeed()*0.007), callfunc, NULL));
	}
}

void GameScene::skillBtn1OnClick(Ref* Sender){
	Button* button = static_cast<Button*>(Sender);
	if (m_hero->getisDead() == false && m_hero->getStun() == NOTSTUN&&m_hero->m_canControl == true)
	{
		button->setTouchEnabled(false);
		m_hero->hitGroundSkill();
		auto callfunc = CallFunc::create([=](){
			button->setTouchEnabled(true);
		});
		button->runAction(Sequence::create(DelayTime::create(SKILL1COLDTIME), callfunc, NULL));
		auto to1 = Sequence::createWithTwoActions(ProgressTo::create(0, 100), ProgressTo::create(SKILL1COLDTIME,0));

		auto shadow = ProgressTimer::create(Sprite::create("skillshadow.png"));
		shadow->setPosition(button->getBoundingBox().size.width / 2, button->getBoundingBox().size.height / 2);
		button->addChild(shadow, 99, 1);
		shadow->setType(ProgressTimer::Type::RADIAL);
		shadow->setReverseProgress(true);
		shadow->runAction(to1);
	}
	
}

void GameScene::skillBtn2OnClick(Ref* Sender){
	Button* button = static_cast<Button*>(Sender);
	if (m_hero->getisDead() == false && m_hero->getStun() == NOTSTUN&&m_hero->m_canControl == true)
	{
		button->setTouchEnabled(false);
		m_hero->blink();
		auto callfunc = CallFunc::create([=](){
			button->setTouchEnabled(true);
		});
		button->runAction(Sequence::create(DelayTime::create(SKILL2COLDTIME), callfunc, NULL));
		auto to1 = Sequence::createWithTwoActions(ProgressTo::create(0, 100), ProgressTo::create(SKILL2COLDTIME, 0));

		auto shadow = ProgressTimer::create(Sprite::create("skillshadow.png"));
		shadow->setPosition(button->getBoundingBox().size.width / 2, button->getBoundingBox().size.height / 2);
		button->addChild(shadow, 3, 1);
		shadow->setType(ProgressTimer::Type::RADIAL);
		shadow->setReverseProgress(true);
		shadow->runAction(to1);
	}

	
}

void GameScene::skillBtn3OnClick(Ref* Sender){
	Button* button = static_cast<Button*>(Sender);
	if (m_hero->getisDead() == false && m_hero->getStun() == NOTSTUN&&m_hero->m_canControl == true)
	{
		button->setTouchEnabled(false);
		m_hero->addDefenceValue();
		auto callfunc = CallFunc::create([=](){
			button->setTouchEnabled(true);
		});
		button->runAction(Sequence::create(DelayTime::create(SKILL3COLDTIME), callfunc, NULL));
		auto to1 = Sequence::createWithTwoActions(ProgressTo::create(0, 100), ProgressTo::create(SKILL3COLDTIME, 0));

		auto shadow = ProgressTimer::create(Sprite::create("skillshadow.png"));
		shadow->setPosition(button->getBoundingBox().size.width / 2, button->getBoundingBox().size.height / 2);
		button->addChild(shadow, 3, 1);
		shadow->setType(ProgressTimer::Type::RADIAL);
		shadow->setReverseProgress(true);
		shadow->runAction(to1);

		auto to2 = Sequence::createWithTwoActions(ProgressTo::create(0, 100), ProgressTo::create(10.0f, 0));
		auto shadow1 = ProgressTimer::create(Sprite::create("sheld.png"));
		shadow1->setPosition(250,565);
		this->addChild(shadow1, 3, 1);
		shadow1->setType(ProgressTimer::Type::RADIAL);
		shadow1->runAction(to2);
	}
}

void GameScene::update(float dt){
	for (auto monster : m_monsterMgr->getMonsterList())
	{
		monster->targetHero = m_hero;
	}
	if (m_hero->getisDead()==true)
	{
		this->unscheduleUpdate();
		this->scheduleOnce(schedule_selector(GameScene::postLoseMessage), 2.0f);
	}

	if (1==m_hero->getheroExistScreen())
	{
		for (auto monster : m_monsterMgr->getMonsterScreen1List())
		{
			if (monster->getisDead()==false)
			{
				return;
			}
		}
		postScreen1IsClear();
		m_hero->setheroExistScreen(2);
	}
	if (2==m_hero->getheroExistScreen())
	{
		for (auto monster : m_monsterMgr->getMonsterScreen2List())
		{
			if (monster->bossOrNot == true && monster->getisDead() == true){
				this->unscheduleUpdate();
				this->scheduleOnce(schedule_selector(GameScene::postWinMessage), 6.0f);
				return;
			}
			if (monster->getisDead() == false)
			{
				return;
			}
		}
		this->unscheduleUpdate();
		this->scheduleOnce(schedule_selector(GameScene::postWinMessage), 6.0f);
	}
}

void GameScene::postScreen1IsClear(){
	log("====================screen 1 is clear!!!===============");
	m_controller->setBoundary();
}

void GameScene::postWinMessage(float dt){
	RenderTexture* fakeBackground = RenderTexture::create(1280, 720);
	fakeBackground->begin();
	this->getParent()->visit();
	fakeBackground->end();
	auto win = WinLayer::createScene(fakeBackground, m_scenario, m_subscenario);
	Director::getInstance()->pushScene(win);
}

void GameScene::postLoseMessage(float dt){
	RenderTexture* fakeBackground = RenderTexture::create(1280, 720);
	fakeBackground->begin();
	this->getParent()->visit();
	fakeBackground->end();
	User& user = JsonUtility::getInstance()->user;
	user.UserCulHealth = user.UserHealth;
	int money = user.UserGoldsNumber;
	if (money-100*(user.UserLevel+1)<0)
	{
		user.UserGoldsNumber = 0;
	}
	else
	{
		user.UserGoldsNumber = money - 100 * (user.UserLevel + 1);
	}

	auto lose = LoseLayer::createScene(fakeBackground, m_scenario, m_subscenario);
	Director::getInstance()->pushScene(lose);
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameScene::postAttackNotification(float dt){
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(static_cast<int>(EnumMsgType::en_Msg_WantToAttack)));
}

void GameScene::postUseSkillNotification(float dt){
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(static_cast<int>(EnumMsgType::en_Msg_WantToUseSkill)));
}

void GameScene::postBossAttackNotification(float dt){
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(static_cast<int>(EnumMsgType::en_Msg_BossWantToAttack)));
}

void GameScene::postBossUseSkillNotification(float dt){
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(static_cast<int>(EnumMsgType::en_Msg_BossWantToUseSkill)));

}

void GameScene::_popupBagLayer(cocos2d::Ref* sender){
	if (!m_lock)
	{
		m_lock = true;
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_13.c_str());
		RenderTexture* fakeBackground = RenderTexture::create(1280, 720);
		fakeBackground->begin();
		this->getParent()->visit();
		fakeBackground->end();
		auto bag = BagLayer::createScene(fakeBackground);
		BagLayer* layer = static_cast<BagLayer*>(bag->getChildByTag(99));
		layer->setCallbackFunc(this, callfuncN_selector(GameScene::_handlePopupBagLayer));
		Director::getInstance()->pushScene(bag);
	}
}

void GameScene::_popupSetupMenu(cocos2d::Ref* sender){
	RenderTexture* fakeBackground = RenderTexture::create(1280, 720);
	fakeBackground->begin();
	this->getParent()->visit();
	fakeBackground->end();
	Scene* setupLayer = SetupLayer::createScene(fakeBackground, m_isSilence);
	SetupLayer* setup = static_cast<SetupLayer*>(setupLayer->getChildByTag(99));
	setup->setCallbackFunc(this, callfuncN_selector(GameScene::_handlePopupSetupMenu));
	Director::getInstance()->pushScene(setupLayer);
}

void GameScene::_handlePopupSetupMenu(cocos2d::Node* sender){
	if (m_isSilence){
		m_isSilence = false;
	}
	else{
		m_isSilence = true;
	}

}

void GameScene::_handlePopupBagLayer(cocos2d::Node* sender){
	log("outside handle=== %d",sender->getTag());
	if (101 == sender->getTag()){
		__updateHero();
	}
	else{
		__useInventory(static_cast<InventoryEnum>(sender->getTag()));
	}
    m_lock = false;
}

void GameScene::_handlePopupWinLayer(cocos2d::Node* sender){
	
}

void GameScene::__updateHero(){	
	
	m_hero->flashHero();

}

void GameScene::__useInventory(InventoryEnum type){
	switch (type)
	{
	case InventoryEnum::sBlood:
		m_hero->recoverHealth(150.0f);
		break;
	case InventoryEnum::bBlood:
		m_hero->recoverHealth(500.0f);
		break;
	case InventoryEnum::jifengyaoshui:
		m_hero->useUnmatchedMedicines();
		break;
	case InventoryEnum::fengkuangyaoshui:
		m_hero->useFastMedicines();
		break;
	case InventoryEnum::mianyiyaoshui:
		m_hero->useCrazyMedicines();		
		break;
	case InventoryEnum::xianlingyaoshui:
		m_hero->useIntelligenceMedicines();
		break;
	default:
		break;
	}
}

void GameScene::updateBar(float dt){
	m_coin = JsonUtility::getInstance()->user.UserGoldsNumber;
    if(m_label != nullptr){
        if (m_showcoin < m_coin){
            m_showcoin++;
        }
        else if(m_showcoin > m_coin){
            m_showcoin--;
        }
        m_label->setString(std::to_string(m_showcoin));
    }
	int Blood = JsonUtility::getInstance()->user.UserCulHealth;
	int upperBlood = JsonUtility::getInstance()->user.UserHealth;
	bloodNum->setString(std::to_string(Blood) + " / " + std::to_string(upperBlood));
}


Scene* ChooseGameScene::createScene(){
	Scene* scene = Scene::create();
	auto layer = ChooseGameScene::create();
	scene->addChild(layer);
	return scene;
}

bool ChooseGameScene::init(){
	if (!Layer::init())
	{
		return false;
	}

	this->addChild(loadCSB());
	return true;
}

Node* ChooseGameScene::loadCSB(){
	auto rootNode = CSLoader::createNode("scenarioselection/scenarioselection.csb");
	Button* backButton = static_cast<Button*>(rootNode->getChildByTag(27));
	PageView* pageView = static_cast<PageView*>(rootNode->getChildByTag(18));

	Button* scenarioButton1 = static_cast<Button*>(pageView->getPage(0)->getChildByTag(43));
	Button* scenarioButton2 = static_cast<Button*>(pageView->getPage(1)->getChildByTag(44));
	Button* scenarioButton3 = static_cast<Button*>(pageView->getPage(2)->getChildByTag(45));

	//change the default threshold to fit 
	pageView->setCustomScrollThreshold(300.0f);
	pageView->setUsingCustomScrollThreshold(true);

	backButton->addClickEventListener(CC_CALLBACK_1(ChooseGameScene::onBackButtonClicked, this));
	scenarioButton1->addClickEventListener(CC_CALLBACK_1(ChooseGameScene::onScenarioChosenClicked, this));
	scenarioButton2->addClickEventListener(CC_CALLBACK_1(ChooseGameScene::onScenarioChosenClicked, this));
	scenarioButton3->addClickEventListener(CC_CALLBACK_1(ChooseGameScene::onScenarioChosenClicked, this));
	return rootNode;
}

void ChooseGameScene::onBackButtonClicked(cocos2d::Ref* Sender){
	log("===== click back ======");
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_2.c_str());
	auto scene = MenuScene::createScene();
	auto transition = TransitionPageTurn::create(2.0f, scene, true);
	Director::getInstance()->replaceScene(transition);

}

void ChooseGameScene::onScenarioChosenClicked(cocos2d::Ref* Sender){
	Button* button = static_cast<Button*>(Sender);

	log("====scene====%d",button->getTag());
	switch (button->getTag())
	{
	case 43:
		changeToPort();
		break;
	case 44:
		changeToMarket();
		break;
	case 45:
		changeToSewer();
		break;
	default:
		break;
	}
}

void ChooseGameScene::changeToMarket(){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_4.c_str());
	auto scene = SubChooseGameScene::createScene(ScenarioEnum::Market);
	auto transition = TransitionMoveInL::create(2.0f, scene);
	Director::getInstance()->replaceScene(transition);
}

void ChooseGameScene::changeToPort(){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_4.c_str());
	auto scene = SubChooseGameScene::createScene(ScenarioEnum::Port);
	auto transition = TransitionMoveInL::create(2.0f, scene);
	Director::getInstance()->replaceScene(transition);
}

void ChooseGameScene::changeToSewer(){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_4.c_str());
	auto scene = SubChooseGameScene::createScene(ScenarioEnum::Sewer);
	auto transition = TransitionMoveInL::create(2.0f, scene);
	Director::getInstance()->replaceScene(transition);
}



//////////////////////////////////////////////////////////////////////////

SubChooseGameScene::SubChooseGameScene(){

}

SubChooseGameScene::~SubChooseGameScene(){
	
}

Scene* SubChooseGameScene::createScene(ScenarioEnum sceneChoose){
	Scene* scene = Scene::create();
	SubChooseGameScene* scenario = SubChooseGameScene::create(sceneChoose);
	scene->addChild(scenario);
	return scene;
}

SubChooseGameScene* SubChooseGameScene::create(ScenarioEnum sceneChoose){
	SubChooseGameScene* subScene = new SubChooseGameScene();
	if (subScene && subScene->init(sceneChoose))
	{
		subScene->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(subScene);
	}
	return subScene;
}

bool SubChooseGameScene::init(ScenarioEnum sceneChoose){
	if (!Layer::init())
	{
		return false;
	}

	
	__loadCSB(sceneChoose);
	return true;
}

void SubChooseGameScene::__loadCSB(ScenarioEnum sceneChoose)
{
	Node* rootNode = nullptr; 
	switch (sceneChoose)
	{
	case ScenarioEnum::Port:
		rootNode = CSLoader::createNode("port/port.csb");
		break;
	case ScenarioEnum::Market:
		rootNode = CSLoader::createNode("market/market.csb");
		break;
	case ScenarioEnum::Sewer:
		rootNode = CSLoader::createNode("sewer/sewer.csb");
		break;
	default:
		break;
	}
	
	Button* backButton = static_cast<Button*>(rootNode->getChildByTag(5));
	Button* lvButton[3] = { nullptr };
	lvButton[0] = static_cast<Button*>(rootNode->getChildByTag(6));
	lvButton[1] = static_cast<Button*>(rootNode->getChildByTag(7));
	lvButton[2] = static_cast<Button*>(rootNode->getChildByTag(8));
    User& aUser = JsonUtility::getInstance()->user;
	int scene = static_cast<int>(sceneChoose);
	
	for (int i = 0; i < 3; i++)
	{
		if (0 == aUser.Clear_BlockID[scene][i]){
			lvButton[i]->setBright(false);
			lvButton[i]->setEnabled(false);
		}
	}

	backButton->addClickEventListener(CC_CALLBACK_1(SubChooseGameScene::onSubScenarioChooseCallback, this, sceneChoose));
	lvButton[0]->addClickEventListener(CC_CALLBACK_1(SubChooseGameScene::onSubScenarioChooseCallback, this, sceneChoose));
	lvButton[1]->addClickEventListener(CC_CALLBACK_1(SubChooseGameScene::onSubScenarioChooseCallback, this, sceneChoose));
	lvButton[2]->addClickEventListener(CC_CALLBACK_1(SubChooseGameScene::onSubScenarioChooseCallback, this,  sceneChoose));

	this->addChild(rootNode);
}

void SubChooseGameScene::onSubScenarioChooseCallback(cocos2d::Ref* Sender,ScenarioEnum scenario){
	Node* sender = static_cast<Node*>(Sender);
	
	Scene* scene;
		switch (sender->getTag())
	{
		case 5:
			backToChooseGame();
			break;
		case 6:
			SimpleAudioEngine::getInstance()->playEffect(EFFECTS_3.c_str());
			scene = LoadingScene::createScene(scenario, SubScenarioEnum::LV1);
			Director::getInstance()->replaceScene(scene);
			break;
		case 7:
			SimpleAudioEngine::getInstance()->playEffect(EFFECTS_3.c_str());
			scene = LoadingScene::createScene(scenario, SubScenarioEnum::LV2);
			Director::getInstance()->replaceScene(scene);
			break;
		case 8:
			SimpleAudioEngine::getInstance()->playEffect(EFFECTS_3.c_str());
			scene = LoadingScene::createScene(scenario, SubScenarioEnum::LV3);
			Director::getInstance()->replaceScene(scene);
			break;
		default:
			break;
	}
	
		
		
}

void SubChooseGameScene::backToChooseGame(){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_2.c_str());
	auto scene = ChooseGameScene::createScene();
	auto transition = TransitionFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(transition);
}


//////////////////////////////////////////////////////////////////////////

