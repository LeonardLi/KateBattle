#include "TreasureBox.h"
#include "GameScene.h"
#include "JsonUtility.h"
#include "cocos2d.h"
USING_NS_CC;
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

	return true;
}

void TreasureBox::__loadCSB(){
	
}

void TreasureBox::__createEquipment(ScenarioEnum scenario){
	 m_equ = Equipment::create("Default/Button_Disable.png","Default/Button_Disable.png","Default/Button_Disable.png");
	int i = static_cast<int>(scenario);	
	int j =	RandomHelper::random_int(0, 3);	
	int ID = j * 3 + i;

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
}