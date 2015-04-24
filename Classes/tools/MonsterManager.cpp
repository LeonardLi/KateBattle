#include "MonsterManager.h"
#include "Monster.h"
#include "MonsterFSM.h"
#include "I_State.h"
#include "StateAttack.h"
#include "StateUseSkill.h"
USING_NS_CC;

MonsterManager* MonsterManager::createWithLevel(int iCurlevel){
	MonsterManager* monsterMgr = new MonsterManager();

	if (monsterMgr && monsterMgr->initWithLevel(iCurlevel))
	{
		monsterMgr->autorelease();
	}
	else
		CC_SAFE_DELETE(monsterMgr);

	return monsterMgr;
}

bool MonsterManager::initWithLevel(int iCurlevel){
	createMonsters(iCurlevel);
	return true;
}


Vector<Monster*> MonsterManager::getMonsterList(){
	return m_monsterList;
}

void MonsterManager::createMonsters(int iCurlevel){
	
	
	/*Monster* monster1 = Monster::create(Sprite::create("wolf.png"),0);
	monster1->setPosition(0, 0);
	monster1->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster1);
	this->addChild(monster1);

	Monster* monster2 = Monster::create(Sprite::create("wolf.png"),1);
	monster2->setPosition(600, 200);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	this->addChild(monster2);*/


	//BOSS NUM 1
	//Vector<Monster*> number1BossShoot;

	//auto shoot = Monster::create(Sprite::create("CloseNormal.png"), MonsterType::num1ShootType);
	//shoot->setPosition(1000, 100);
	//shoot->getFSM()->changeState(new StateUseSkill());
	//number1BossShoot.pushBack(shoot);
	//m_monsterList.pushBack(shoot);

	//auto shoot2 = Monster::create(Sprite::create("CloseNormal.png"), MonsterType::num1ShootType);
	//shoot2->setPosition(1000, 200);
	//shoot2->getFSM()->changeState(new StateUseSkill());
	//number1BossShoot.pushBack(shoot2);
	//m_monsterList.pushBack(shoot2);

	//auto shoot3 = Monster::create(Sprite::create("CloseNormal.png"), MonsterType::num1ShootType);
	//shoot3->setPosition(1000, 300);
	//shoot3->getFSM()->changeState(new StateUseSkill());
	//number1BossShoot.pushBack(shoot3);
	//m_monsterList.pushBack(shoot3);
	//
	//auto shoot4 = Monster::create(Sprite::create("CloseNormal.png"), MonsterType::num1ShootType);
	//shoot4->setPosition(1000, 400);
	//shoot4->getFSM()->changeState(new StateUseSkill());
	//number1BossShoot.pushBack(shoot4);
	//m_monsterList.pushBack(shoot4);
	//

	//Monster* monster2 = MonsterBossNum1::create(Sprite::create("wolf.png"), number1BossShoot);
	//monster2->setPosition(0, 0);
	//monster2->getFSM()->changeState(new BossStateUseSkill());
	//m_monsterList.pushBack(monster2);
	////monster2->setAnchorPoint(Vec2(0.5, 0.5));
	//this->addChild(monster2); 
	
	//Boss Number 2

	auto monster1 = Monster::create(Sprite::create("wolf.png"), MonsterType::monsterBossNum2Assister);
	monster1->setPosition(Vec2(800,400));
	monster1->getFSM()->changeState(new StateAttack());
	m_monsterList.pushBack(monster1);
	this->addChild(monster1);

	MonsterBossNum2* monster2 = MonsterBossNum2::create(Sprite::create("wolf.png"), monster1);
	monster2->setPosition(Vec2(200,200));
	monster2->getFSM()->changeState(new BossStateAttack());
	monster2->setAnchorPoint(Vec2(0.5,0.5));
	m_monsterList.pushBack(monster2);
	this->addChild(monster2);



	//Boss Number 3

	//Vector<Monster*> number3BossCar;
	//auto car1 = Monster::create(Sprite::create("wolf.png"), MonsterType::num3CarType);
	////car1->setPosition(1000, 375);
	//car1->getFSM()->changeState(new StateAttack());
	//number3BossCar.pushBack(car1);
	//
	//auto car2 = Monster::create(Sprite::create("wolf.png"), MonsterType::num3CarType);
	////car2->setPosition(1000, 225);
	//car2->getFSM()->changeState(new StateAttack());
	//number3BossCar.pushBack(car2);

	//auto car3 = Monster::create(Sprite::create("wolf.png"), MonsterType::num3CarType);
	////car3->setPosition(1000,75);
	//car3->getFSM()->changeState(new StateAttack());
	//number3BossCar.pushBack(car3);

	//Monster* monster3 = MonsterBossNum3::create(Sprite::create("wolf.png"), number3BossCar);
	//monster3->setPosition(200, 200);
	//monster3->getFSM()->changeState(new BossStateAttack());
	//m_monsterList.pushBack(monster3);
	//this->addChild(monster3);
	


}