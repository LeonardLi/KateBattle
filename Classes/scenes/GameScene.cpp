#include "GameScene.h"
#include "MenuScene.h"
#include "JoyStick.h"
#include "Hero.h"
#include "cocos2d.h"
#include "ControllerMoveBase.h"
#include "JsonUtility.h"
#include "Monster.h"
#include "MonsterManager.h"
#include "StateAttack.h"
#include "StateUseSkill.h"
#include "MonsterFSM.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"
#include "SoundsController.h"
#include "SoundsDef.h"
#include <stdio.h>
#include "Inventory.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;

#define COLLIDEMARGIN 30

GameScene::GameScene():
m_hero(nullptr),
m_stick(nullptr),
m_monsterMgr(nullptr),
m_map(nullptr)
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

	auto rootnode = loadCSB(scenario, subscenario);

	this->addChild(rootnode, 0);
	
	auto controllayer = loadControlLayer();
	this->addChild(controllayer, 1);

	auto attackButton = static_cast<Button*>(controllayer->getChildByTag(10));
	attackButton->addClickEventListener(CC_CALLBACK_1(GameScene::attackBtnOnClick,this));
	
	auto SkillButton1 = static_cast<Button*>(controllayer->getChildByTag(12));
	SkillButton1->addClickEventListener(CC_CALLBACK_1(GameScene::skillBtn1OnClick, this));

	auto SkillButton2 = static_cast<Button*>(controllayer->getChildByTag(13));
	SkillButton2->addClickEventListener(CC_CALLBACK_1(GameScene::skillBtn2OnClick, this));

	auto SkillButton3 = static_cast<Button*>(controllayer->getChildByTag(14));
	SkillButton3->addClickEventListener(CC_CALLBACK_1(GameScene::skillBtn3OnClick, this));

	m_hero = Hero::create();
	m_hero->setPosition(100, 100);

	m_map = static_cast<Sprite*>(rootnode->getChildByTag(80));	
	m_map->addChild(m_hero, 0);
	

	ControllerMoveBase *controller = ControllerMoveBase::create(m_hero, m_map);
	m_hero->setMoveController(controller);

	__createStickBar();
    
	m_monsterMgr = MonsterManager::createWithLevel(11);
	m_hero->m_heroMonsterList = m_monsterMgr->m_showedMonsterList;
	m_map->addChild(m_monsterMgr);

	this->scheduleUpdate();	
	//this->scheduleOnce(schedule_selector(GameScene::postAttackNotification), 1.0f);
	this->scheduleOnce(schedule_selector(GameScene::postBossAttackNotification), 1.0f);
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

	setupButton->addClickEventListener(CC_CALLBACK_1(GameScene::_popupSetupMenu, this));
	bagButton->addClickEventListener(CC_CALLBACK_1(GameScene::_popupBagLayer, this));
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
	if (m_hero->getisDead() == false&&m_hero->getStun()==NOTSTUN)
	{
		Button* button = static_cast<Button*>(Sender);
		button->setTouchEnabled(false);
		m_hero->attack();
		auto callfunc = CallFunc::create([=](){
			button->setTouchEnabled(true);
		});
		button->runAction(Sequence::create(DelayTime::create(1.0f), callfunc, NULL));
	}
		
}

void GameScene::skillBtn1OnClick(Ref* Sender){

}

void GameScene::skillBtn2OnClick(Ref* Sender){
	if (m_hero->getisDead() == false && m_hero->getStun() == NOTSTUN)
	{
		Button* button = static_cast<Button*>(Sender);
		button->setTouchEnabled(false);
		m_hero->blink();
		auto callfunc = CallFunc::create([=](){
			button->setTouchEnabled(true);
		});
		button->runAction(Sequence::create(DelayTime::create(2.0f), callfunc, NULL));
	}
}

void GameScene::skillBtn3OnClick(Ref* Sender){

}

