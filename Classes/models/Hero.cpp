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
	bool bRet = false;
	m_moveController = nullptr;
	m_direction = JoystickEnum::DEFAULT;

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
	m_moveController->simpleMove(m_direction);
}


void Hero::ChangeDirection(JoystickEnum direction){
	m_direction = direction;
}

void Hero::onDead(){

}

void Hero::onHurt(){
	
}