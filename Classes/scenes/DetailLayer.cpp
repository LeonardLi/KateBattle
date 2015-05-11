#include "DetailLayer.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cocos2d.h"
#include "VisibleRect.h"
#include "Inventory.h"
#include "Equipment.h"
#include "JsonUtility.h"
#include "SoundsDef.h"
#include "SoundsController.h"

USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;
DetailLayer::DetailLayer()
{

}

DetailLayer::~DetailLayer(){

}

DetailLayer* DetailLayer::create(Equipment* equipment)
{
	DetailLayer* instance = new (std::nothrow)DetailLayer();
	if (instance && instance->init(equipment)) {
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return instance;
}

DetailLayer* DetailLayer::create(InventoryEnum type){
	DetailLayer* instance = new (std::nothrow)DetailLayer();
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
	Button* backButton = static_cast<Button*>(rootNode->getChildByTag(2)->getChildByTag(8));
    Button* Equip = static_cast<Button*>(rootNode->getChildByTag(2)->getChildByTag(7));
    Button* sell = static_cast<Button*>(rootNode->getChildByTag(2)->getChildByTag(195));
    ImageView* image = static_cast<ImageView*>(rootNode->getChildByTag(2)->getChildByTag(3));
    Text* name = static_cast<Text*>(rootNode->getChildByTag(2)->getChildByTag(6));
    Text* intro = static_cast<Text*>(rootNode->getChildByTag(2)->getChildByTag(4));
    Text* price = static_cast<Text*>(rootNode->getChildByTag(2)->getChildByTag(197));

	Text* speed = static_cast<Text*>(rootNode->getChildByTag(2)->getChildByTag(194));
	Text* attackValue = static_cast<Text*>(rootNode->getChildByTag(2)->getChildByTag(192));
	Text* Hp = static_cast<Text*>(rootNode->getChildByTag(2)->getChildByTag(189));
	Text* defence = static_cast<Text*>(rootNode->getChildByTag(2)->getChildByTag(190));
	Text* intelligence = static_cast<Text*>(rootNode->getChildByTag(2)->getChildByTag(191));
	Text* attackRate = static_cast<Text*>(rootNode->getChildByTag(2)->getChildByTag(193));
	

    Equip->addClickEventListener(CC_CALLBACK_1(DetailLayer::onEquipBuntonClicked, this));
	backButton->addClickEventListener(CC_CALLBACK_1(DetailLayer::onBackupButtonClicked, this));
    sell->addClickEventListener(CC_CALLBACK_1(DetailLayer::onSaleButtonClicked, this));
    
	EquipmentInfo info = JsonUtility::getInstance()->getEquipment(eq->getEquipmentID());
    image->loadTexture(info.EquipAddress);
    name->setString(info.EquipName);
    intro->setString(info.EquipInfo);
	intro->ignoreContentAdaptWithSize(false);
	intro->setContentSize(Size(110.0f, 130.0f));
	intro->setPosition(Vec2(218,280));
	speed->setString(std::to_string((int)eq->getMoveRate()));
	attackRate->setString(std::to_string((int)eq->getAttackRate()));
	Hp->setString(std::to_string((int)eq->getBlood()));
	defence->setString(std::to_string((int)eq->getDenfense()));
	intelligence->setString(std::to_string((int)eq->getIntelligence()));
	attackValue->setString(std::to_string((int)eq->getAttack()));
    price->setString(std::to_string(JsonUtility::getInstance()->getEquipment(m_equipment->getEquipmentID()).EquipPrice));

    this->addChild(rootNode);
}

void DetailLayer::__loadPicFromCSB(InventoryEnum type){
	Node* rootNode = CSLoader::createNode("inventorytest/inventorytest.csb");
	Button* UseButton = static_cast<Button*>(rootNode->getChildByTag(2)->getChildByTag(6));
	Button* BackupButton = static_cast<Button*>(rootNode->getChildByTag(2)->getChildByTag(7));
	UseButton->addClickEventListener(CC_CALLBACK_1(DetailLayer::onUseButtonClicked, this));
	BackupButton->addClickEventListener(CC_CALLBACK_1(DetailLayer::onBackupButtonClicked, this));
	Text* name = static_cast<Text*>(rootNode->getChildByTag(2)->getChildByTag(4));
	Text* intro = static_cast<Text*>(rootNode->getChildByTag(2)->getChildByTag(5));
	ImageView* avatar = static_cast<ImageView*>(rootNode->getChildByTag(2)->getChildByTag(3));



	Tool inventory = JsonUtility::getInstance()->getTool(static_cast<int>(type));
	intro->ignoreContentAdaptWithSize(false);
	intro->setContentSize(Size(200.0f,115.0f));
	intro->setPosition(Vec2(225.0f,105.0f));
	name->setString(inventory.ToolName);
	intro->setString(inventory.ToolInfo);
	avatar->loadTexture(inventory.ToolAddress);
	this->addChild(rootNode);
}

bool DetailLayer::init(Equipment* eq){
	if (!LayerColor::init())
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
	m_equipment = eq;
	__loadPicFromCSB(eq);
	return true;
}

bool DetailLayer::init(InventoryEnum type){
	if (!LayerColor::init())
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
    m_type = type;
	__loadPicFromCSB(type);
	return true;

}

bool DetailLayer::init(){
	if (!LayerColor::init())
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


	__loadPicFromCSB(InventoryEnum::bBlood);
	return true;
}

bool DetailLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	return true;
}

void DetailLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){

}

void DetailLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){

}

void DetailLayer::onUseButtonClicked(cocos2d::Ref* sender){
	//log("====================== use ===============");
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_11.c_str());
	int i = JsonUtility::getInstance()->user.ToolID[static_cast<int>(m_type)];
	JsonUtility::getInstance()->user.ToolID[static_cast<int>(m_type)] = i - 1;
	Node* node = static_cast<Node*>(sender);
	node->setTag(static_cast<int>(m_type));

	if (m_callback && m_callbackListener)
	{
		(m_callbackListener->*m_callback)(node);
	}


	this->removeFromParent();

}

void DetailLayer::onEquipBuntonClicked(Ref* sender){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_12.c_str());
	User& user = JsonUtility::getInstance()->user;
	if (user.Equip[m_equipment->getIndex()].Used){
		user.Equip[m_equipment->getIndex()].Used = false;
		m_equipment->setUsed(false);
	}
	else
	{
		user.Equip[m_equipment->getIndex()].Used = true;
		m_equipment->setUsed(true);
	}


	if (m_callback && m_callbackListener)
	{
		(m_callbackListener->*m_callback)(dynamic_cast<Node*>(m_equipment));
	}
	this->removeFromParent();
}

void DetailLayer::onBackupButtonClicked(Ref* sender){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_2.c_str());
	this->removeFromParent();
}

void DetailLayer::onSaleButtonClicked(Ref* sender){
    User& user = JsonUtility::getInstance()->user;
    
    user.Equip[m_equipment->getIndex()].ID = -1;
    user.UserGoldsNumber = user.UserGoldsNumber + JsonUtility::getInstance()->getEquipment(m_equipment->getEquipmentID()).EquipPrice;
    m_equipment->setEquipmentID(-1);
    if (m_callback && m_callbackListener)
    {
        (m_callbackListener->*m_callback)(dynamic_cast<Node*>(m_equipment));
    }
    this->removeFromParent();
}

void DetailLayer::setCallbackFunc(Ref*target, cocos2d::SEL_CallFuncN callFun){
	m_callback = callFun;
	m_callbackListener = target;
}

void DetailLayer::onEnter(){
	PopupLayer::onEnter();
}