void GameScene::update(float dt){
	
	
	for (auto monster : m_monsterMgr->getMonsterList())
	{
		monster->heroLocation = m_hero->getPosition();
		monster->targetHero = m_hero;
		
		/*Rect monsterRect = monster->getBoundingBox();
		Rect monsterCollideRect = Rect(monsterRect.origin.x + COLLIDEMARGIN, monsterRect.origin.y + COLLIDEMARGIN,
			monsterRect.size.width - 2 * COLLIDEMARGIN, monsterRect.size.height - 2 * COLLIDEMARGIN);
		
		Rect heroRect = m_hero->getBoundingBox();
		if (monsterCollideRect.intersectsRect(heroRect)&&m_hero->m_canControl==true)
		{
			m_hero->heroNotControl(0.5f);
			
			m_hero->runAction(MoveBy::create(0.5, Vec2((m_hero->getPositionX()-monster->getPositionX())/2, (m_hero->getPositionY()-monster->getPositionY())/2)));

			log("collide");
		}*/

	}
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
	//this->schedule(schedule_selector(GameScene::postUseSkillNotification), 1.0f);
}

void GameScene::postUseSkillNotification(float dt){
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(static_cast<int>(EnumMsgType::en_Msg_WantToUseSkill)));
	//this->scheduleOnce(schedule_selector(GameScene::postAttackNotification), 5.0f);

}

void GameScene::postBossAttackNotification(float dt){
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(static_cast<int>(EnumMsgType::en_Msg_BossWantToAttack)));
	//this->schedule(schedule_selector(GameScene::postUseSkillNotification), 1.0f);
}

void GameScene::postBossUseSkillNotification(float dt){
	NotificationCenter::getInstance()->postNotification(StringUtils::toString(static_cast<int>(EnumMsgType::en_Msg_BossWantToUseSkill)));
	//this->scheduleOnce(schedule_selector(GameScene::postAttackNotification), 5.0f);

}

void GameScene::_popupBagLayer(cocos2d::Ref* sender){
	RenderTexture* fakeBackground = RenderTexture::create(1280, 720);
	fakeBackground->begin();
	this->getParent()->visit();
	fakeBackground->end();	
	auto bag = BagLayer::createScene(fakeBackground);
	BagLayer* layer = static_cast<BagLayer*>(bag->getChildByTag(99));
	layer->setCallbackFunc(this, callfuncN_selector(GameScene::_handlePopupBagLayer));
	Director::getInstance()->pushScene(bag);
}

void GameScene::_popupSetupMenu(cocos2d::Ref* sender){
	Director::getInstance()->pause();
	SetupLayer* setupLayer = SetupLayer::create();
	this->addChild(setupLayer, 2);
}

void GameScene::_popupWinLayer(cocos2d::Ref* sender){
	Director::getInstance()->pause();
	WinLayer *winLayer = WinLayer::create();
	this->addChild(winLayer, 2);
}

////
void GameScene::_handlePopupSetupmMenu(cocos2d::Node* sender){

}

void GameScene::_handlePopupBagLayer(cocos2d::Node* sender){
	log("outside handle=== %d",sender->getTag());
}

void GameScene::_handlePopupWinLayer(cocos2d::Node* sender){
	
}

//////////////////////////////////////////////////////////////////////////

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
		Director::getInstance()->replaceScene(SubChooseGameScene::createScene(ScenarioEnum::Port));
		break;
	case 44:
		Director::getInstance()->replaceScene(SubChooseGameScene::createScene(ScenarioEnum::Market));
		break;
	case 45:
		Director::getInstance()->replaceScene(SubChooseGameScene::createScene(ScenarioEnum::Sewer));
		break;
	default:
		break;
	}
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
	User aUser = JsonUtility::getInstance()->getUser();
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
			scene = ChooseGameScene::createScene();
			break;
		case 6:
			scene = GameScene::createScene(scenario, SubScenarioEnum::LV1);
			SoundsController::getInstance()->stopBackgroundMusic(scenario);
			break;
		case 7:
			scene = GameScene::createScene(scenario, SubScenarioEnum::LV2);
			SoundsController::getInstance()->stopBackgroundMusic(scenario);
			break;
		case 8:
			scene = GameScene::createScene(scenario, SubScenarioEnum::LV3);
			SoundsController::getInstance()->stopBackgroundMusic(scenario);
			break;
		default:
			break;
	}
		auto transition = TransitionFadeBL::create(2.f, scene);
		Director::getInstance()->replaceScene(transition);
}

