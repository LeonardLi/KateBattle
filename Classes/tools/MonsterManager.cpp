#include "MonsterManager.h"
#include "Monster.h"
#include "MonsterFSM.h"
#include "I_State.h"
#include "StateAttack.h"
#include "StateUseSkill.h"
#include "GameScene.h"
USING_NS_CC;

MonsterManager* MonsterManager::createWithLevel(ScenarioEnum scenario, SubScenarioEnum subscenario){
	MonsterManager* monsterMgr = new MonsterManager();

	if (monsterMgr && monsterMgr->initWithLevel(scenario,subscenario))
	{
		monsterMgr->autorelease();
	}
	else
		CC_SAFE_DELETE(monsterMgr);

	return monsterMgr;
}

bool MonsterManager::initWithLevel(ScenarioEnum scenario, SubScenarioEnum subscenario){
	createMonsters(scenario,subscenario);
	return true;
}


Vector<Monster*> MonsterManager::getMonsterList(){
	return m_monsterList;
}

Vector<Monster*> MonsterManager::getMonsterScreen1List(){
	return m_monsterScreen1List;
}
Vector<Monster*> MonsterManager::getMonsterScreen2List(){
	return m_monsterScreen2List;
}
void MonsterManager::createMonsters(ScenarioEnum scenario, SubScenarioEnum subscenario){
	if (scenario==ScenarioEnum::Port)
	{
		switch (subscenario)
		{
		case SubScenarioEnum::LV1:
			__createMonsterLevel11();
			break;
		case SubScenarioEnum::LV2:
			__createMonsterLevel12();
			break;
		case SubScenarioEnum::LV3:
			__createMonsterLevel13();
			break;
		default:
			break;
		}
	}
	else if (scenario==ScenarioEnum::Market)
	{
		switch (subscenario)
		{
		case SubScenarioEnum::LV1:
			__createMonsterLevel21();
			break;
		case SubScenarioEnum::LV2:
			__createMonsterLevel22();
			break;
		case SubScenarioEnum::LV3:
			__createMonsterLevel23();
			break;
		default:
			break;
		}
	}
	else if (scenario == ScenarioEnum::Sewer)
	{
		switch (subscenario)
		{
		case SubScenarioEnum::LV1:
			__createMonsterLevel31();
			break;
		case SubScenarioEnum::LV2:
			__createMonsterLevel32();
			break;
		case SubScenarioEnum::LV3:
			__createMonsterLevel33();
			break;
		default:
			break;
		}
	}
	else{
		return;
	}
}

void MonsterManager::__createMonsterLevel11()
{
	Monster* monster1 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv1);
	monster1->setPosition(900, 200);
	monster1->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster1);
	m_monsterScreen1List.pushBack(monster1);
	m_showedMonsterList.pushBack(monster1);
	this->addChild(monster1);

	Monster* monster2 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv1);
	monster2->setPosition(1500, 300);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	m_monsterScreen1List.pushBack(monster2);
	m_showedMonsterList.pushBack(monster2);
	this->addChild(monster2);

	Monster* monster3 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv1);
	monster3->setPosition(1600, 200);
	monster3->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster3);
	m_monsterScreen1List.pushBack(monster3);
	m_showedMonsterList.pushBack(monster3);
	this->addChild(monster3);

	Monster* monster4 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalMoveFastTypeLv1);
	monster4->setPosition(2800, 300);
	monster4->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster4);
	m_monsterScreen2List.pushBack(monster4);
	m_showedMonsterList.pushBack(monster4);
	this->addChild(monster4);

	Monster* monster9 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv1);
	monster9->setPosition(3500, 200);
	monster9->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster9);
	m_monsterScreen2List.pushBack(monster9);
	m_showedMonsterList.pushBack(monster9);
	this->addChild(monster9);
	Vector<Monster*> number1BossShoot;

}

