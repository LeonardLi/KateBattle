#include "BagLayer.h"
#include "cocos2d.h"
#include "VisibleRect.h"
#include "Equipment.h"
#include "ui/CocosGUI.h"
#include "SetupLayer.h"
#include "DetailLayer.h"
#include "Inventory.h"
#include "SoundsDef.h"
#include "SoundsController.h"
#include <string>
#include "Hero.h"

USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;
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
	if (!LayerColor::init())
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
	User user = JsonUtility::getInstance()->user;
    m_equipmentVec.clear();
	for (int i = 0; i < 24; i++) {
        if (user.Equip[i].ID == -1) {
            continue;
        }
			std::string file = JsonUtility::getInstance()->getEquipment(user.Equip[i].ID).EquipAddress;
			Equipment* aEquipment = Equipment::create(file, file, file);
			aEquipment->setBlood(user.Equip[i].Blood);
			aEquipment->setIntelligence(user.Equip[i].Intelligence);
			aEquipment->setEquipmentID(user.Equip[i].ID);
			aEquipment->setEquipmentStyle(static_cast<EquipmentType>(user.Equip[i].Style));
			aEquipment->setDenfense(user.Equip[i].Defense);
			aEquipment->setMoveRate(user.Equip[i].MoveRate);
			aEquipment->setAttack(user.Equip[i].Attack);
			aEquipment->setAttackRate(user.Equip[i].AttackRate);
			aEquipment->setUsed(user.Equip[i].Used);
			aEquipment->setIndex(i);
			m_equipmentVec.pushBack(aEquipment);
			
	}
	//log("vec size ============================ %zd",m_equipmentVec.size());
	return true;
}

void BagLayer::setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun){
	m_callback = callFun;
	m_callbackListener = target;
}

