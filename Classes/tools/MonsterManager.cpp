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

Vector<Monster*> MonsterManager::getMonsterScreen1List(){
	return m_monsterScreen1List;
}
Vector<Monster*> MonsterManager::getMonsterScreen2List(){
	return m_monsterScreen2List;
}
void MonsterManager::createMonsters(int iCurlevel){
	Monster* monster1 = Monster::create(Sprite::create("wolf.png"),MonsterType::normalAggressiveTypeLv1);
	monster1->setPosition(400, 200);
	monster1->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster1);
	m_monsterScreen1List.pushBack(monster1);
	m_showedMonsterList.pushBack(monster1);
	this->addChild(monster1);

	Monster* monster2 = Monster::create(Sprite::create("wolf.png"), MonsterType::normalFatTypeLv1);
	monster2->setPosition(400, 200);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	m_monsterScreen1List.pushBack(monster2);
	m_showedMonsterList.pushBack(monster2);
	this->addChild(monster2);

	Monster* monster3 = Monster::create(Sprite::create("wolf.png"), MonsterType::shootAggressiveTypeLv1);
	monster3->setPosition(400, 200);
	monster3->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster3);
	m_showedMonsterList.pushBack(monster3);
	m_monsterScreen1List.pushBack(monster3);
	this->addChild(monster3);

	//Rect rect = monster2->getBoundingBox();
	//auto s = Director::getInstance()->getWinSize();
	//auto draw = DrawNode::create();
	//this->addChild(draw, 10);
	////Vec2 points[] = { Vec2(0, 0), Vec2(rect.size.width, 0), Vec2(rect.size.width, rect.size.height), Vec2(0, rect.size.height) };
	//Vec2 points[] = { Vec2(rect.origin.x, rect.origin.y), Vec2(rect.origin.x + rect.size.width, rect.origin.y), Vec2(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height), Vec2(rect.origin.x, rect.origin.y + rect.size.height) };
	//draw->drawPolygon(points, sizeof(points) / sizeof(points[0]), Color4F(1, 0, 0, 0.5), 4, Color4F(0, 0, 1, 1));


	/*
	Monster* monster2 = Monster::create(Sprite::create("wolf.png"),MonsterType::shootTypeLv1);
	monster2->setPosition(600, 200);
	monster2->getFSM()->changeState(new StateUseSkill());
	m_monsterList.pushBack(monster2);
	this->addChild(monster2);*/


	//BOSS NUM 1
	//Vector<Monster*> number1BossShoot;

	//auto shoot = Monster::create(Sprite::create("CloseNormal.png"), MonsterType::num1ShootType);
	//shoot->setPosition(1000, 80);
	//shoot->getFSM()->changeState(new StateUseSkill());
	//number1BossShoot.pushBack(shoot);
	//m_monsterList.pushBack(shoot);
	////m_showedMonsterList.pushBack(shoot);

	//auto shoot2 = Monster::create(Sprite::create("CloseNormal.png"), MonsterType::num1ShootType);
	//shoot2->setPosition(100, 150);
	//shoot2->getFSM()->changeState(new StateUseSkill());
	//number1BossShoot.pushBack(shoot2);
	//m_monsterList.pushBack(shoot2);
	////m_showedMonsterList.pushBack(shoot2);

	//auto shoot3 = Monster::create(Sprite::create("CloseNormal.png"), MonsterType::num1ShootType);
	//shoot3->setPosition(1000, 160);
	//shoot3->getFSM()->changeState(new StateUseSkill());
	//number1BossShoot.pushBack(shoot3);
	//m_monsterList.pushBack(shoot3);
	////m_showedMonsterList.pushBack(shoot3);

	//Monster* monster2 = MonsterBossNum1::create(Sprite::create("wolf.png"), number1BossShoot);
	//monster2->setPosition(400, 200);
	//monster2->getFSM()->changeState(new BossStateUseSkill());
	//m_monsterList.pushBack(monster2);
	//m_showedMonsterList.pushBack(monster2);
	////monster2->setAnchorPoint(Vec2(0.5, 0.5));
	//this->addChild(monster2); 


	//Boss Number 2

	/*auto monster1 = Monster::create(Sprite::create("wolf.png"), MonsterType::monsterBossNum2Assister);
	monster1->setPosition(Vec2(1040,540));
	monster1->getFSM()->changeState(new StateAttack());
	m_monsterList.pushBack(monster1);
	this->addChild(monster1);

	auto box = Sprite::create("box2.png");
	box->setScale(0.5);
	box->setPosition(1100, 400);
	this->addChild(box);


	MonsterBossNum2* monster2 = MonsterBossNum2::create(Sprite::create("wolf.png"), monster1);
	monster2->setPosition(Vec2(200,200));
	monster2->getFSM()->changeState(new BossStateUseSkill());
	monster2->setAnchorPoint(Vec2(0.5,0.5));
	m_monsterList.pushBack(monster2);
	m_showedMonsterList.pushBack(monster2);
	this->addChild(monster2);*/

	//Rect rect = monster2->getBoundingBox();
	//auto s = Director::getInstance()->getWinSize();
	//auto draw = DrawNode::create();
	//this->addChild(draw, 10);
	////Vec2 points[] = { Vec2(0, 0), Vec2(rect.size.width, 0), Vec2(rect.size.width, rect.size.height), Vec2(0, rect.size.height) };
	//Vec2 points[] = { Vec2(rect.origin.x, rect.origin.y), Vec2(rect.origin.x + rect.size.width, rect.origin.y), Vec2(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height), Vec2(rect.origin.x, rect.origin.y + rect.size.height) };
	//draw->drawPolygon(points, sizeof(points) / sizeof(points[0]), Color4F(1, 0, 0, 0.5), 4, Color4F(0, 0, 1, 1));



	//Boss Number 3

	//Vector<Monster*> number3BossCar;
	//auto car1 = Monster::create(Sprite::create("car.png"), MonsterType::num3CarType);
	////car1->setPosition(1000, 375);
	//car1->getFSM()->changeState(new StateAttack());
	//number3BossCar.pushBack(car1);
	//
	//auto car2 = Monster::create(Sprite::create("car.png"), MonsterType::num3CarType);
	////car2->setPosition(1000, 225);
	//car2->getFSM()->changeState(new StateAttack());
	//number3BossCar.pushBack(car2);

	//auto car3 = Monster::create(Sprite::create("car.png"), MonsterType::num3CarType);
	////car3->setPosition(1000,75);
	//car3->getFSM()->changeState(new StateAttack());
	//number3BossCar.pushBack(car3);

	//Monster* monster3 = MonsterBossNum3::create(Sprite::create("wolf.png"), number3BossCar);
	//monster3->setPosition(200, 200);
	//monster3->getFSM()->changeState(new BossStateUseSkill());
	//m_monsterList.pushBack(monster3);
	//m_showedMonsterList.pushBack(monster3);
	//this->addChild(monster3,5);
	

	

}