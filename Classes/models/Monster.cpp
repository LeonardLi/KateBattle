//
//  Monster.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "Monster.h"
#include "MonsterFSM.h"
#include "cocos2d.h"
#define SKILLRUSHSPEED 200
#define SPEEDRATE 0.5
#define RANDOMMOVEKEY "randommove"
USING_NS_CC;
Monster* Monster::create(Sprite* sprite){
	Monster* monster = new Monster();
	if (monster&&monster->init(sprite))
	{
		monster->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monster);
	}
	return monster;
}

bool Monster::init(Sprite* sprite){
	bool bRet = false;
	
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);
		m_FSM = MonsterFSM::createWithMonster(this);
		setattackRange(100.0);
		setattackTime(2.0f);
		bRet = true;
	} while (0);
	return bRet;
}

MonsterFSM* Monster::getFSM(){
	return this->m_FSM;
}


void Monster::attackSequence(){
	log("monster attackSequence_______");
	this->readyForAttack(1.0f);
}

void Monster::readyForAttack(float dt){
	log("ready to move!!~~");
	if (this->isScheduled(schedule_selector(Monster::readyForAttack)))
		this->unschedule(schedule_selector(Monster::readyForAttack));
	this->attack(dt);
}

void Monster::attack(float dt){
	float randomNum = CCRANDOM_0_1();
	if (randomNum<0.6)
	{
		log("move to hero!!!!!!");
		this->schedule(schedule_selector(Monster::monsterMoveToHero));
	}
	else if (randomNum >= 0.6&&randomNum <= 0.9)
	{
		log("random move!!!!");
		float randomSpeed = 0;
		if (randomNum >= 0.75)
			randomSpeed = 1.0;
		else
			randomSpeed = -1.0;
		this->schedule(CC_CALLBACK_1(Monster::monsterRandomMove, this, randomSpeed), RANDOMMOVEKEY);

	}
	else
	{
		log("stand for 2s~~~~");
		this->schedule(schedule_selector(Monster::readyForAttack), 2.0f);
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
}

void Monster::monsterRandomMove(float dt,float randomSpeed){
	static int num=0;
	this->setPositionX(this->getPositionX() + randomSpeed);
	num++;
	if (num>=50)
	{
		this->unschedule(RANDOMMOVEKEY);
		this->schedule(schedule_selector(Monster::readyForAttack), 2.0f);
		num = 0;
	}
}

void Monster::monsterStay(float dt){

}

void Monster::attackafterMove(float attackColdTime){
	if (CCRANDOM_0_1() > 0.3)
		log("monster attack!!! after move ");
	else
		log("just stand");

	this->scheduleOnce(schedule_selector(Monster::attack), attackColdTime);

}