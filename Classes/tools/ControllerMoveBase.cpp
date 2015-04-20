#include "ControllerMoveBase.h"
#include "Hero.h"
#include "Monster.h"
#include "JoyStick.h"
#define SPEED 1

#define LEFT 2
#define RIGHT 3





USING_NS_CC;

ControllerMoveBase::ControllerMoveBase(){

}

ControllerMoveBase::~ControllerMoveBase(){

}

ControllerMoveBase* ControllerMoveBase::create(Hero* hero, Sprite* map){
	ControllerMoveBase* ctrMoveBase = new ControllerMoveBase();

	if (ctrMoveBase && ctrMoveBase->init(hero, map)){
	}
	else{
		CC_SAFE_DELETE(ctrMoveBase);
	}
	return ctrMoveBase;

}

bool ControllerMoveBase::init(Hero* hero, Sprite* map){
	if (hero == nullptr || map == nullptr)
	{
		return false;
	}

	m_isMoving = false;
	m_hero = nullptr;
	m_iSpeed = SPEED;
	this->m_hero = hero;
	this->m_map = map;
	return true;
}

void ControllerMoveBase::judgeBlock(){
	for (auto monster : m_hero->m_blockArea){
		if (m_hero->getBoundingBox().intersectsRect(monster->getBoundingBox()))
		{
			float heroRightLineX = m_hero->getPositionX() + m_hero->getContentSize().width / 2;
			float heroLeftLineX = m_hero->getPositionX() - m_hero->getContentSize().width / 2;
			float heroUpLineY = m_hero->getPositionY() + m_hero->getContentSize().height / 2;
			float heroDownLineY = m_hero->getPositionY() - m_hero->getContentSize().height / 2;

			float blockRightLineX = monster->getPositionX() + monster->getContentSize().width / 2;
			float blockLeftLineX = monster->getPositionX() - monster->getContentSize().width / 2;
			float blockUpLineY = monster->getPositionY() + monster->getContentSize().height / 2;
			float blockDownLineY = monster->getPositionY() - monster->getContentSize().height / 2;

			float isUpThanBlock = (heroUpLineY - blockUpLineY)*(heroUpLineY - blockDownLineY);
			float isDownThanBlock = (heroDownLineY - blockUpLineY)*(heroDownLineY - blockDownLineY);
			float isLeftThanBlock = (heroLeftLineX - blockLeftLineX)*(heroLeftLineX - blockRightLineX);
			float isRightThanBlock = (heroRightLineX - blockLeftLineX)*(heroRightLineX - blockRightLineX);
			
		
			if (isUpThanBlock > 0 && isDownThanBlock > 0 || isUpThanBlock < 0 && isDownThanBlock < 0)
			{
				if (isLeftThanBlock>=0&&isRightThanBlock<=0)
				{
					isAllowToRight = false;
					isAllowToRightDown = false;
					isAllowToRightUp = false;
					log("mid--left");
				}
				if (isLeftThanBlock <= 0 && isRightThanBlock >= 0)
				{
					isAllowToLeft = false;
					isAllowToLeftDown = false;
					isAllowToLeftUp = false;
					log("mid---right");
				}		
			}

			else if (isLeftThanBlock > 0 && isRightThanBlock > 0 || isLeftThanBlock < 0 && isRightThanBlock < 0)
			{
				if (isUpThanBlock>=0&&isDownThanBlock<=0)
				{
					isAllowToDown = false;
					isAllowToLeftDown = false;
					isAllowToRightDown = false;
					log("mid  up");
				}
				if (isUpThanBlock<=0&&isDownThanBlock>=0)
				{
					isAllowToUp = false;
					isAllowToRightUp = false;
					isAllowToLeftUp = false;
					log("mid down");
				}
			}


			else if (isUpThanBlock <= 0 && isDownThanBlock >= 0 && isLeftThanBlock >= 0 && isRightThanBlock <= 0)
			{
				isAllowToUp = false;
				isAllowToRightUp = false;
				isAllowToRight = false;
				isAllowToLeftUp = false;
				isAllowToRightDown = false;
				log("zuo xia colide!!!!!!!!!!!!");
			}
			else if (isUpThanBlock >= 0 && isDownThanBlock <= 0 && isLeftThanBlock >= 0 && isRightThanBlock <= 0)
			{
				isAllowToRight = false;
				isAllowToDown = false;
				isAllowToRightDown = false;
				isAllowToRightUp = false;
				isAllowToLeftDown = false;
				log("zuo shang colide!!!!!!!!!!!!");
			}
			else if (isUpThanBlock >= 0 && isDownThanBlock <= 0 && isLeftThanBlock <= 0 && isRightThanBlock >= 0)
			{
				isAllowToLeftDown = false;
				isAllowToLeft = false;
				isAllowToDown = false;
				isAllowToLeftUp = false;
				isAllowToRightDown = false;
				log("you shang colide!!!!!!!!!!!!");
			}
			else if (isUpThanBlock <= 0 && isDownThanBlock >= 0 && isLeftThanBlock <= 0 && isRightThanBlock >= 0)
			{
				isAllowToUp = false;
				isAllowToLeftUp = false;
				isAllowToLeft = false;
				isAllowToRightUp = false;
				isAllowToLeftDown = false;
				log("you xia colide!!!!!!!!!!!!");
			}
		}
	}
}

