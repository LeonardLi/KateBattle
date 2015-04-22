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

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));    
    auto popupItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::_popupEquipmentMenu, this));
    



    // create menu, it's an autorelease object
  

    /////////////////////////////

	auto rootnode = loadCSB("gangkou1/gangkou1.csb");
	this->addChild(rootnode, 0);
	
	m_hero = Hero::create(Sprite::create("wolf.png"));
	m_hero->setPosition(100, 100);

	Sprite* map = static_cast<Sprite*>(rootnode->getChildByTag(80));	
	map->addChild(m_hero,0);
	
	ControllerMoveBase *controller =ControllerMoveBase::create(m_hero, map);
	m_hero->setMoveController(controller);

	__createStickBar();
    
	m_monsterMgr = MonsterManager::createWithLevel(11);
	map->addChild(m_monsterMgr);

	this->scheduleUpdate();	
	//this->scheduleOnce(schedule_selector(GameScene::postBossAttackNotification), 1.0f);
	this->scheduleOnce(schedule_selector(GameScene::postBossUseSkillNotification), 1.0f);
    return true;
}

Node* GameScene::loadCSB(std::string csbfile){
	Node* rootNode = CSLoader::createNode(csbfile.c_str());
	ActionTimeline* actionTime = CSLoader::createTimeline(csbfile);
	actionTime->gotoFrameAndPlay(0, 60, true);
	rootNode->runAction(actionTime);
	return rootNode;
}

void GameScene::onDirectionChange(JoystickEnum direction){
	m_hero->ChangeDirection(direction);
}

void GameScene::__createStickBar(){
	m_stick = Joystick::create("directioncontrol1.png", "directioncontrol2.png");
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

void GameScene::_popupEquipmentMenu(cocos2d::Ref* sender){
    Director::getInstance()->pause();
    EquipmentLayer* eqLayer = EquipmentLayer::create();
	eqLayer->setCallbackFunc(this, callfuncN_selector(GameScene::_handlePopupEquipmentMenu));
    this->addChild(eqLayer, 2);
}

void GameScene::_popupSetupMenu(cocos2d::Ref* sender){
	Director::getInstance()->pause();
	SetupLayer* setupLayer = SetupLayer::create();
	this->addChild(setupLayer, 2);
}

void GameScene::_popupInventoryMenu(cocos2d::Ref* sender){
	Director::getInstance()->pause();
	InventoryLayer* invLayer = InventoryLayer::create();
	this->addChild(invLayer, 2);
}

void GameScene::_popupWinLayer(cocos2d::Ref* sender){
	Director::getInstance()->pause();
	WinLayer *winLayer = WinLayer::create();
	this->addChild(winLayer, 2);
}

void GameScene::_handlePopupEquipmentMenu(cocos2d::Node* sender){
	log("GameScene: %d",sender->getTag());
}

void GameScene::_handlePopupSetupmMenu(cocos2d::Node* sender){

}

void GameScene::_handlePopupInventoryMenu(cocos2d::Node* sender){

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
	switch (sceneChoose)
	{
	case ScenarioEnum::Port:
		__loadCSB("port/port.csb");
		break;
	case ScenarioEnum::Market:
		__loadCSB("market/market.csb");
		break;
	case ScenarioEnum::Sewer:
		__loadCSB("sewer/sewer.csb");
		break;
	default:
		break;
	}
	

	return true;
}

void SubChooseGameScene::__loadCSB(std::string scbfile)	{
	Node* rootNode = CSLoader::createNode(scbfile);
	Button* backButton = static_cast<Button*>(rootNode->getChildByTag(5));
	Button* lv1Button = static_cast<Button*>(rootNode->getChildByTag(6));
	Button* lv2Button = static_cast<Button*>(rootNode->getChildByTag(7));
	Button* lv3Button = static_cast<Button*>(rootNode->getChildByTag(8));

	backButton->addClickEventListener(CC_CALLBACK_1(SubChooseGameScene::onSubScenarioChooseCallback, this));
	lv1Button->addClickEventListener(CC_CALLBACK_1(SubChooseGameScene::onSubScenarioChooseCallback, this));
	lv2Button->addClickEventListener(CC_CALLBACK_1(SubChooseGameScene::onSubScenarioChooseCallback, this));
	lv3Button->addClickEventListener(CC_CALLBACK_1(SubChooseGameScene::onSubScenarioChooseCallback, this));

	this->addChild(rootNode);
}

void SubChooseGameScene::onSubScenarioChooseCallback(cocos2d::Ref* Sender){
	Node* sender = static_cast<Node*>(Sender);
		switch (sender->getTag())
	{
		case 5:
			Director::getInstance()->replaceScene(ChooseGameScene::createScene());
			break;
		case 6:
			Director::getInstance()->replaceScene(GameScene::createScene());
			break;
		case 7:

			break;
		case 8:
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

EquipmentLayer::EquipmentLayer():
m_callback(nullptr),
m_callbackListener(nullptr)
{
}

EquipmentLayer::~EquipmentLayer(){
 
}

void EquipmentLayer::loadPicFromCSB(std::string csbfile){
    auto rootNode = CSLoader::createNode(csbfile);
    rootNode->setPosition(VisibleRect::center());
    this->addChild(rootNode, 2);
    Button* button = static_cast<Button*>(rootNode->getChildByName("Button"));
    button->addClickEventListener(CC_CALLBACK_1(EquipmentLayer::_ClickCallBack, this));   
}

bool EquipmentLayer::init(){
	log("========= EquipmentLayer ========== init");
    if (!PopupLayer::init()) {
        return false;
    } 
	//delegate the Touch event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(EquipmentLayer::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(EquipmentLayer::onTouchEnded, this);
    listener->onTouchMoved = CC_CALLBACK_2(EquipmentLayer::onTouchMoved, this);
    auto dispatcher = Director::getInstance()->getEventDispatcher();    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    loadPicFromCSB("Node.csb");
	
	return true;
}

void EquipmentLayer::onEnter(){
    log("========= EquipmentLayer ========== onEnter");
    PopupLayer::onEnter();

    Action* popupMenu = Sequence::create(ScaleTo::create(0.0f, 0.0f)
                                           , ScaleTo::create(0.06f, 1.05f)
                                           , ScaleTo::create(0.08f, 0.95f)
                                           , ScaleTo::create(0.08f, 1.0f)
                                           , NULL);
    this->runAction(popupMenu);
}

void EquipmentLayer::onExit(){
    PopupLayer::onExit();
}

void EquipmentLayer::_ClickCallBack(cocos2d::Ref* sender){
    
    Node* node = dynamic_cast<Node*>(sender);
    
    log("click the button %d",node->getTag());
    
    if(m_callbackListener && m_callback){
        (m_callbackListener->*m_callback)(node);
    }
}

void EquipmentLayer::setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun){
    m_callbackListener = target;
    m_callback = callFun;
}

bool EquipmentLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
    return true;
}

void EquipmentLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){

}

void EquipmentLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){

}

//////////////////////////////////////////////////////////////////////////

InventoryLayer::InventoryLayer():
m_callback(nullptr),
m_callbackListener(nullptr)
{

}

InventoryLayer::~InventoryLayer(){

}

void InventoryLayer::loadPicFromCSB(std::string csbfile){
	
}

bool InventoryLayer::init(){
	if (!PopupLayer::init())
	{
		return false;
	}
	//delegate the Touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(InventoryLayer::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(InventoryLayer::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(InventoryLayer::onTouchMoved, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void InventoryLayer::setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun){
	m_callbackListener = target;
	m_callback = callFun;
}

bool InventoryLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	return true;
}

void InventoryLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){
	
}

void InventoryLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
	
}

void InventoryLayer::onEnter(){
	log("========= InventoryLayer ========== onEnter");
	PopupLayer::onEnter();

	Action* popupMenu = Sequence::create(ScaleTo::create(0.0f, 0.0f)
		, ScaleTo::create(0.06f, 1.05f)
		, ScaleTo::create(0.08f, 0.95f)
		, ScaleTo::create(0.08f, 1.0f)
		, NULL);
	this->runAction(popupMenu);
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

	return true;
}

void BagLayer::setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun){
	m_callback = callFun;
	m_callbackListener = target;
}

void BagLayer::loadPicFromCSB(std::string){
	
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

	Action* popupMenu = Sequence::create(ScaleTo::create(0.0f, 0.0f)
		, ScaleTo::create(0.06f, 1.05f)
		, ScaleTo::create(0.08f, 0.95f)
		, ScaleTo::create(0.08f, 1.0f)
		, NULL);
	this->runAction(popupMenu);
}
//////////////////////////////////////////////////////////////////////////

WinLayer::WinLayer():
m_callback(nullptr),
m_callbackListener(nullptr)
{
	
}

WinLayer::~WinLayer(){

}

void WinLayer::loadPicFromCSB(std::string csbfile){

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
	loadPicFromCSB("Node.csb");
	return true;
}
void SetupLayer::loadPicFromCSB(std::string csbfile){
	Node* rootNode = CSLoader::createNode(csbfile);
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
}
