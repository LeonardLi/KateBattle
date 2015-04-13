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
#define SKILLRUSHSPEED 200
#define SPEEDRATE 0.5
USING_NS_CC;
Monster* Monster::create(Sprite* sprite,int type){
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

bool Monster::init(Sprite* sprite,int type){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);
		m_FSM = MonsterFSM::createWithMonster(this);
		setviewRange(700.0);
		
		setattackTime(2.0f);
		switch (type)
		{
		case  normalType:
			m_monsterType = normalType;
			setattackRange(100.0);
			break;
		case shootType:
			m_monsterType = shootType;
			setattackRange(400.0);
			break;
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
	case normalType:
		break;
	case shootType:
		initBullet();
		break;
	default:
		break;
	}
	log("monster attackSequence_______");
	this->readyForAttack(1.0f);

}

void Monster::readyForAttack(float dt){
	log("ready to move!!~~");
	this->schedule(schedule_selector(Monster::isInViewRange));	
}

void Monster::attack(float dt){
	float randomNum = CCRANDOM_0_1();
	if (randomNum>0.25)
	{
		log("move to hero!!!!!!");
		this->schedule(schedule_selector(Monster::monsterMoveToHero));
	}
	else if (randomNum >= 0.1&&randomNum <= 0.25)
	{
		log("random move!!!!");
		monsterRandomMove();
	}
	else
	{
		log("stand for 2s~~~~");
		this->scheduleOnce(schedule_selector(Monster::readyForAttack), 2.0f);
	}
}

void Monster::useSkillSequence(){
	
	//rushskill
	/*float x = heroLocation.x;
	float y = heroLocation.y;
	float x1 = this->getPositionX();
	float y1 = this->getPositionY();

	float time = sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1)) / SKILLRUSHSPEED;
	this->runAction(MoveTo::create(time, heroLocation));*/
	log("monster skill");
}

void Monster::onDead(){
	CCASSERT(false," ");
	
}

void Monster::onHurt(){
	CCASSERT(false, " ");
}

void Monster::update(float dt){
}

void Monster::monsterMoveToHero(float dt){
	Vec2 distance = Vec2(heroLocation.x - this->getPositionX(), heroLocation.y - this->getPositionY());
	if (distance.length() > this->getattackRange())
	{		
		Vec2 speed = distance / distance.length();
		speed.x *= SPEEDRATE;
		speed.y *= SPEEDRATE;
		this->setPosition(this->getPositionX() + speed.x, this->getPositionY() + speed.y);
	}
	else
	{
		log("hero in range");
		this->unschedule(schedule_selector(Monster::monsterMoveToHero));
		this->attackafterMove(m_attackTime);
	}

	if (CCRANDOM_0_1()<0.001)
	{
		//stop
		this->unschedule(schedule_selector(Monster::monsterMoveToHero));
		this->scheduleOnce(schedule_selector(Monster::readyForAttack), 2.0f);
	}
}

void Monster::monsterRandomMove(){
	Vec2 move = Vec2(0, 0);
	float randomNum = CCRANDOM_0_1();
	if (randomNum <0.25)
	{
		move = Vec2(50, 0);
	}
	else if (randomNum >= 0.25&&randomNum<0.5)
	{
		move = Vec2(-50, 0);
	}
	else if (randomNum >= 0.5&&randomNum < 0.75)
	{
		if (this->getPositionY()>=800)
		{
			move = Vec2(0, -50);
		}
		else
		move = Vec2(0, 50);
	}
	else
	{
		if (this->getPositionY() <= 75)
		{
			move = Vec2(0, 50);
		}
		else
			move = Vec2(0, -50);
	}
	
	this->runAction(MoveBy::create(1.0f, move));
	this->scheduleOnce(schedule_selector(Monster::readyForAttack), 2.0f);
	
}

void Monster::attackafterMove(float attackColdTime){
	if (CCRANDOM_0_1() > 0.3)
	{
		log("monster attack!!! after move ");
		switch (m_monsterType)
		{
		case normalType:
			attackWithHand();
			break;
		case shootType:
			attackWithBullet(1);
			break;	
		default:
			break;
		}	
	}
	else
	log("just stand");
	this->scheduleOnce(schedule_selector(Monster::attack), attackColdTime);
	
}

void Monster::isInViewRange(float dt){
	Vec2 distance = Vec2(heroLocation.x - this->getPositionX(), heroLocation.y - this->getPositionY());
	if (distance.length() <= this->getviewRange())
	{
		attack(dt);
		this->unschedule(schedule_selector(Monster::isInViewRange));
	}
}

void Monster::attackWithHand(){
	log("attack with hand!");
}

void Monster::attackWithBullet(int bulletType){
	BulletBase* bullet = this->getAnyUnUsedBullet();
	if (bullet!=NULL)
	{
		bullet->setPosition(this->getPosition());
		bullet->onLockAim(targetHero);
	}

}

void Monster::initBullet(){
	BulletBase* bullet = NULL;
	for (int i = 0; i <10; i++)
	{
		bullet = BulletNormal::create(Sprite::create("CloseNormal.png"));
		bullet->setUsed(false);
		m_bulletList.pushBack(bullet);
		this->getParent()->addChild(bullet);
	}
	this->schedule(schedule_selector(Monster::bulletLogicCheck));
}

void Monster::bulletLogicCheck(float dt){
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
					targetHero->getHurt(10,1.0f);
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

BulletBase* Monster::getAnyUnUsedBullet(){
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

