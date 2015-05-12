#include "TreasureBox.h"
#include "GameScene.h"
#include "JsonUtility.h"
#include "cocos2d.h"
#include "SoundsDef.h"
#include "SoundsController.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace CocosDenshion;
TreasureBox::TreasureBox(){
}

TreasureBox::~TreasureBox(){

}

TreasureBox* TreasureBox::create(ScenarioEnum scenario){
	TreasureBox* treasure = new (std::nothrow)TreasureBox;
	if (treasure && treasure->init(scenario))
	{
		treasure->autorelease();
		return treasure;
	}
	CC_SAFE_DELETE(treasure);
	return treasure;
}

bool TreasureBox::init(ScenarioEnum scenario){
	if (!Node::init())
	{
		return false;
	}


	__loadCSB();
	__createEquipment(scenario);
	return true;
}

void TreasureBox::__loadCSB(){
	Node* rootNode = CSLoader::createNode("tbox/tbox.csb");
	m_clickButton = static_cast<Button*>(rootNode->getChildByTag(14));
	m_armature = static_cast<Armature*>(rootNode->getChildByTag(13));
	m_armature->getAnimation()->play("stand");
	m_clickButton->addClickEventListener(CC_CALLBACK_1(TreasureBox::onBoxClicked, this));
	this->addChild(rootNode);
}

void TreasureBox::__createEquipment(ScenarioEnum scenario){
	 m_equ = Equipment::create("Default/Button_Disable.png","Default/Button_Disable.png","Default/Button_Disable.png");
	int i = static_cast<int>(scenario);	
	int j =	RandomHelper::random_int(0, 3);	
	EquipmentType type = static_cast<EquipmentType>(j);
	int ID = j * 3 + i;
	m_equ->setEquipmentID(ID);
	m_equ->setEquipmentStyle(type);
	EquipmentInfo info = JsonUtility::getInstance()->getEquipment(ID);
	float percent = RandomHelper::random_real(0.8f, 1.2f);
	m_equ->setAttack(info.Attack * percent);
	percent = RandomHelper::random_real(0.8f, 1.2f);
	m_equ->setAttackRate(info.AttackRate * percent);
	percent = RandomHelper::random_real(0.8f, 1.2f);
	m_equ->setDenfense(info.Defense * percent);
	percent = RandomHelper::random_real(0.8f, 1.2f);
	m_equ->setMoveRate(info.MoveRate * percent);
	percent = RandomHelper::random_real(0.8f, 1.2f);
	m_equ->setIntelligence(info.Intelligence * percent);
	percent = RandomHelper::random_real(0.8f, 1.2f);
	m_equ->setBlood(info.Blood * percent);
	m_equ->retain();
}

void TreasureBox::onBoxClicked(cocos2d::Ref*){
    m_clickButton->setEnabled(false);
	__writeInfo();
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_24.c_str());
	auto callfuncPlay = CallFunc::create([=](){
		m_armature->getAnimation()->play("release", -1 , 0);
	});
	auto callfuncRemove = CallFunc::create([=](){
		this->removeFromParent();
	});
	this->runAction(Sequence::create(callfuncPlay, DelayTime::create(3.5f), callfuncRemove ,NULL));

}

void TreasureBox::__writeInfo(){
	User &user = JsonUtility::getInstance()->user;
    int number = -1;
    for (int i= 0; i < 24; i++){
        if(-1 == user.Equip[i].ID){
            number = i;
            break;
        }
    }
    
    if (-1 == number) {
        log("==== full bag ====");
    }
    else
    {
	user.Equip[number].Attack = m_equ->getAttack();
	user.Equip[number].AttackRate = m_equ->getAttackRate();
	user.Equip[number].Blood = m_equ->getBlood();
	user.Equip[number].Defense = m_equ->getDenfense();
	user.Equip[number].Intelligence = m_equ->getIntelligence();
	user.Equip[number].MoveRate = m_equ->getMoveRate();
	user.Equip[number].ID = m_equ->getEquipmentID();
	user.Equip[number].Style = m_equ->getEquipmentStyle();
	user.Equip[number].Used = false;
    user.EquipmentNumber = user.EquipmentNumber + 1;
    }
    
}