void MonsterManager::__createMonsterLevel12()
{
	Monster* monster1 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalMoveFastTypeLv1);
	monster1->setPosition(900, 200);
	monster1->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster1);
	m_monsterScreen1List.pushBack(monster1);
	m_showedMonsterList.pushBack(monster1);
	this->addChild(monster1);

	Monster* monster2 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootTypeLv1);
	monster2->setPosition(1000, 100);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	m_monsterScreen1List.pushBack(monster2);
	m_showedMonsterList.pushBack(monster2);
	this->addChild(monster2);

	Monster* monster3 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAttackFastTypeLv1);
	monster3->setPosition(1600, 200);
	monster3->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster3);
	m_monsterScreen1List.pushBack(monster3);
	m_showedMonsterList.pushBack(monster3);
	this->addChild(monster3);

	Monster* monster4 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAttackFastTypeLv1);
	monster4->setPosition(1700, 250);
	monster4->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster4);
	m_monsterScreen1List.pushBack(monster4);
	m_showedMonsterList.pushBack(monster4);
	this->addChild(monster4);

	Monster* monster5 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalIronTypeLv1);
	monster5->setPosition(2900, 250);
	monster5->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster5);
	m_monsterScreen2List.pushBack(monster5);
	m_showedMonsterList.pushBack(monster5);
	this->addChild(monster5);

	Monster* monster6 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootTypeLv1);
	monster6->setPosition(3100, 200);
	monster6->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster6);
	m_monsterScreen2List.pushBack(monster6);
	m_showedMonsterList.pushBack(monster6);
	this->addChild(monster6);

	Monster* monster7 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAggressiveTypeLv1);
	monster7->setPosition(4000, 100);
	monster7->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster7);
	m_monsterScreen2List.pushBack(monster7);
	m_showedMonsterList.pushBack(monster7);
	this->addChild(monster7);

	Monster* monster8 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAggressiveTypeLv1);
	monster8->setPosition(4100, 280);
	monster8->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster8);
	m_monsterScreen2List.pushBack(monster8);
	m_showedMonsterList.pushBack(monster8);
	this->addChild(monster8);

}

void MonsterManager::__createMonsterLevel13()
{
	Monster* monster1 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv1);
	monster1->setPosition(900, 200);
	monster1->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster1);
	m_monsterScreen1List.pushBack(monster1);
	m_showedMonsterList.pushBack(monster1);
	this->addChild(monster1);

	Monster* monster2 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv1);
	monster2->setPosition(1000, 300);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	m_monsterScreen1List.pushBack(monster2);
	m_showedMonsterList.pushBack(monster2);
	this->addChild(monster2);

	Monster* monster3 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAggressiveTypeLv1);
	monster3->setPosition(1700, 200);
	monster3->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster3);
	m_monsterScreen1List.pushBack(monster3);
	m_showedMonsterList.pushBack(monster3);
	this->addChild(monster3);

	Monster* monster4 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootAggressiveTypeLv1);
	monster4->setPosition(1800, 300);
	monster4->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster4);
	m_monsterScreen1List.pushBack(monster4);
	m_showedMonsterList.pushBack(monster4);
	this->addChild(monster4);

	Monster* monster5 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootAggressiveTypeLv1);
	monster5->setPosition(1900, 100);
	monster5->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster5);
	m_monsterScreen1List.pushBack(monster5);
	m_showedMonsterList.pushBack(monster5);
	this->addChild(monster5);

	Monster* monster6 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv2);
	monster6->setPosition(2700, 200);
	monster6->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster6);
	m_monsterScreen2List.pushBack(monster6);
	m_showedMonsterList.pushBack(monster6);
	this->addChild(monster6);


	//Boss Number 3

	Vector<Monster*> number3BossCar;
	auto car1 = Monster::create(Sprite::create("car.png"), MonsterType::num3CarType);
	car1->getFSM()->changeState(new StateAttack());
	number3BossCar.pushBack(car1);

	auto car2 = Monster::create(Sprite::create("car.png"), MonsterType::num3CarType);
	car2->getFSM()->changeState(new StateAttack());
	number3BossCar.pushBack(car2);

	auto car3 = Monster::create(Sprite::create("car.png"), MonsterType::num3CarType);
	car3->getFSM()->changeState(new StateAttack());
	number3BossCar.pushBack(car3);

	Monster* monster8 = MonsterBossNum3::create(Sprite::create("wolf.png"), number3BossCar);
	monster8->setPosition(4100, 200);
	monster8->getFSM()->changeState(new BossStateUseSkill());
	m_monsterList.pushBack(monster8);
	m_showedMonsterList.pushBack(monster8);
	m_monsterScreen2List.pushBack(monster8);
	this->addChild(monster8, 5);
}

