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
m_defaultSpeed(1.0),
m_direction(JoystickEnum::DEFAULT),
m_canControl(true),
m_moveController(nullptr)
{}

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
	
	do 
	{
		CC_BREAK_IF(!sprite);
		_loadCSB("hero1/hero1.csb");
		//bindSprite(sprite);
		//m_moveController = ControllerMoveBase::create(this);
		bRet = true;
	} while (0);
	this->scheduleUpdate();
	return bRet;
}


void Hero::_loadCSB(std::string csbfile){
	mViewNode = static_cast<Node*>(CSLoader::createNode(csbfile));
	Armature* arm = static_cast<Armature*>(mViewNode->getChildByTag(21));
	arm->getAnimation()->play("walk");
	this->setAnchorPoint(Vec2(0.5, 0.5));
	this->setContentSize(Size(70, 90));

	this->addChild(mViewNode);
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
	//mViewSprite->stopAllActions();
	m_Stun = STUN;
	if (this->isScheduled(schedule_selector(Hero::changeStun)))
	{
		this->unschedule(schedule_selector(Hero::changeStun));
		this->scheduleOnce(schedule_selector(Hero::changeStun), time);
	}
	else
	this->scheduleOnce(schedule_selector(Hero::changeStun), time);
	
}

void Hero::attack(){
	log("attack!!============");
	//if (mViewSprite->getNumberOfRunningActions()==0)
	//{
		//run action
	//}
}

void Hero::heroNotControl(float time){
	//mViewSprite->stopAllActions();
	m_canControl = false;
	this->scheduleOnce(schedule_selector(Hero::changeControlType), time);
}

void Hero::changeControlType(float dt){
	if (m_canControl == false)
		m_canControl = true;
}

void Hero::getHurt(float ivalue,float stunTime,float slowValue,float slowTime){
	this->onHurt();
	this->hurtMe(ivalue);
	if (slowTime>0)
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