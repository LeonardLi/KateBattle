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



USING_NS_CC;
using namespace cocostudio;
Hero::Hero() :
m_defaultSpeed(1.0f),
m_attackValue(10.0f),
m_attackSpeed(2.0f),
m_attackRange(100.0f),
m_defaultHp(100.0f),
m_curHp(2000.0f),
m_finnalHp(100.0f),
m_direction(JoystickEnum::DEFAULT),
m_canControl(true),
m_isDead(false),
m_moveController(nullptr),
m_armature(nullptr)
{}

Hero* Hero::create(){
	Hero* hero = new Hero();
	if (hero&&hero->init()){
		hero->autorelease();
	}
	else{
		CC_SAFE_DELETE(hero);
	}
	return hero;
}


bool Hero::init(){
	if (!Entity::init())
	{
		return false;
	}

	bool bRet = false;
	
	do 
	{
		_loadCSB("hero1/hero1.csb");
		
		bRet = true;
	} while (0);
	this->scheduleUpdate();
	return bRet;
}


void Hero::_loadCSB(std::string csbfile){
	mViewNode = static_cast<Node*>(CSLoader::createNode(csbfile));
	m_armature = static_cast<Armature*>(mViewNode->getChildByTag(21));
	//arm->setScale(-0.2,0.2);
	m_armature->getAnimation()->play("stand");
	
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setContentSize(Size(70, 120));

	this->addChild(mViewNode);
}

void Hero::update(float dt){
	if (getStun()!=STUN && m_isDead==false&&m_canControl==true)
	m_moveController->simpleMove(m_direction);

}


void Hero::ChangeDirection(JoystickEnum direction){
	
	m_direction = direction;
}

void Hero::onDead(){
	this->m_armature->getAnimation()->play("dead");

	//cast the animation
}

void Hero::onHurt(){
	//cast the animation
}

void Hero::changeStun(float dt){
	if (getStun() == STUN)
		setStun(NOTSTUN);
	this->m_armature->getAnimation()->play("stand");
}

void Hero::herostun(float time)
{
	this->m_armature->getAnimation()->play("hurt", -1, 0);
	setStun(STUN);
	if (this->isScheduled(schedule_selector(Hero::changeStun)))
	{
		this->unschedule(schedule_selector(Hero::changeStun));
		this->scheduleOnce(schedule_selector(Hero::changeStun), time);
	}
	else
	this->scheduleOnce(schedule_selector(Hero::changeStun), time);
	
}

void Hero::attack(){
	log("=========hero attack!!============");
	this->m_armature->getAnimation()->play("attack", -1, 0);
	Rect rect;
	if (this->m_moveController->leftOrRight == false)
	{
		rect = Rect(this->getPositionX() - this->getattackRange(), this->getPositionY()-30, this->getattackRange()-30, this->getattackRange() / 2+20);
	}
	else
	{
		rect = Rect(this->getPositionX() + this->getContentSize().width-20, this->getPositionY()-30, this->getattackRange() - 20.0f, this->getattackRange() / 2+20);
	}
	for (auto monster : m_heroMonsterList)
	{
		if (rect.intersectsRect(monster->getBoundingBox())&&monster->getisDead()==false&&monster->getcanAttack()==true)
		{
			monster->monsterGetHurt(this->getattackValue(), 0.0f);
			return;
		}
	}	
}

void Hero::heroNotControl(float time){
	m_canControl = false;
	this->scheduleOnce(schedule_selector(Hero::changeControlType), time);
}

void Hero::changeControlType(float dt){
	if (m_canControl == false)
		m_canControl = true;
}

void Hero::blink(){
	Vec2 desPoint;
	int direction;
	if (this->m_moveController->leftOrRight == false)
	{
		direction = 0;
		desPoint = Vec2(this->getPositionX() - 200, this->getPositionY());		
	}
	else
	{
		direction = 1;
		desPoint = Vec2(this->getPositionX() + 200, this->getPositionY());
	}
	for (auto monster : m_blockArea){
		Rect rect = monster->getBoundingBox();
		if (rect.containsPoint(desPoint))
		{
			if (direction==0)
			{
				desPoint = Vec2(rect.origin.x + rect.size.width, this->getPositionY());
			}
			else
				desPoint = Vec2(rect.origin.x, this->getPositionY());
		}
	}

	this->setPosition(desPoint);
}

void Hero::getHurt(float ivalue,float stunTime,float slowValue,float slowTime){
	this->onHurt();
	this->hurtMe(ivalue);

	float iCurHp = getcurHp();
	float iAfterHp = iCurHp - ivalue;

	if (iAfterHp > 0)
	{
		this->onHurt();
		setcurHp(iAfterHp);
	}
	//ËÀÍö
	else
	{
		this->setisDead(true);
		onDead();
		return;
	}

	if (stunTime>0)
	{
		this->herostun(stunTime);
	}
	if (slowValue>0.01)
	{
		this->changeSpeed(slowValue, slowTime);
	}
	
}

void Hero::changeSpeed(float slowValue, float slowTime){
	float speed = this->m_moveController->getiSpeed();
	if (speed==this->getDefaultSpeed())
	{
		this->m_moveController->setiSpeed(speed*(1-slowValue));
		if (this->isScheduled(schedule_selector(Hero::recoverSpeed)))
		{
			this->unschedule(schedule_selector(Hero::recoverSpeed));
			this->scheduleOnce(schedule_selector(Hero::recoverSpeed), slowTime);
		}
		else
		this->scheduleOnce(schedule_selector(Hero::recoverSpeed), slowTime);
	}
}

void Hero::recoverSpeed(float dt){
	this->m_moveController->setiSpeed(this->getDefaultSpeed());
}

void Hero::playAnimaitonAttack(Direction direction){
	if (direction == Direction::left)
	{
		m_armature->setScale(-0.2f, 0.2f);
		m_armature->getAnimation()->play("attack");
	}
	else
	{
		m_armature->setScale(0.2f, 0.2f);
		m_armature->getAnimation()->play("attack");
	}
}
void Hero::playAnimaitonStand(Direction direction){
	if (direction == Direction::left)
	{
		m_armature->setScale(-0.2f, 0.2f);
		m_armature->getAnimation()->play("stand");
	}
	else
	{
		m_armature->setScale(0.2f, 0.2f);
		m_armature->getAnimation()->play("stand");
	}

}
void Hero::playAnimaitonWalk(Direction direction){
	if (direction == Direction::left)
	{
		m_armature->setScale(-0.2f, 0.2f);
		m_armature->getAnimation()->play("walk");
	}
	else
	{
		m_armature->setScale(0.2f, 0.2f);
		m_armature->getAnimation()->play("walk");
	}
}
void Hero::playAnimaitonHurt(Direction direction){
	if (direction == Direction::left)
	{
		m_armature->setScale(-0.2f, 0.2f);
		m_armature->getAnimation()->play("hurt");
	}
	else
	{
		m_armature->setScale(0.2f, 0.2f);
		m_armature->getAnimation()->play("hurt");
	}
}
void Hero::playAnimaitonDead(Direction direction){
	if (direction == Direction::left)
	{
		m_armature->setScale(-0.2f, 0.2f);
		m_armature->getAnimation()->play("dead");
	}
	else
	{
		m_armature->setScale(0.2f, 0.2f);
		m_armature->getAnimation()->play("dead");
	}
}