void MonsterManager::__createMonsterLevel21()
{
	Monster* monster1 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv2);
	monster1->setPosition(900, 200);
	monster1->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster1);
	m_monsterScreen1List.pushBack(monster1);
	m_showedMonsterList.pushBack(monster1);
	this->addChild(monster1);

	Monster* monster2 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv2);
	monster2->setPosition(1000, 100);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	m_monsterScreen1List.pushBack(monster2);
	m_showedMonsterList.pushBack(monster2);
	this->addChild(monster2);

	Monster* monster3 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalIronTypeLv2);
	monster3->setPosition(2800, 200);
	monster3->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster3);
	m_monsterScreen2List.pushBack(monster3);
	m_showedMonsterList.pushBack(monster3);
	this->addChild(monster3);


	Monster* monster5 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv2);
	monster5->setPosition(1600, 300);
	monster5->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster5);
	m_monsterScreen2List.pushBack(monster5);
	m_showedMonsterList.pushBack(monster5);
	this->addChild(monster5);

	Monster* monster6 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAggressiveTypeLv2);
	monster6->setPosition(1700, 200);
	monster6->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster6);
	m_monsterScreen2List.pushBack(monster6);
	m_showedMonsterList.pushBack(monster6);
	this->addChild(monster6);

	Monster* monster7 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalIronTypeLv2);
	monster7->setPosition(3600, 100);
	monster7->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster7);
	m_monsterScreen2List.pushBack(monster7);
	m_showedMonsterList.pushBack(monster7);
	this->addChild(monster7);

	Monster* monster8 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAggressiveTypeLv2);
	monster8->setPosition(3900, 300);
	monster8->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster8);
	m_monsterScreen2List.pushBack(monster8);
	m_showedMonsterList.pushBack(monster8);
	this->addChild(monster8);
}

void MonsterManager::__createMonsterLevel22()
{
	Monster* monster1 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalMoveFastTypeLv2);
	monster1->setPosition(900, 300);
	monster1->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster1);
	m_monsterScreen1List.pushBack(monster1);
	m_showedMonsterList.pushBack(monster1);
	this->addChild(monster1);

	Monster* monster2 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv2);
	monster2->setPosition(900, 100);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	m_monsterScreen1List.pushBack(monster2);
	m_showedMonsterList.pushBack(monster2);
	this->addChild(monster2);

	Monster* monster3 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalIronTypeLv2);
	monster3->setPosition(1600, 200);
	monster3->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster3);
	m_monsterScreen1List.pushBack(monster3);
	m_showedMonsterList.pushBack(monster3);
	this->addChild(monster3);

	Monster* monster4 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootTypeLv2);
	monster4->setPosition(1700, 300);
	monster4->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster4);
	m_monsterScreen1List.pushBack(monster4);
	m_showedMonsterList.pushBack(monster4);
	this->addChild(monster4);

	Monster* monster5 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv2);
	monster5->setPosition(2800, 300);
	monster5->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster5);
	m_monsterScreen2List.pushBack(monster5);
	m_showedMonsterList.pushBack(monster5);
	this->addChild(monster5);

	Monster* monster6 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootTypeLv2);
	monster6->setPosition(3000, 200);
	monster6->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster6);
	m_monsterScreen2List.pushBack(monster6);
	m_showedMonsterList.pushBack(monster6);
	this->addChild(monster6);

	Monster* monster7 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootTypeLv2);
	monster7->setPosition(3200, 100);
	monster7->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster7);
	m_monsterScreen2List.pushBack(monster7);
	m_showedMonsterList.pushBack(monster7);
	this->addChild(monster7);
}