//////////////////////////////////////////////////////////////////////////
void PopupLayer::onEnter(){
    Layer::onEnter();
}

void PopupLayer::onExit(){
    Layer::onExit();
}

bool PopupLayer::init(){
	log("========= PopupLayer ========== init");
	if (!LayerColor::init())
	{
		return false;
	}
	//cover other layer
	//setColor(Color3B::BLACK);
	//setOpacity(128);
	return true;
}

void PopupLayer::__loadPicFromCSB(){
}

//////////////////////////////////////////////////////////////////////////
BagLayer::BagLayer():
m_callback(nullptr),
m_callbackListener(nullptr)
{
	
}

BagLayer::~BagLayer(){

}

Scene* BagLayer::createScene(cocos2d::RenderTexture* sqr){
	Scene* scene = Scene::create();
	BagLayer* baglayer = BagLayer::create();
	baglayer->setTag(99);
	scene->addChild(baglayer,1);

	Sprite* fakeSprite = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	fakeSprite->setPosition(VisibleRect::center());
	fakeSprite->setFlippedY(true);
	fakeSprite->setColor(Color3B::GRAY);
	scene->addChild(fakeSprite,0);
	return scene;
}

BagLayer* BagLayer::create(){
	BagLayer* instance = new BagLayer();
	if (instance && instance->init())
	{
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return instance;
}

bool BagLayer::init(){
	if (!PopupLayer::init())
	{
		return false;
	}
	if (!__initFromFile())
	{
		return false;
	}
	//delegate the Touch event
	m_listener = EventListenerTouchOneByOne::create();
	m_listener->setSwallowTouches(true);
	m_listener->onTouchBegan = CC_CALLBACK_2(BagLayer::onTouchBegan, this);
	m_listener->onTouchEnded = CC_CALLBACK_2(BagLayer::onTouchEnded, this);
	m_listener->onTouchMoved = CC_CALLBACK_2(BagLayer::onTouchMoved, this);
	m_dispatcher = Director::getInstance()->getEventDispatcher();
    
	m_dispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

	__loadPicFromCSB();

	

	return true;
}

bool BagLayer::__initFromFile(){
	m_user = JsonUtility::getInstance()->getUser();
    for (int i = 0; i < 24; i++) {        
        if(-1 != m_user.Equip[i].ID){
			Equipment* aEquipment = __matchPic(m_user.Equip[i].ID);
			aEquipment->setBlood(m_user.Equip[i].Blood);
			aEquipment->setIntelligence(m_user.Equip[i].Intelligence);
			aEquipment->setEquipmentID(m_user.Equip[i].ID);
			aEquipment->setEquipmentStyle(static_cast<EquipmentType>(m_user.Equip[i].Style));
			aEquipment->setDenfense(m_user.Equip[i].Defense);
			aEquipment->setMoveRate(m_user.Equip[i].MoveRate);
			aEquipment->setAttack(m_user.Equip[i].Attack);
			aEquipment->setAttackRate(m_user.Equip[i].AttackRate);
			aEquipment->setUsed(m_user.Equip[i].Used);
            m_equipmentVec.pushBack(aEquipment);
            
        }
        else{
            
            break;
        }
    }
    //log("vec size ============================ %zd",m_equipmentVec.size());
	return true;
}

Equipment* BagLayer::__matchPic(int ID){
	std::string filename;
	switch (ID)
	{
	case 0:
		filename = "bag/equ_11.png";
		break;
	case 1:
		filename = "bag/equ_12.png";
		break;
	case 2:
		filename = "bag/equ_13.png";
		break;
	case 3:
		filename = "bag/equ_21.png";
		break;
	case 4:
		filename = "bag/equ_22.png";
		break;
	case 5:
		filename = "bag/equ_23.png";
		break;
	case 6:
		filename = "bag/equ_31.png";
		break;
	case 7:
		filename = "bag/equ_32.png";
		break;
	case 8:
		filename = "bag/equ_33.png";
		break;
	case 9:
		filename = "bag/equ_41.png";
		break;
	case 10:
		filename = "bag/equ_42.png";
		break;
	case 11:
		filename = "bag/equ_43.png";
		break;

		break;
	default:
		break;
	}
	Equipment* eq = Equipment::create(filename,filename,filename);
	return eq;
}

void BagLayer::setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun){
	m_callback = callFun;
	m_callbackListener = target;
}

