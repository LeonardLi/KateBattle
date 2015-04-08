#include "ControllerMoveBase.h"
#include "Hero.h"
#include "JoyStick.h"
#define SPEED 1
#define LEFT 0
#define RIGHT 1
USING_NS_CC;

ControllerMoveBase::ControllerMoveBase(){

}

ControllerMoveBase::~ControllerMoveBase(){

}

ControllerMoveBase* ControllerMoveBase::create(Hero* hero){
	ControllerMoveBase* ctrMoveBase = new ControllerMoveBase();

	if (ctrMoveBase && ctrMoveBase->init(hero)){
	}
	else{
		CC_SAFE_DELETE(ctrMoveBase);
	}
	return ctrMoveBase;

}

bool ControllerMoveBase::init(Hero* hero){
	if (hero == nullptr)
	{
		return false;
	}

	m_isMoving = false;
	m_hero = nullptr;
	m_iSpeed = SPEED;
	this->m_hero = hero;
	return true;
}

void ControllerMoveBase::simpleMove(JoystickEnum direction){
	if (m_hero->getSprite() != nullptr)
	{
		heroDirection = direction;
	}
	else{
		CCASSERT(false,"not bind sprite");
	}

	Point pos = m_hero->getPosition();
	switch (heroDirection)
	{

	case JoystickEnum::D_UP:
		m_hero->setPosition(pos.x, pos.y + SPEED);
		break;
	case JoystickEnum::D_DOWN:
		m_hero->setPosition(pos.x, pos.y - SPEED);
		break;
	case JoystickEnum::D_LEFT:
		m_hero->m_heroDirection = LEFT;
		m_hero->setPosition(pos.x - SPEED, pos.y);
		break;
	case JoystickEnum::D_RIGHT:
		m_hero->m_heroDirection = RIGHT;
		m_hero->setPosition(pos.x + SPEED, pos.y);
		break;
	case JoystickEnum::D_LEFT_UP:
		m_hero->m_heroDirection = LEFT;
		m_hero->setPosition(pos.x - SPEED, pos.y + SPEED);
		break;
	case JoystickEnum::D_RIGHT_UP:
		m_hero->m_heroDirection = RIGHT;
		m_hero->setPosition(pos.x + SPEED, pos.y + SPEED);
		break;
	case JoystickEnum::D_LEFT_DOWN:
		m_hero->m_heroDirection = LEFT;
		m_hero->setPosition(pos.x - SPEED, pos.y - SPEED);
		break;
	case JoystickEnum::D_RIGHT_DOWN:
		m_hero->m_heroDirection = RIGHT;
		m_hero->setPosition(pos.x + SPEED, pos.y - SPEED);
		break;
	case JoystickEnum::DEFAULT:
		break;



	}
				
}
