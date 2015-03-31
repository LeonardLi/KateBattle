#include "ControllerMoveBase.h"
USING_NS_CC;
ControllerMoveBase::ControllerMoveBase(){
	m_isMoving = false;
	m_entity = nullptr;
	m_iSpeed = SPEED;
}

ControllerMoveBase::~ControllerMoveBase(){

}

ControllerMoveBase* ControllerMoveBase::create(Entity* entity){
	ControllerMoveBase* ctrMoveBase = new ControllerMoveBase();

	if (ctrMoveBase&&ctrMoveBase->init(entity)){
		ctrMoveBase->autorelease();
	}
	else{
		CC_SAFE_DELETE(ctrMoveBase);
	}
	return ctrMoveBase;

}

bool ControllerMoveBase::init(Entity* entity){
	this->m_entity = entity;
	return true;
}

void ControllerMoveBase::simpleMove(JoystickEnum direction){
	Sprite* sprite = m_entity->getSprite();
	if (sprite != nullptr)
	{
		heroDirection = direction;
		this->scheduleUpdate();
	}
				
}

void ControllerMoveBase::update(float dt){
	Point pos = m_entity->getPosition();
	switch (heroDirection)
	{
	
	case JoystickEnum::D_UP:
		m_entity->setPosition(pos.x, pos.y + SPEED);
		break;
	case JoystickEnum::D_DOWN:
		m_entity->setPosition(pos.x, pos.y - SPEED);
		break;
	case JoystickEnum::D_LEFT:
		m_entity->setPosition(pos.x - SPEED, pos.y);
		break;
	case JoystickEnum::D_RIGHT:
		m_entity->setPosition(pos.x + SPEED, pos.y);
		break;
	case JoystickEnum::D_LEFT_UP:
		m_entity->setPosition(pos.x - SPEED, pos.y + SPEED);
		break;
	case JoystickEnum::D_RIGHT_UP:
		m_entity->setPosition(pos.x + SPEED, pos.y + SPEED);
		break;
	case JoystickEnum::D_LEFT_DOWN:
		m_entity->setPosition(pos.x - SPEED, pos.y - SPEED);
		break;
	case JoystickEnum::D_RIGHT_DOWN:
		m_entity->setPosition(pos.x + SPEED, pos.y - SPEED);
		break;
	case JoystickEnum::DEFAULT:
		break;
	


	}


}