void ControllerMoveBase::blockHeroDirection(){


}

void ControllerMoveBase::resetHeroDirection(){
	isAllowToLeft=true;
	isAllowToRight=true;
	isAllowToUp=true;
	isAllowToDown=true;
	isAllowToLeftUp=true;
	isAllowToLeftDown=true;
	isAllowToRightUp=true;
	isAllowToRightDown=true;
}


void ControllerMoveBase::simpleMove(JoystickEnum direction){
	
	heroDirection = direction;
	

	Point pos = m_hero->getPosition();
	float moveSpeed = this->getiSpeed();
	resetHeroDirection();
	judgeBlock();
	
	switch (heroDirection)
	{

	case JoystickEnum::D_UP:
		if (isAllowToUp)
		{
			m_hero->setPosition(pos.x, pos.y + moveSpeed);
		}
		break;
	case JoystickEnum::D_DOWN:
		if (isAllowToDown)
		{
			m_hero->setPosition(pos.x, pos.y - moveSpeed);
		}
		break;
	case JoystickEnum::D_LEFT:
		
		if (isAllowToLeft)
		{
			m_hero->m_heroDirection = LEFT;
			m_hero->setPosition(pos.x - moveSpeed, pos.y);
		}	
		break;
	case JoystickEnum::D_RIGHT:	
		if (isAllowToRight)
		{
			m_hero->m_heroDirection = RIGHT;
			m_hero->setPosition(pos.x + moveSpeed, pos.y);
		}	
		break;
	case JoystickEnum::D_LEFT_UP:
		if (isAllowToLeftUp)
		{
			m_hero->m_heroDirection = LEFT;
			m_hero->setPosition(pos.x - moveSpeed, pos.y + moveSpeed);
		}		
		break;
	case JoystickEnum::D_RIGHT_UP:
		if (isAllowToRightUp)
		{
			m_hero->m_heroDirection = RIGHT;
			m_hero->setPosition(pos.x + moveSpeed, pos.y + moveSpeed);
		}	
		break;
	case JoystickEnum::D_LEFT_DOWN:
		if (isAllowToLeftDown)
		{
			m_hero->m_heroDirection = LEFT;
			m_hero->setPosition(pos.x - moveSpeed, pos.y - moveSpeed);
		}	
		break;
	case JoystickEnum::D_RIGHT_DOWN:
		if (isAllowToRightDown)
		{
			m_hero->m_heroDirection = RIGHT;
			m_hero->setPosition(pos.x + moveSpeed, pos.y - moveSpeed);
		}
		break;
	case JoystickEnum::DEFAULT:
		break;
	}
				
}