void BagLayer::__loadPicFromCSB(){
	m_baglayer = static_cast<Node*>(CSLoader::createNode("bag/bag.csb"));
	Button* backButton = static_cast<Button*>(m_baglayer->getChildByTag(139)->getChildByTag(76));
	backButton->addClickEventListener(CC_CALLBACK_1(BagLayer::onBackButtonClickListener, this));
	
	Button* advancedButton = static_cast<Button*>(m_baglayer->getChildByTag(139)->getChildByTag(121));
	advancedButton->addClickEventListener(CC_CALLBACK_1(BagLayer::onAdvancedButtonClickListener, this));

	__flushHeroStatus();
	__flushEquipment();
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

void BagLayer::onAdvancedButtonClickListener(cocos2d::Ref* sender){
	Vector<Equipment*> equiped;
	for (auto equipment:m_equipmentVec)
	{
		if (equipment->getUsed()==true)
		{
			equiped.pushBack(equipment);
		}
	}
	if (equiped.size()==4)
	{
		int level=equiped.at(0)->getEquipmentID()%3;
		for (int i = 1; i < 4;i++)
		{
			if (level!=equiped.at(i)->getEquipmentID()%3)
			{
				Label* label = Label::create("make sure these 4 items in one level!", "fonts/arial.ttf", 20);
				label->setPosition(Vec2(640, 360));
				label->setColor(Color3B::BLACK);
				this->addChild(label);
				FadeIn* action1 = FadeIn::create(1.0f);
				MoveTo* action2 = MoveTo::create(1.0f, Vec2(640, 380));
				FadeOut* action3 = FadeOut::create(1.0f);
				Sequence* seq1 = Sequence::create(action2, action3, NULL);
				Sequence* seq2 = Sequence::create(action1, seq1, NULL);
				label->runAction(seq2);
				return;
			}
		}
		User& user = JsonUtility::getInstance()->user;
		if (user.UserLevel==level)
		{
			for (auto equipment1 :equiped)
			{
				equipment1->setTouchEnabled(false);
				equipment1->runAction(Sequence::create(ScaleBy::create(0.8, 1.4), ScaleBy::create(2.0, 0), NULL));
				user.Equip[equipment1->getIndex()].ID = -1;
			}
			SimpleAudioEngine::getInstance()->playEffect(EFFECTS_17.c_str());
			Label* label = Label::create("Level Up!!!", "fonts/arial.ttf", 30);
			label->setPosition(Vec2(640, 360));
			label->setColor(Color3B::BLACK);
			this->addChild(label);
			FadeIn* action1 = FadeIn::create(1.0f);
			MoveTo* action2 = MoveTo::create(1.0f, Vec2(640, 380));
			FadeOut* action3 = FadeOut::create(1.0f);
			Sequence* seq1 = Sequence::create(action2, action3, NULL);
			Sequence* seq2 = Sequence::create(action1, seq1, NULL);
			label->runAction(seq2);


			log("==========advanced=========================");
		}
		else
		{
			Label* label = Label::create("please use the correct level equipment!", "fonts/arial.ttf", 20);
			label->setPosition(Vec2(640, 360));
			label->setColor(Color3B::BLACK);
			this->addChild(label);
			FadeIn* action1 = FadeIn::create(1.0f);
			MoveTo* action2 = MoveTo::create(1.0f, Vec2(640, 380));
			FadeOut* action3 = FadeOut::create(1.0f);
			Sequence* seq1 = Sequence::create(action2, action3, NULL);
			Sequence* seq2 = Sequence::create(action1, seq1, NULL);
			label->runAction(seq2);
		}
	}
	else
	{
		Label* label = Label::create("please collect 4 items!", "fonts/arial.ttf", 20);
		label->setPosition(Vec2(640, 360));
		label->setColor(Color3B::BLACK);
		this->addChild(label);
		FadeIn* action1 = FadeIn::create(1.0f);
		MoveTo* action2 = MoveTo::create(1.0f, Vec2(640, 380));
		FadeOut* action3 = FadeOut::create(1.0f);
		Sequence* seq1 = Sequence::create(action2, action3, NULL);
		Sequence* seq2 = Sequence::create(action1, seq1, NULL);
		label->runAction(seq2);
	}

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
	Node* node = static_cast<Node*>(sender);
	node->setTag(101); 
	if (m_callbackListener && m_callback)
	{
		(m_callbackListener->*m_callback)(node);
	}
	Director::getInstance()->popScene();
}


void BagLayer::__handleEquipmentDetailLayer(cocos2d::Node* sender){
	Equipment* equ = static_cast<Equipment*>(sender);
    if(equ->getEquipmentID() == -1){
        
    }
    else{
		if (equ->getUsed()){
		//equip 
		__replaceEquipment(equ);
		
		}
		else{
		//unequip
		__updateHeroData(equ, true);
		}
    }
	__flushEquipment();
	__flushHeroStatus();
}

void BagLayer::__handleInventoryDetailLayer(cocos2d::Node* sender){
    if (sender->getTag() == 99) {
       	__flushInventory();
        return;
    }
	InventoryEnum type = static_cast<InventoryEnum>(sender->getTag());
	__flushInventory();
	__playAnimation(type);
	if (m_callback && m_callbackListener)
	{
		(m_callbackListener->*m_callback)(sender);
	}
	__flushHeroStatus();
}

void BagLayer::__playAnimation(InventoryEnum type){
	//show different thing according to the type
	Tool inventory = JsonUtility::getInstance()->getTool(static_cast<int>(type));
	Label* label = Label::create(inventory.ToolEffect,"Arial", 20);
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
	User& user = JsonUtility::getInstance()->user;
	switch (type)
	{
	case EquipmentType::Hat:
		if (0 == bg->getChildByTag(178)->getChildrenCount())
		{	
			user.Equip[equ->getIndex()].Used = true;
			__updateHeroData(equ, false);
		}
		else
		{
			Equipment* temp = static_cast<Equipment*>(bg->getChildByTag(178)->getChildren().at(0));
			temp->setUsed(false);
			equ->setUsed(true);
			user.Equip[temp->getIndex()].Used = false;
			user.Equip[equ->getIndex()].Used = true;
			__updateHeroData(equ, temp);

		}
		break;
	case EquipmentType::Aniversary:
		if (0 == bg->getChildByTag(179)->getChildrenCount())
		{
			user.Equip[equ->getIndex()].Used = true;
			__updateHeroData(equ, false);
		}
		else
		{
			Equipment* temp = static_cast<Equipment*>(bg->getChildByTag(179)->getChildren().at(0));
			temp->setUsed(false);
			equ->setUsed(true);
			user.Equip[temp->getIndex()].Used = false;
			user.Equip[equ->getIndex()].Used = true;
			__updateHeroData(equ, temp);
		}
		break;
	case EquipmentType::Cloth:
		if (0 == bg->getChildByTag(180)->getChildrenCount())
		{
			user.Equip[equ->getIndex()].Used = true;
			__updateHeroData(equ, false);
		}
		else
		{
			Equipment* temp = static_cast<Equipment*>(bg->getChildByTag(180)->getChildren().at(0));
			temp->setUsed(false);
			equ->setUsed(true);
			user.Equip[temp->getIndex()].Used = false;
			user.Equip[equ->getIndex()].Used = true;
			__updateHeroData(equ, temp);
		}
		break;
	case EquipmentType::Shoes:
		if (0 == bg->getChildByTag(181)->getChildrenCount())
		{
			user.Equip[equ->getIndex()].Used = true;
			__updateHeroData(equ, false);
		}
		else
		{
			Equipment* temp = static_cast<Equipment*>(bg->getChildByTag(181)->getChildren().at(0));
			temp->setUsed(false);
			equ->setUsed(true);
			user.Equip[temp->getIndex()].Used = false;
			user.Equip[equ->getIndex()].Used = true;
			__updateHeroData(equ, temp);
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
        inventory[j]->getInventoryButton()->setBright(true);
        inventory[j]->getInventoryButton()->setEnabled(true);
        inventory[j]->getInventoryButton()->addClickEventListener(CC_CALLBACK_1(BagLayer::onInventoryClickedListener, this));
        if (m_user.ToolID[j] != 0){
            inventory[j]->setAmount(m_user.ToolID[j]);
            Text* text = inventory[j]->getInventoryButton()->getChildByName<Text*>("text");
			text->setString(std::to_string(m_user.ToolID[j]));
        }
        else
        {
            Text* text = inventory[j]->getInventoryButton()->getChildByName<Text*>("text");
            text->setString(" ");
            
        }
        
    }

}

void BagLayer::__flushEquipment(){
    __initFromFile();
	ImageView* equip[24] = { nullptr };
	int i = 142;
	for (int k = 142; k < 164; k++)
	{
		equip[k - 142] = static_cast<ImageView*>(m_baglayer->getChildByTag(140)->getChildByTag(141)->getChildByTag(k));
		equip[k - 142]->removeAllChildrenWithCleanup(true);
	}
	for (int k = 178; k < 182; k++){
		if (0 != m_baglayer->getChildByTag(139)->getChildByTag(k)->getChildrenCount()){
			m_baglayer->getChildByTag(139)->getChildByTag(k)->removeAllChildrenWithCleanup(true);
		}

	}

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
			eq->setScale(1);
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
}

void BagLayer::__flushHeroStatus(){
	Text* speed = static_cast<Text*>(m_baglayer->getChildByTag(139)->getChildByTag(167));
	Text* attackValue = static_cast<Text*>(m_baglayer->getChildByTag(139)->getChildByTag(165));
	Text* Hp = static_cast<Text*>(m_baglayer->getChildByTag(139)->getChildByTag(163));
	Text* defence = static_cast<Text*>(m_baglayer->getChildByTag(139)->getChildByTag(157));
	Text* intelligence = static_cast<Text*>(m_baglayer->getChildByTag(139)->getChildByTag(164));
	Text* attackRate = static_cast<Text*>(m_baglayer->getChildByTag(139)->getChildByTag(166));

	User user = JsonUtility::getInstance()->user;

	speed->setString(std::to_string((int)user.UserMoveRate));
	attackValue->setString(std::to_string((int)user.UserAttack));
	Hp->setString(std::to_string((int)user.UserHealth));
	defence->setString(std::to_string((int)user.UserDefense));
	intelligence->setString(std::to_string((int)user.UserIntelligence));
	attackRate->setString(std::to_string((int)user.UserAttackRate));
}

void BagLayer::__updateHeroData(InventoryEnum type){
	
}

void BagLayer::__updateHeroData(Equipment* equ, bool type){
	User& user = JsonUtility::getInstance()->user;
	//update the value
	if (type){
		float healthRate = user.UserCulHealth / user.UserHealth;
		user.UserAttack = user.UserAttack - equ->getAttack();
		user.UserMoveRate = user.UserMoveRate - equ->getMoveRate();
		user.UserAttackRate = user.UserAttackRate - equ->getAttackRate();
		user.UserHealth = user.UserHealth - equ->getBlood();
		user.UserCulHealth = user.UserHealth * healthRate;
		user.UserDefense = user.UserDefense - equ->getDenfense();
		user.UserIntelligence = user.UserIntelligence - equ->getIntelligence();
	}
	else{
		float healthRate = user.UserCulHealth / user.UserHealth;
		user.UserAttack = user.UserAttack + equ->getAttack();
		user.UserMoveRate = user.UserMoveRate + equ->getMoveRate();
		user.UserAttackRate = user.UserAttackRate + equ->getAttackRate();
		user.UserHealth = user.UserHealth + equ->getBlood();
		user.UserCulHealth = user.UserHealth * healthRate;
		user.UserDefense = user.UserDefense + equ->getDenfense();
		user.UserIntelligence = user.UserIntelligence + equ->getIntelligence();
	}
}

void BagLayer::__updateHeroData(Equipment* newEqu, Equipment* oldEqu){
	User& user = JsonUtility::getInstance()->user;
	float healthRate = user.UserCulHealth / user.UserHealth;
	user.UserAttack = user.UserAttack - oldEqu->getAttack() + newEqu->getAttack();
	user.UserMoveRate = user.UserMoveRate - oldEqu->getMoveRate() + newEqu->getAttack();
	user.UserAttackRate = user.UserAttackRate - oldEqu->getAttackRate() + newEqu->getAttackRate();
	user.UserHealth = user.UserHealth - oldEqu->getBlood() + newEqu->getBlood();
	user.UserCulHealth = user.UserCulHealth * healthRate;
	user.UserDefense = user.UserDefense - oldEqu->getDenfense() + newEqu->getDenfense() ;
	user.UserIntelligence = user.UserIntelligence - oldEqu->getIntelligence() + newEqu->getIntelligence();
}