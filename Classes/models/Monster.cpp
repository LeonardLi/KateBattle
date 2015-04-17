//
//  Monster.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "Monster.h"
#include "MonsterFSM.h"
#include "BulletBase.h"
#include "BulletNormal.h"
#include "Hero.h"
#include "cocos2d.h"
#include "I_State.h"
#include "StateAttack.h"
#include "StateUseSkill.h"
#define SKILLRUSHSPEED 200
#define SPEEDRATE 0.5
USING_NS_CC;


Monster* Monster::create(Sprite* sprite, MonsterType type){
	Monster* monster = new Monster();
	if (monster&&monster->init(sprite,type))
	{
		monster->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monster);
	}
	return monster;
}

bool Monster::init(Sprite* sprite, MonsterType type){
	bool bRet = false;
	do
	{
		
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);
		m_FSM = MonsterFSM::createWithMonster(this);
		//set attribute
		setviewRange(1500.0);
		
		setattackTime(2.0f);
		//attackrange+100 = move range
		skillOrAttack = false;

		switch (type)
		{
		case  MonsterType::normalType:
			m_monsterType = MonsterType::normalType;
			setattackRange(100.0);
			break;
		case MonsterType::shootType:
			m_monsterType = MonsterType::shootType;
			setattackRange(400.0);
			break;
		case MonsterType::monsterBossNum1:
			m_monsterType = MonsterType::monsterBossNum1;
			setattackRange(200.0);
			break;
		case MonsterType::Num1ShootType:
			m_monsterType = MonsterType::Num1ShootType;
			setattackRange(1500.0);
		default:
			break;
		}
		bRet = true;
	} while (0);
	
	return bRet;
}

MonsterFSM* Monster::getFSM(){
	return this->m_FSM;
}

void Monster::attackSequence(){
	switch (m_monsterType)
	{
	case MonsterType::normalType:
	case MonsterType::monsterBossNum1:
		break;
	case MonsterType::shootType:
	
		__initBullet(1);
		break;

	case MonsterType::Num1ShootType:
		__initBullet(2);

		break;

	default:
		break;
	}
	log("monster attackSequence_______");
	this->__readyForAttack(1.0f);
}

void Monster::__initBullet(int bulletType){
	BulletBase* bullet = NULL;

	for (int i = 0; i < 10; i++)
	{
		switch (bulletType)
		{
		case 1:
			bullet = BulletNormal::create(Sprite::create("CloseNormal.png"));
			bullet->setBulletValue(10, 1.0f, 0.0f, 0.0f);
			break;
		case 2:
			bullet = BulletNormal::create(Sprite::create("CloseNormal.png"));
			bullet->setBulletValue(10, 0.0f, 0.5f, 5.0f);
			break;
		default:
			break;
		}		
		bullet->setUsed(false);
		m_bulletList.pushBack(bullet);
		this->getParent()->addChild(bullet);
	}
	this->schedule(schedule_selector(Monster::__bulletLogicCheck));
}

void Monster::__bulletLogicCheck(float dt){
	for (auto bullet : m_bulletList)
	{
		if (bullet->isUsed())
		{
			auto aim = bullet->getTarget();
			if (aim != NULL)
			{
				if (bullet->getBoundingBox().intersectsRect(targetHero->getBoundingBox()))
				{
					log("hero get hurt~~~~~~~");
					
						targetHero->getHurt(bullet->bulletDamage,bullet->bulletStunTime,bullet->bulletSlowDown,bullet->bulletSlowDownTime);
					
					bullet->stopAllActions();
					bullet->m_isArrive = true;
				}
				if (bullet->isArrive())
				{
					log("bullet Arrive!---------- - ");
					bullet->setUsed(false);
				}
			}
		}
	}
}

void Monster::__readyForAttack(float dt){
	if (this->getFSM()->getState()==MonsterFSM::toAttack||this->getFSM()->getState()==MonsterFSM::BossToAttack)
	{
		log("attack state!!~~");
		this->schedule(schedule_selector(Monster::__intoAttackSequence));
	}

	else
	{
		skillOrAttack = true;
	}
}

void Monster::__intoAttackSequence(float dt){
	if (skillOrAttack == false)
	{
		this->unschedule(schedule_selector(Monster::__intoAttackSequence));
		this->schedule(schedule_selector(Monster::__isInViewRange));
	}
}

void Monster::__isInViewRange(float dt){
	Vec2 distance = Vec2(heroLocation.x - this->getPositionX(), heroLocation.y - this->getPositionY());
	if (distance.length() <= this->getviewRange())
	{
		log("hero  InView!!!!!!!!!!");
		__attack();
		this->unschedule(schedule_selector(Monster::__isInViewRange));
	}
}

