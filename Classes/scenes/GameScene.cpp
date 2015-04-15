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


USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;

#define COLLIDEMARGIN 30

GameScene::GameScene():
m_hero(nullptr),
m_stick(nullptr),
m_monsterMgr(nullptr){

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

	m_hero = Hero::create();
	m_hero->setPosition(0, 0);

	Sprite* map = static_cast<Sprite*>(rootnode->getChildByTag(80));	
	map->addChild(m_hero,0);
	

	ControllerMoveBase *controller =ControllerMoveBase::create(m_hero, map);
	m_hero->setMoveController(controller);

	__createStickBar();
    
	m_monsterMgr = MonsterManager::createWithLevel(11);
	map->addChild(m_monsterMgr);

	this->scheduleUpdate();	
	this->scheduleOnce(schedule_selector(GameScene::postBossUseSkillNotification), 1.0f);
	//this->scheduleOnce(schedule_selector(GameScene::postUseSkillNotification), 1.0f);
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

void GameScene::attackBtnOnClick(Ref* Sender, ui::Widget::TouchEventType type){

	m_hero->attack();
	//check
	//monsterMgr 
		
}

void GameScene::skillBtn1OnClick(Ref* Sender, ui::Widget::TouchEventType type){

}

void GameScene::skillBtn2OnClick(Ref* Sender, ui::Widget::TouchEventType type){

}

void GameScene::skillBtn3OnClick(Ref* Sender, ui::Widget::TouchEventType type){

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
    Director::getInstance()->pause();
    BagLayer* bagLayer = BagLayer::create();
	bagLayer->setCallbackFunc(this, callfuncN_selector(GameScene::_handlePopupBagLayer));
    this->addChild(bagLayer, 2);
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
	auto transition = TransitionShrinkGrow::create(2.0f, scene);
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
		switch (sender->getTag())
	{
		case 5:
			Director::getInstance()->replaceScene(ChooseGameScene::createScene());
			break;
		case 6:
			Director::getInstance()->replaceScene(GameScene::createScene(scenario, SubScenarioEnum::LV1));
			break;
		case 7:
			Director::getInstance()->replaceScene(GameScene::createScene(scenario, SubScenarioEnum::LV2));
			break;
		case 8:
			Director::getInstance()->replaceScene(GameScene::createScene(scenario, SubScenarioEnum::LV3));
			break;
		default:
			break;
	}
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
	setColor(Color3B::BLACK);
	setOpacity(128);
	return true;
}



//////////////////////////////////////////////////////////////////////////
BagLayer::BagLayer():
m_callback(nullptr),
m_callbackListener(nullptr)
{
	
}

BagLayer::~BagLayer(){

}

bool BagLayer::init(){
	if (!PopupLayer::init())
	{
		return false;
	}
	//delegate the Touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(BagLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(BagLayer::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(BagLayer::onTouchMoved, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
    
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	__loadPicFromCSB();
	if (!__initFromFile())
	{
		return false;
	}
	

	return true;
}

bool BagLayer::__initFromFile(){
    User aUser = JsonUtility::getInstance()->getUser();
    for (int i = 0; i < 24; i++) {
        
        if(-1 != aUser.Equip[i].ID){
            Equipment* aEquipment = Equipment::create();
            
            aEquipment->setBlood(aUser.Equip[i].Blood);
            aEquipment->setIntelligence(aUser.Equip[i].Intelligence);
            aEquipment->setEquipmentID(aUser.Equip[i].ID);
            aEquipment->setEquipmentStyle(static_cast<EquipmentType>(aUser.Equip[i].Style));
            aEquipment->setDenfense(aUser.Equip[i].Defense);
            aEquipment->setMoveRate(aUser.Equip[i].MoveRate);
            aEquipment->setAttack(aUser.Equip[i].Attack);
            aEquipment->setAttackRate(aUser.Equip[i].AttackRate);
            aEquipment->setUsed(aUser.Equip[i].Used);
            m_equipmentVec.pushBack(aEquipment);
            
        }
        else{
            
            break;
        }
    }
    log("vec size ====== %zd",m_equipmentVec.size());
	return true;
}
void BagLayer::setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun){
	m_callback = callFun;
	m_callbackListener = target;
}

void BagLayer::__loadPicFromCSB(){
	Node* baglayer = static_cast<Node*>(CSLoader::createNode("bag/bag.csb"));
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
}

void BagLayer::onEquipmentClickedListener(cocos2d::Ref* sender){
	Node* node = static_cast<Node*>(sender);

	if (m_callback && m_callbackListener)
	{
		(m_callbackListener->*m_callback)(node);
	}
}

//////////////////////////////////////////////////////////////////////////

DetailLayer::DetailLayer():
m_callback(nullptr),
m_callbackListener(nullptr)
{

}

DetailLayer::~DetailLayer(){

}

void DetailLayer::__loadPicFromCSB(){

}

bool DetailLayer::init(){
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
