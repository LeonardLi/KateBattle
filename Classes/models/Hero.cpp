//
//  Hero.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "Hero.h"
#include "ControllerMoveBase.h"
#include "JoyStick.h"

#define LEFT 0
#define RIGHT 1
//ÉÁÏÖ
#define SKILLBLINKID 1
//ÎÞµÐ
#define SKILLUNCONQUER 2
#define SKILL3 3
#define SKILL4 4
#define SKILL5 5
#define SKILL6 6



USING_NS_CC;

Hero::Hero(){
}

Hero* Hero::create(Sprite* sprite){
	Hero* hero = new Hero();
	if (hero&&hero->init(sprite)){
		hero->autorelease();
	}
	else{
		CC_SAFE_DELETE(hero);
	}
	return hero;
}


bool Hero::init(Sprite* sprite){
	if (!Entity::init())
	{
		return false;
	}

	bool bRet = false;
	m_moveController = nullptr;
	m_direction = JoystickEnum::DEFAULT;
	m_Stun = NOTSTUN;
	m_canControl = true;
	m_heroDirection = RIGHT;
	do 
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);
		m_moveController = ControllerMoveBase::create(this);
		bRet = true;
	} while (0);
	this->scheduleUpdate();
	return bRet;
}

void Hero::update(float dt){
	if (m_Stun!=STUN && m_isDead==false&&m_canControl==true)
	m_moveController->simpleMove(m_direction);
}


void Hero::ChangeDirection(JoystickEnum direction){
	
	m_direction = direction;
}

void Hero::onDead(){
	//cast the animation
}

void Hero::onHurt(){
	//cast the animation
}

void Hero::changeStun(float dt){
	if (m_Stun == STUN)
		m_Stun = NOTSTUN;
}

void Hero::herostun(float time)
{
	mViewSprite->stopAllActions();
	m_Stun = STUN;
	this->scheduleOnce(schedule_selector(Hero::changeStun), time);
}

void Hero::attack(){
	log("attack!!============");
	if (mViewSprite->getNumberOfRunningActions()==0)
	{
		//run action
	}
}

void Hero::heroNotControl(float time){
	mViewSprite->stopAllActions();
	m_canControl = false;
	this->scheduleOnce(schedule_selector(Hero::changeControlType), time);
}

void Hero::changeControlType(float dt){
	if (m_canControl == false)
		m_canControl = true;
}

void Hero::getHurt(int ivalue,float stunTime){
	this->onHurt();
	this->hurtMe(ivalue);
	herostun(stunTime);
}