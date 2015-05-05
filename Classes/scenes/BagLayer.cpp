#include "BagLayer.h"
#include "cocos2d.h"
#include "VisibleRect.h"
#include "Equipment.h"
#include "ui/CocosGUI.h"
#include "SetupLayer.h"
#include "DetailLayer.h"
#include "Inventory.h"

USING_NS_CC;
using namespace ui;
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
	scene->addChild(baglayer, 1);

	Sprite* fakeSprite = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	fakeSprite->setPosition(VisibleRect::center());
	fakeSprite->setFlippedY(true);
	fakeSprite->setColor(Color3B::GRAY);
	scene->addChild(fakeSprite, 0);
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
	User& user = JsonUtility::getInstance()->user;
	for (int i = 0; i < user.EquipmentNumber; i++) {
			Equipment* aEquipment = __matchPic(user.Equip[i].ID);
			aEquipment->setBlood(user.Equip[i].Blood);
			aEquipment->setIntelligence(user.Equip[i].Intelligence);
			aEquipment->setEquipmentID(user.Equip[i].ID);
			aEquipment->setEquipmentStyle(static_cast<EquipmentType>(user.Equip[i].Style));
			aEquipment->setDenfense(user.Equip[i].Defense);
			aEquipment->setMoveRate(user.Equip[i].MoveRate);
			aEquipment->setAttack(user.Equip[i].Attack);
			aEquipment->setAttackRate(user.Equip[i].AttackRate);
			aEquipment->setUsed(user.Equip[i].Used);
			m_equipmentVec.pushBack(aEquipment);
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
	Equipment* eq = Equipment::create(filename, filename, filename);
	return eq;
}

void BagLayer::setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun){
	m_callback = callFun;
	m_callbackListener = target;
}

void BagLayer::__loadPicFromCSB(){
	m_baglayer = static_cast<Node*>(CSLoader::createNode("bag/bag.csb"));
	Button* backButton = static_cast<Button*>(m_baglayer->getChildByTag(76));
	backButton->addClickEventListener(CC_CALLBACK_1(BagLayer::onBackButtonClickListener, this));

	ImageView* equip[24] = { nullptr };
	int i = 142;
	for (Equipment* eq : m_equipmentVec){
		if (!eq->getUsed()){
			equip[i - 142] = static_cast<ImageView*>(m_baglayer->getChildByTag(140)->getChildByTag(141)->getChildByTag(i));
			eq->addClickEventListener(CC_CALLBACK_1(BagLayer::onEquipmentClickedListener, this));
			eq->setScale(1.2f);
			eq->setPosition(Vec2(91.5f, 81.5f));
			eq->setTag(i);
			equip[i - 142]->addChild(eq);
			i++;
		}
		else{

			eq->setPosition(Vec2(64.5f, 64.5f));
			eq->addClickEventListener(CC_CALLBACK_1(BagLayer::onEquipmentClickedListener, this));
			switch (eq->getEquipmentStyle())
			{
			case EquipmentType::Hat:
				m_baglayer->getChildByTag(139)->getChildByTag(178)->addChild(eq);					
				break;
			case EquipmentType::Aniversary:
				m_baglayer->getChildByTag(139)->getChildByTag(179)->addChild(eq);
				break;
			case EquipmentType::Cloth:
				m_baglayer->getChildByTag(139)->getChildByTag(180)->addChild(eq);
				break;
			case EquipmentType::Shoes:
				m_baglayer->getChildByTag(139)->getChildByTag(181)->addChild(eq);
				break;
			default:
				break;
			}
		}
	}
    
    __flushInventory();
	this->addChild(m_baglayer);
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
	//log("inside========= %d", node->getTag());
	InventoryEnum type = static_cast<InventoryEnum>(node->getTag()- 301);
	DetailLayer* detail = DetailLayer::create(type);
	detail->setCallbackFunc(this, callfuncN_selector(BagLayer::__handleInventoryDetailLayer));
	this->addChild(detail, 2);

}

void BagLayer::onEquipmentClickedListener(cocos2d::Ref* sender){
	Equipment* node = static_cast<Equipment*>(sender);
	log("Equitment id====== %d", node->getEquipmentID());
	DetailLayer* detail = DetailLayer::create(node);
	detail->setCallbackFunc(this, callfuncN_selector(BagLayer::__handleEquipmentDetailLayer));
	this->addChild(detail);
}

void BagLayer::onBackButtonClickListener(Ref* sender){
	Director::getInstance()->popScene();
}


void BagLayer::__handleEquipmentDetailLayer(cocos2d::Node* sender){
	Equipment* equ = static_cast<Equipment*>(sender);
	__replaceEquipment(equ);
	
}

void BagLayer::__handleInventoryDetailLayer(cocos2d::Node* sender){
    __flushInventory();
	__playAnimation();
}