void BagLayer::__loadPicFromCSB(){
	Node* baglayer = static_cast<Node*>(CSLoader::createNode("bag/bag.csb"));
	Button* backButton = static_cast<Button*>(baglayer->getChildByTag(76));
	backButton->addClickEventListener(CC_CALLBACK_1(BagLayer::onBackButtonClickListener, this));
	
	ImageView* equip[24] = { nullptr };
	int i = 142;
	for (Equipment* eq : m_equipmentVec){
		equip[i - 142] = static_cast<ImageView*>(baglayer->getChildByTag(140)->getChildByTag(141)->getChildByTag(i));
        eq->addClickEventListener(CC_CALLBACK_1(BagLayer::onEquipmentClickedListener, this));
        eq->setScale(1.2f);
        eq->setPosition(Vec2(91.5f,81.5f));
		eq->setTag(i);
		equip[i - 142]->addChild(eq);
		i++;
	}

	Button* inventory[6] = { nullptr };
	for (int j = 0; j < 6; j++){
		inventory[j] = static_cast<Button*>(baglayer->getChildByTag(139)->getChildByTag(301 + j));
        if(m_user.ToolID[j] != 0){
            inventory[j]->setBright(true);
			inventory[j]->setEnabled(true);
            Text* text = inventory[j]->getChildByName<Text*>("text");
            char number[2];
            std::sprintf(number,"%d",m_user.ToolID[j]);
            text->setString(number);
            inventory[j]->addClickEventListener(CC_CALLBACK_1(BagLayer::onInventoryClickedListener, this));
        }
        else
        {
			inventory[j]->setBright(false);
            Text* text = inventory[j]->getChildByName<Text*>("text");
            text->setString(" ");
            
        }
		
	}


	this->addChild(baglayer);
}

bool BagLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	return true;
}

void BagLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){
}

void BagLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
}

void BagLayer::onEnter(){
	log("========= BagLayer ========== onEnter");
	PopupLayer::onEnter();

}

void BagLayer::onInventoryClickedListener(cocos2d::Ref* sender){
	Node* node = static_cast<Node*>(sender);

	if (m_callback && m_callbackListener)
	{
		(m_callbackListener->*m_callback)(node);
	}
	log("inside========= %d",node->getTag());
    SetupLayer* layer = SetupLayer::create();
    //this->addChild(layer, 2);
	DetailLayer* detail = DetailLayer::create(InventoryEnum::bBlood);
	//detail->setCallbackFunc(this, callfuncN_selector(BagLayer::__handleInventoryDetailLayer));
	this->addChild(detail, 2);

}

void BagLayer::onEquipmentClickedListener(cocos2d::Ref* sender){
	Equipment* node = static_cast<Equipment*>(sender);

	if (m_callback && m_callbackListener)
	{
		(m_callbackListener->*m_callback)(node);
	}
    log("Equitment id====== %d",node->getEquipmentID());

	//DetailLayer* detail = DetailLayer::create(node);
	//this->addChild(detail);
}