void MonsterManager::__createMonsterLevel23()
{
	Monster* monster1 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv2);
	monster1->setPosition(900, 300);
	monster1->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster1);
	m_monsterScreen1List.pushBack(monster1);
	m_showedMonsterList.pushBack(monster1);
	this->addChild(monster1);

	Monster* monster2 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv2);
	monster2->setPosition(900, 100);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	m_monsterScreen1List.pushBack(monster2);
	m_showedMonsterList.pushBack(monster2);
	this->addChild(monster2);

	Monster* monster3 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootTypeLv2);
	monster3->setPosition(1100, 200);
	monster3->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster3);
	m_monsterScreen1List.pushBack(monster3);
	m_showedMonsterList.pushBack(monster3);
	this->addChild(monster3);

	Monster* monster4 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootAggressiveTypeLv2);
	monster4->setPosition(1800, 300);
	monster4->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster4);
	m_monsterScreen1List.pushBack(monster4);
	m_showedMonsterList.pushBack(monster4);
	this->addChild(monster4);

	Monster* monster5 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootAggressiveTypeLv2);
	monster5->setPosition(1800, 100);
	monster5->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster5);
	m_monsterScreen1List.pushBack(monster5);
	m_showedMonsterList.pushBack(monster5);
	this->addChild(monster5);

	Monster* monster6 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootTypeLv2);
	monster6->setPosition(1900, 200);
	monster6->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster6);
	m_monsterScreen1List.pushBack(monster6);
	m_showedMonsterList.pushBack(monster6);
	this->addChild(monster6);

	Monster* monster7 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv3);
	monster7->setPosition(2500, 100);
	monster7->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster7);
	m_monsterScreen1List.pushBack(monster7);
	m_showedMonsterList.pushBack(monster7);
	this->addChild(monster7);

	//BOSS NUM 1
	Vector<Monster*> number1BossShoot;

	auto shoot = Monster::create(Sprite::create("CloseNormal.png"), MonsterType::num1ShootType);
	shoot->setPosition(4050, 80);
	shoot->getFSM()->changeState(new StateUseSkill());
	number1BossShoot.pushBack(shoot);
	m_monsterList.pushBack(shoot);

	auto shoot2 = Monster::create(Sprite::create("CloseNormal.png"), MonsterType::num1ShootType);
	shoot2->setPosition(3150, 180);
	shoot2->getFSM()->changeState(new StateUseSkill());
	number1BossShoot.pushBack(shoot2);
	m_monsterList.pushBack(shoot2);

	auto shoot3 = Monster::create(Sprite::create("CloseNormal.png"), MonsterType::num1ShootType);
	shoot3->setPosition(4050, 160);
	shoot3->getFSM()->changeState(new StateUseSkill());
	number1BossShoot.pushBack(shoot3);
	m_monsterList.pushBack(shoot3);

	Monster* monster8 = MonsterBossNum1::create(Sprite::create("wolf.png"), number1BossShoot);
	monster8->setPosition(4100, 200);
	monster8->getFSM()->changeState(new BossStateUseSkill());
	m_monsterList.pushBack(monster8);
	m_showedMonsterList.pushBack(monster8);
	m_monsterScreen2List.pushBack(monster8);
	this->addChild(monster8);
	
}

void MonsterManager::__createMonsterLevel31()
{
	Monster* monster1 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv3);
	monster1->setPosition(850, 250);
	monster1->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster1);
	m_monsterScreen1List.pushBack(monster1);
	m_showedMonsterList.pushBack(monster1);
	this->addChild(monster1);

	Monster* monster2 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootTypeLv3);
	monster2->setPosition(1000, 50);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	m_monsterScreen1List.pushBack(monster2);
	m_showedMonsterList.pushBack(monster2);
	this->addChild(monster2);

	Monster* monster3 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalIronTypeLv3);
	monster3->setPosition(1600, 200);
	monster3->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster3);
	m_monsterScreen1List.pushBack(monster3);
	m_showedMonsterList.pushBack(monster3);
	this->addChild(monster3);

	Monster* monster4 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalIronTypeLv3);
	monster4->setPosition(1800, 300);
	monster4->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster4);
	m_monsterScreen1List.pushBack(monster4);
	m_showedMonsterList.pushBack(monster4);
	this->addChild(monster4);

	Monster* monster5 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv3);
	monster5->setPosition(2500, 300);
	monster5->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster5);
	m_monsterScreen2List.pushBack(monster5);
	m_showedMonsterList.pushBack(monster5);
	this->addChild(monster5);

	Monster* monster6 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAggressiveTypeLv3);
	monster6->setPosition(2700, 200);
	monster6->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster6);
	m_monsterScreen2List.pushBack(monster6);
	m_showedMonsterList.pushBack(monster6);
	this->addChild(monster6);

	Monster* monster7 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalIronTypeLv3);
	monster7->setPosition(3600, 100);
	monster7->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster7);
	m_monsterScreen2List.pushBack(monster7);
	m_showedMonsterList.pushBack(monster7);
	this->addChild(monster7);

	Monster* monster8 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAggressiveTypeLv3);
	monster8->setPosition(3900, 300);
	monster8->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster8);
	m_monsterScreen2List.pushBack(monster8);
	m_showedMonsterList.pushBack(monster8);
	this->addChild(monster8);
}