void BagLayer::__playAnimation(){
	Label* label = Label::create("Hello","fonts/arial.ttf", 20);
	label->setPosition(Vec2(640, 360));
	this->addChild(label);
	FadeIn* action1 = FadeIn::create(1.0f);
	MoveTo* action2 = MoveTo::create(1.0f, Vec2(640, 380));
	FadeOut* action3 = FadeOut::create(1.0f);
	Sequence* seq1 = Sequence::create(action2, action3, NULL);
	Sequence* seq2 = Sequence::create(action1, seq1, NULL);
	label->runAction(seq2);
}

void BagLayer::__replaceEquipment(Equipment* equ){
	EquipmentType type = equ->getEquipmentStyle();
	Node* bg = m_baglayer->getChildByTag(139);
	equ->setScale(1);
	equ->setPosition(Vec2(64.5f, 64.5f));
	switch (type)
	{
	case EquipmentType::Hat:
		if (0 == bg->getChildByTag(178)->getChildrenCount())
		{	
			equ->retain();
			equ->removeFromParent();
			bg->getChildByTag(178)->addChild(equ);
			equ->setUsed(true);
		}
		else
		{
			Equipment* temp = static_cast<Equipment*>(bg->getChildByTag(178)->getChildren().at(0));
			Node* tempParent = equ->getParent();
			temp->retain();
			equ->retain();
			equ->removeFromParent();
			temp->removeFromParent();
			temp->setScale(1.2f);
			temp->setPosition(Vec2(91.5f, 81.5f));
			tempParent->addChild(temp);
			bg->getChildByTag(178)->addChild(equ);
			equ->setUsed(true);
			temp->setUsed(false);
		}
		break;
	case EquipmentType::Aniversary:
		if (0 == bg->getChildByTag(179)->getChildrenCount())
		{
			equ->retain();
			equ->removeFromParent();
			bg->getChildByTag(179)->addChild(equ);
			equ->setUsed(true);
		}
		else
		{
			Equipment* temp = static_cast<Equipment*>(bg->getChildByTag(179)->getChildren().at(0));
			Node* tempParent = equ->getParent();
			temp->retain();
			equ->retain();
			equ->removeFromParent();
			temp->removeFromParent();
			temp->setScale(1.2f);
			temp->setPosition(Vec2(91.5f, 81.5f));
			tempParent->addChild(temp);
			bg->getChildByTag(179)->addChild(equ);
			equ->setUsed(true);
			temp->setUsed(false);
		}
		break;
	case EquipmentType::Cloth:
		if (0 == bg->getChildByTag(180)->getChildrenCount())
		{
			equ->retain();
			equ->removeFromParent();
			bg->getChildByTag(180)->addChild(equ);
			equ->setUsed(true);
		}
		else
		{
			Equipment* temp = static_cast<Equipment*>(bg->getChildByTag(180)->getChildren().at(0));
			Node* tempParent = equ->getParent();
			temp->retain();
			equ->retain();
			equ->removeFromParent();
			temp->removeFromParent();
			temp->setScale(1.2f);
			temp->setPosition(Vec2(91.5f, 81.5f));
			tempParent->addChild(temp);
			bg->getChildByTag(180)->addChild(equ);
			equ->setUsed(true);
			temp->setUsed(false);
		}
		break;
	case EquipmentType::Shoes:
		if (0 == bg->getChildByTag(181)->getChildrenCount())
		{
			equ->retain();
			equ->removeFromParent();
			bg->getChildByTag(181)->addChild(equ);
			equ->setUsed(true);
		}
		else
		{
			Equipment* temp = static_cast<Equipment*>(bg->getChildByTag(181)->getChildren().at(0));
			Node* tempParent = equ->getParent();
			temp->retain();
			equ->retain();
			equ->removeFromParent();
			temp->removeFromParent();
			temp->setScale(1.2f);
			temp->setPosition(Vec2(91.5f, 81.5f));
			tempParent->addChild(temp);
			bg->getChildByTag(181)->addChild(equ);
			equ->setUsed(true);
			temp->setUsed(false);
		}
		break;
	default:
		break;
	}
}

void BagLayer::__flushInventory(){
    User& m_user = JsonUtility::getInstance()->user;
    Inventory* inventory[6] = { nullptr };
    for (int j = 0; j < 6; j++){
        Button* button = static_cast<Button*>(m_baglayer->getChildByTag(139)->getChildByTag(301 + j));
        inventory[j] = Inventory::create();
        inventory[j]->setInventoryButton(button);
        if (m_user.ToolID[j] != 0){
            inventory[j]->getInventoryButton()->setBright(true);
            inventory[j]->getInventoryButton()->setEnabled(true);
            inventory[j]->setAmount(m_user.ToolID[j]);
            Text* text = inventory[j]->getInventoryButton()->getChildByName<Text*>("text");
            char number[2];
            std::sprintf(number, "%d", m_user.ToolID[j]);
            text->setString(number);
            inventory[j]->getInventoryButton()->addClickEventListener(CC_CALLBACK_1(BagLayer::onInventoryClickedListener, this));
        }
        else
        {
            inventory[j]->getInventoryButton()->setBright(false);
            Text* text = inventory[j]->getInventoryButton()->getChildByName<Text*>("text");
            text->setString(" ");
            
        }
        
    }

}