void Monster::__attack(){
	float randomNum = CCRANDOM_0_1();
	float moveAndAttack = 0.25;
	float standRate = 0.1;
	
	switch (m_monsterType)
	{
	case MonsterType::Num1ShootType:
		//never random move
		moveAndAttack = 0.5;
		standRate = 0.5;
		break;
	default:
		break;
	}
		
	if (randomNum > moveAndAttack)
	{
		log("move to hero!!!!!!");
		this->schedule(schedule_selector(Monster::__monsterMoveToHero));
	}
	else if (randomNum >= standRate&&randomNum <= moveAndAttack)
	{
		log("random move!!!!");
		__monsterRandomMove();
	}
	else if (randomNum>0 && randomNum<standRate)
	{
		log("stand for 2s~~~~");
		this->scheduleOnce(schedule_selector(Monster::__readyForAttack), 2.0f);
	}
}

void Monster::__monsterMoveToHero(float dt){
	Vec2 distance = Vec2(heroLocation.x - this->getPositionX(), heroLocation.y - this->getPositionY());
	if (distance.length() > this->getattackRange())
	{
		__moveCloseToHero(distance);
	}
	else
	{
		log("hero in range");
		this->unschedule(schedule_selector(Monster::__monsterMoveToHero));
		this->__attackafterMove();
	}
	if (CCRANDOM_0_1() < 0.001)
	{
		//stop
		this->unschedule(schedule_selector(Monster::__monsterMoveToHero));
		this->scheduleOnce(schedule_selector(Monster::__readyForAttack), 2.0f);
	}
}

void Monster::__monsterRandomMove(){
	Vec2 move = Vec2(0, 0);
	float randomNumX = (CCRANDOM_0_1()-0.5)*80;
	float randomNumY = (CCRANDOM_0_1()-0.5)*100;

	if (this->getPositionY()<75&&randomNumY<0)
	{
		randomNumY*=(-1);
	}
	if (this->getPositionY()>800&&randomNumY>0)
	{
		randomNumY *= (-1);
	}

	move = Vec2(randomNumX, randomNumY);
	
	this->runAction(MoveBy::create(1.0f, move));
	this->scheduleOnce(schedule_selector(Monster::__readyForAttack), 2.0f);
}

void Monster::__attackafterMove(){
	float randomNum = CCRANDOM_0_1();
	if (randomNum > 0.25)
	{
		log("monster attack!!! after move ");
		switch (m_monsterType)
		{
		case MonsterType::monsterBossNum1:
		case MonsterType::normalType:
			
			//this->schedule();
			__attackWithHand();
			break;
		case MonsterType::shootType:
		case MonsterType::Num1ShootType:
			__attackWithBullet();
			break;
		default:
			break;
		}
	}
	else
	{
		log("stand---------------");
	}
	this->scheduleOnce(schedule_selector(Monster::__finishAttack), m_attackTime);
}

void Monster::__attackWithHand(){
	float num = CCRANDOM_0_1();
	if (num < 0.8)
	{
		this->__postBossSkillMessage(1.0f);
	}
	log("attack with hand!");
}

void Monster::__attackWithBullet(){
	BulletBase* bullet = this->__getAnyUnUsedBullet();
	if (bullet != NULL)
	{
		bullet->setPosition(this->getPosition());
		bullet->onLockAim(targetHero);
	}

}

BulletBase* Monster::__getAnyUnUsedBullet(){
	for (auto bullet : m_bulletList)
	{
		if (bullet->isUsed() == false)
		{
			bullet->setUsed(true);
			return bullet;
		}
	}
	return NULL;
}

void Monster::__finishAttack(float dt){
	this->__readyForAttack(1.0f);
	log("finish attack~~~~");
}

void Monster::useSkillSequence(){
	__readyForUseSkill(0.0f);
}

void Monster::__readyForUseSkill(float dt){
	if (this->getFSM()->getState() == MonsterFSM::toUseSkill)
	{
		this->m_Stun = 1;
		this->schedule(schedule_selector(Monster::__intoSkillSequence));
		log("ready to skill!!~~");
	}

	if (this->getFSM()->getState() == MonsterFSM::BosstoUseSkill)
	{
		this->m_Stun = 1;
		this->schedule(schedule_selector(MonsterBossNum1::__intoSkillSequence));
		log("ready to skill!!~~");
	}

	else
	{
		skillOrAttack = false;
	}
}

void Monster::__intoSkillSequence(float dt){
	if (skillOrAttack == true)
	{
		this->unschedule(schedule_selector(Monster::__intoSkillSequence));
		this->__skill();
	}

}

void Monster::__skill(){
	switch (m_monsterType)
	{
	case MonsterType::monsterBossNum1:
		log("Boss1 Skill~~~~~~~~");

		this->scheduleOnce(schedule_selector(MonsterBossNum1::skillRushBox), 0.0f);
		this->schedule(schedule_selector(Monster::skillRush), 0.0, kRepeatForever, 5.0f);
		//rushskill
		/*float x = heroLocation.x;
		float y = heroLocation.y;
		float x1 = this->getPositionX();
		float y1 = this->getPositionY();

		float time = sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1)) / SKILLRUSHSPEED;
		this->runAction(MoveTo::create(time, heroLocation));*/
		break;

	default:
		break;
	}
}