void BagLayer::onBackButtonClickListener(Ref* sender){
	Director::getInstance()->popScene();
}


void BagLayer::__handleEquipmentDetailLayer(cocos2d::Node* sender){

}

void BagLayer::__handleInventoryDetailLayer(cocos2d::Node* sender){
	__playAnimation();
}

void BagLayer::__playAnimation(){
	Label* label = Label::create();
	label->setString("Hello");
	label->setPosition(Vec2(640,360));
	FadeIn* action1 = FadeIn::create(1.0f);
	MoveTo* action2 = MoveTo::create(1.0f,Vec2(640,365));
	FadeOut* action3 = FadeOut::create(1.0f);
	Sequence* seq1 = Sequence::create(action2, action3, NULL);
	Sequence* seq2 = Sequence::create(action1, seq1, NULL);
	label->runAction(seq2);
}
//////////////////////////////////////////////////////////////////////////
DetailLayer::DetailLayer():
m_callback(nullptr),
m_callbackListener(nullptr)
{

}

DetailLayer::~DetailLayer(){

}

DetailLayer* DetailLayer::create(Equipment* equipment)
{
    DetailLayer* instance = new (std::nothrow)DetailLayer;
    if (instance && instance->init(equipment)) {
        instance->autorelease();
        return instance;
    }
    CC_SAFE_DELETE(instance);
    return instance;
}

DetailLayer* DetailLayer::create(InventoryEnum type){
	DetailLayer* instance = new (std::nothrow)DetailLayer;
	if (instance && instance->init(type))
	{
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return instance;
}

void DetailLayer::__loadPicFromCSB(Equipment* eq){
	Node* rootNode = CSLoader::createNode("equ/equ_on.csb");
	this->addChild(rootNode);
}

void DetailLayer::__loadPicFromCSB(InventoryEnum type){
	Node* rootNode = CSLoader::createNode("inventory/Node.csb");
    rootNode->setPosition(VisibleRect::center());
	this->addChild(rootNode);

	Button* Use = static_cast<Button*>(rootNode->getChildByTag(12));
	//Use->setEnabled(true);
	Use->addClickEventListener(CC_CALLBACK_1(DetailLayer::onUseButtonClicked, this));


	switch (type)
	{
	case InventoryEnum::sBlood:
		break;
	case InventoryEnum::bBlood:
		break;
	case InventoryEnum::jifengyaoshui:
		break;
	case InventoryEnum::fengkuangyaoshui:
		break;
	case InventoryEnum::mianyiyaoshui:
		break;
	case InventoryEnum::xianlingyaoshui:
		break;
	default:
		break;
	}
}

bool DetailLayer::init(Equipment* eq){
	if (!PopupLayer::init())
	{
		return false;
	}
	//delegate the Touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(DetailLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(DetailLayer::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(DetailLayer::onTouchMoved, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	__loadPicFromCSB(eq);
	return true;
}

bool DetailLayer::init(InventoryEnum type){
	if (!PopupLayer::init())
	{
		return false;
	}
	//delegate the Touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(DetailLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(DetailLayer::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(DetailLayer::onTouchMoved, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
	__loadPicFromCSB(type);
	return true;

}

void DetailLayer::setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun){
	m_callbackListener = target;
	m_callback = callFun;
}

bool DetailLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	return true;
}

void DetailLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){

}

void DetailLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){

}

void DetailLayer::onEnter(){

}

void DetailLayer::onUseButtonClicked(cocos2d::Ref* sender){
	log("====================== use ===============");
}
//////////////////////////////////////////////////////////////////////////

WinLayer::WinLayer():
m_callback(nullptr),
m_callbackListener(nullptr)
{
	
}

WinLayer::~WinLayer(){

}

void WinLayer::__loadPicFromCSB(){

}

bool WinLayer::init(){
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
	
}
//////////////////////////////////////////////////////////////////////////

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