void MonsterManager::__createMonsterLevel32()
{
	Monster* monster1 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalMoveFastTypeLv3);
	monster1->setPosition(850, 250);
	monster1->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster1);
	m_monsterScreen1List.pushBack(monster1);
	m_showedMonsterList.pushBack(monster1);
	this->addChild(monster1);

	Monster* monster2 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootTypeLv3);
	monster2->setPosition(1000, 50);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	m_monsterScreen1List.pushBack(monster2);
	m_showedMonsterList.pushBack(monster2);
	this->addChild(monster2);

	Monster* monster3 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv3);
	monster3->setPosition(1600, 200);
	monster3->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster3);
	m_monsterScreen1List.pushBack(monster3);
	m_showedMonsterList.pushBack(monster3);
	this->addChild(monster3);

	Monster* monster4 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalTypeLv3);
	monster4->setPosition(1800, 300);
	monster4->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster4);
	m_monsterScreen1List.pushBack(monster4);
	m_showedMonsterList.pushBack(monster4);
	this->addChild(monster4);

	Monster* monster5 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv3);
	monster5->setPosition(2500, 300);
	monster5->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster5);
	m_monsterScreen2List.pushBack(monster5);
	m_showedMonsterList.pushBack(monster5);
	this->addChild(monster5);

	Monster* monster6 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAggressiveTypeLv3);
	monster6->setPosition(2700, 200);
	monster6->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster6);
	m_monsterScreen2List.pushBack(monster6);
	m_showedMonsterList.pushBack(monster6);
	this->addChild(monster6);

	Monster* monster7 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv3);
	monster7->setPosition(3500, 100);
	monster7->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster7);
	m_monsterScreen2List.pushBack(monster7);
	m_showedMonsterList.pushBack(monster7);
	this->addChild(monster7);

	Monster* monster8 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv3);
	monster8->setPosition(3900, 300);
	monster8->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster8);
	m_monsterScreen2List.pushBack(monster8);
	m_showedMonsterList.pushBack(monster8);
	this->addChild(monster8);
}

void MonsterManager::__createMonsterLevel33()
{
	Monster* monster1 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAggressiveTypeLv3);
	monster1->setPosition(900, 300);
	monster1->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster1);
	m_monsterScreen1List.pushBack(monster1);
	m_showedMonsterList.pushBack(monster1);
	this->addChild(monster1);

	Monster* monster2 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAggressiveTypeLv3);
	monster2->setPosition(900, 100);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	m_monsterScreen1List.pushBack(monster2);
	m_showedMonsterList.pushBack(monster2);
	this->addChild(monster2);

	Monster* monster3 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalAggressiveTypeLv3);
	monster3->setPosition(1100, 200);
	monster3->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster3);
	m_monsterScreen1List.pushBack(monster3);
	m_showedMonsterList.pushBack(monster3);
	this->addChild(monster3);

	Monster* monster4 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv3);
	monster4->setPosition(1700, 200);
	monster4->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster4);
	m_monsterScreen1List.pushBack(monster4);
	m_showedMonsterList.pushBack(monster4);
	this->addChild(monster4);

	Monster* monster5 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootAggressiveTypeLv3);
	monster5->setPosition(1820, 100);
	monster5->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster5);
	m_monsterScreen1List.pushBack(monster5);
	m_showedMonsterList.pushBack(monster5);
	this->addChild(monster5);

	Monster* monster6 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootAggressiveTypeLv3);
	monster6->setPosition(1820, 250);
	monster6->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster6);
	m_monsterScreen1List.pushBack(monster6);
	m_showedMonsterList.pushBack(monster6);
	this->addChild(monster6);

	Monster* monster7 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv3);
	monster7->setPosition(2500, 250);
	monster7->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster7);
	m_monsterScreen1List.pushBack(monster7);
	m_showedMonsterList.pushBack(monster7);
	this->addChild(monster7);

	Monster* monster10 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootAggressiveTypeLv3);
	monster10->setPosition(2600, 250);
	monster10->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster10);
	m_monsterScreen1List.pushBack(monster10);
	m_showedMonsterList.pushBack(monster10);
	this->addChild(monster10);


	//Boss Number 2

	auto monster8 = Monster::create(Sprite::create("wolf.png"), MonsterType::monsterBossNum2Assister);
	monster8->setPosition(Vec2(3725, 540));
	monster8->getFSM()->changeState(new StateAttack());
	m_monsterList.pushBack(monster8);
	this->addChild(monster8);

	auto box = Sprite::create("box3.png");
	box->setScale(0.5);
	box->setPosition(3790, 450);
	this->addChild(box);


	MonsterBossNum2* monster9 = MonsterBossNum2::create(Sprite::create("wolf.png"), monster8);
	monster9->setPosition(Vec2(3700, 200));
	monster9->getFSM()->changeState(new BossStateUseSkill());
	monster9->setAnchorPoint(Vec2(0.5, 0.5));
	m_monsterList.pushBack(monster9);
	m_showedMonsterList.pushBack(monster9);
	m_monsterScreen2List.pushBack(monster9);
	this->addChild(monster9);

}