void Monster::__skillRushBox(float dt){
	auto box = Monster::create(Sprite::create("wolf.png"), MonsterType::block);
	float num = CCRANDOM_0_1();
	Vec2 boxPoint = Vec2(0, 0);
	
	

	if (num<0.25)
	{
		boxPoint = Vec2(600, 400);
	}
	else if (num>0.25&&num<0.5)
	{
		boxPoint = Vec2(200, 400);
	}
	else if (num >= 0.5&&num < 0.75)
	{
		boxPoint = Vec2(200, 200);
	}
	else
		boxPoint = Vec2(600, 200);

	box->setPosition(boxPoint);
	this->getParent()->addChild(box);
	m_boxes = box;


	this->schedule(schedule_selector(Monster::isCollide));
}

void Monster::__moveCloseToHero(Vec2 distance){
	Vec2 speed = distance / distance.length();
	speed.x *= SPEEDRATE;
	speed.y *= SPEEDRATE;
	this->setPosition(this->getPositionX() + speed.x, this->getPositionY() + speed.y);
}

void Monster::skillRush(float dt){
	if (this->m_Stun == 0)
	{
		this->unschedule(schedule_selector(Monster::skillRush));
		this->scheduleOnce(schedule_selector(Monster::__skillFinish), 5.0f);

	}
	else
	{
		Vec2 distance = Vec2(heroLocation.x - this->getPositionX(), heroLocation.y - this->getPositionY());
		Vec2 speed = distance / distance.length();
		speed.x *= 1.0;
		speed.y *= 1.0;
		this->setPosition(this->getPositionX() + speed.x, this->getPositionY() + speed.y);	
	}
}

void Monster::__skillFinish(float dt){
	log("finishskill!");
	skillOrAttack = false;
	__postBossAttackMessage(1.0f);
	//readyForUseSkill(1.0f);
}

void Monster::isCollide(float dt){
	if (this->getBoundingBox().intersectsRect(m_boxes->getBoundingBox()))
	{	
		this->unschedule(schedule_selector(Monster::isCollide));
		this->m_Stun = STUN;
		this->targetHero->m_blockArea.eraseObject(m_boxes);
		this->getParent()->removeChild(m_boxes);
	}
}

void Monster::__postBossAttackMessage(float dt){
	this->getFSM()->OnRecvBossWantToAttack(this);
}

void Monster::__postBossSkillMessage(float dt){
	this->getFSM()->OnRecvBossWantToUseSkill(this);
}


void Monster::onDead(){
	CCASSERT(false," ");
	
}

void Monster::onHurt(){
	CCASSERT(false, " ");
}

void Monster::update(float dt){
}

void Monster::monsterGetHurt(int iValue, int time){

}




MonsterBossNum1* MonsterBossNum1::create(Sprite* sprite, Vector<Monster*> monsterList){
	MonsterBossNum1* number1Boss = new MonsterBossNum1();
	if (number1Boss&&number1Boss->init(sprite, monsterList))
	{
		number1Boss->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(number1Boss);
	}
	return number1Boss;
}

bool MonsterBossNum1::init(Sprite* sprite, Vector<Monster*> monsterList){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);
		m_FSM = MonsterFSM::createWithMonster(this);

		shootMonsterList = monsterList;
		//set attribute
		setviewRange(700.0);

		setattackTime(2.0f);
		//attackrange+100 = move range
		skillOrAttack = false;	
		m_monsterType = MonsterType::monsterBossNum1;
		setattackRange(200.0);
		bRet = true;
	} while (0);
	return bRet;
}

void MonsterBossNum1::skillRushBox(float dt){
	auto box = Monster::create(Sprite::create("wolf.png"), MonsterType::block);
	Vec2 boxPoint = Vec2(0, 0);

	
	
	float locationX = this->getPositionX();
	float locationY = this->getPositionY();
	if (locationX<=400&&locationY<=300)
	{
		boxPoint = Vec2(600, 400);
	}

	else if (locationX > 400 && locationY <= 300)
	{
		boxPoint = Vec2(200, 400);
	}
	else if (locationX > 400 && locationY > 300)
	{
		boxPoint = Vec2(200, 200);
	}
	else
		boxPoint = Vec2(600, 200);

	box->setPosition(boxPoint);
	this->getParent()->addChild(box);
	m_boxes = box;
	
	targetHero->m_blockArea.pushBack(box);

	static int monsterExist = 0;
	if (monsterExist <= 3)
	{
		auto monster = shootMonsterList.at(monsterExist);
		this->getParent()->addChild(monster);
		monster->getFSM()->OnRecvWantToAttack(monster);
		monsterExist ++;
	}

	this->schedule(schedule_selector(Monster::isCollide));
}
