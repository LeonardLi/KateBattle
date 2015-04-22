#include "ControllerMoveBase.h"
#include "Hero.h"
#include "Monster.h"
#include "JoyStick.h"
#define SPEED 1

#define LEFT 2
#define RIGHT 3





USING_NS_CC;

ControllerMoveBase::ControllerMoveBase() :
m_isMoving(false),
m_hero(nullptr),
m_map(nullptr),
m_iSpeed(SPEED),
m_isLeft(false),
m_isRight(false),
m_isStand(false),
m_isUp(false),
m_isDown(false)
{

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
				if (isLeftThanBlock >= 0 && isRightThanBlock <= 0)
				{
					setisAllowToRight(false);
					setisAllowToRightDown(false);
					setisAllowToRightUp(false);
					log("mid--left");
				}
				if (isLeftThanBlock <= 0 && isRightThanBlock >= 0)
				{
					setisAllowToLeft(false);
					setisAllowToLeftDown(false);
					setisAllowToLeftUp(false);
					log("mid---right");
				}
			}

			else if (isLeftThanBlock > 0 && isRightThanBlock > 0 || isLeftThanBlock < 0 && isRightThanBlock < 0)
			{
				if (isUpThanBlock >= 0 && isDownThanBlock <= 0)
				{
					setisAllowToDown(false);
					setisAllowToLeftDown(false);
					setisAllowToRightDown(false);
					log("mid  up");
				}
				if (isUpThanBlock <= 0 && isDownThanBlock >= 0)
				{
					setisAllowToUp(false);
					setisAllowToRightUp(false);
					setisAllowToLeftUp(false);
					log("mid down");
				}
			}


			else if (isUpThanBlock <= 0 && isDownThanBlock >= 0 && isLeftThanBlock >= 0 && isRightThanBlock <= 0)
			{
				setisAllowToUp(false);
				setisAllowToRightUp(false);
				setisAllowToRight(false);
				setisAllowToLeftUp(false);
				setisAllowToRightDown(false);
				log("zuo xia colide!!!!!!!!!!!!");
			}
			else if (isUpThanBlock >= 0 && isDownThanBlock <= 0 && isLeftThanBlock >= 0 && isRightThanBlock <= 0)
			{
				setisAllowToRight(false);
				setisAllowToDown(false);
				setisAllowToRightDown(false);
				setisAllowToRightUp(false);
				setisAllowToLeftDown(false);
				log("zuo shang colide!!!!!!!!!!!!");
			}
			else if (isUpThanBlock >= 0 && isDownThanBlock <= 0 && isLeftThanBlock <= 0 && isRightThanBlock >= 0)
			{
				setisAllowToLeftDown(false);
				setisAllowToLeft(false);
				setisAllowToDown(false);
				setisAllowToLeftUp(false);
				setisAllowToRightDown(false);
				log("you shang colide!!!!!!!!!!!!");
			}
			else if (isUpThanBlock <= 0 && isDownThanBlock >= 0 && isLeftThanBlock <= 0 && isRightThanBlock >= 0)
			{
				setisAllowToUp(false);
				setisAllowToLeftUp(false);
				setisAllowToLeft(false);
				setisAllowToRightUp(false);
				setisAllowToLeftDown(false);
				log("you xia colide!!!!!!!!!!!!");
			}
		}
	}
}

void ControllerMoveBase::blockHeroDirection(){


}

void ControllerMoveBase::resetHeroDirection(){
	setisAllowToRight(true);
	setisAllowToLeft(true);
	setisAllowToUp(true);
	setisAllowToDown(true);
	setisAllowToLeftUp(true);
	setisAllowToLeftDown(true);
	setisAllowToRightUp(true);
	setisAllowToRightDown(true);

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
		m_isStand = false;
		if (getisAllowToUp() && m_hero->getPositionY() < 350.0f)
		{
			m_hero->setPosition(pos.x, pos.y + moveSpeed);
			if (m_isRight && !m_isUp)
			{	
				m_isUp = true;
				m_hero->playAnimaitonWalk(Direction::right);
			}
			else if (m_isLeft && !m_isUp){
				m_isUp = true;
				m_hero->playAnimaitonWalk(Direction::left);
			}
		}
		
		break;
	case JoystickEnum::D_DOWN:
		m_isStand = false;
		if (getisAllowToDown() && m_hero->getPositionY() > 45.0f)
		{
			m_hero->setPosition(pos.x, pos.y - moveSpeed);
			if (m_isRight && !m_isDown)
			{	
				m_isDown = true;
				m_hero->playAnimaitonWalk(Direction::right);
			}
			else if(m_isLeft && !m_isDown)
			{
				m_isDown = true;
				m_hero->playAnimaitonWalk(Direction::left);
			}
		}
		break;
	case JoystickEnum::D_LEFT:
		m_isStand = false;
		if (getisAllowToLeft())
		{
			m_hero->setPosition(pos.x - moveSpeed, pos.y);
			if (!m_isLeft)
			{
				m_isLeft = true;
				m_hero->playAnimaitonWalk(Direction::left);
				m_isRight = false;
			}
		}
		break;
	case JoystickEnum::D_RIGHT:	
		m_isStand = false;
		if (getisAllowToRight())
		{
			
			m_hero->setPosition(pos.x + moveSpeed, pos.y);
			if (!m_isRight)
			{
				m_isRight = true;
				m_hero->playAnimaitonWalk(Direction::right);
				m_isLeft = false;
			}
			__rollmapForward();
		}
		break;
	case JoystickEnum::D_LEFT_UP:
		m_isStand = false;		
		if (getisAllowToLeftUp() && m_hero->getPositionY() < 350.0f)
		{
			if (!m_isLeft)
			{
				m_isLeft = true;
				m_hero->playAnimaitonWalk(Direction::left);
				m_isRight = false;
			}
			m_hero->setPosition(pos.x - moveSpeed, pos.y + moveSpeed);
		}
		
		break;
	case JoystickEnum::D_RIGHT_UP:
		m_isStand = false;
		if (getisAllowToRightUp() && m_hero->getPositionY() < 350.0f)
		{
			
			m_hero->setPosition(pos.x + moveSpeed, pos.y);
			if (!m_isRight)
			{
				m_isRight = true;
				m_hero->playAnimaitonWalk(Direction::right);
				m_isLeft = false;
			}
			__rollmapForward();
		}
	
		break;
	case JoystickEnum::D_LEFT_DOWN:
		m_isStand = false;
		if (getisAllowToLeftDown() && m_hero->getPositionY() >= 45.0f)
		{
			if (!m_isLeft)
			{
				m_isLeft = true;
				m_hero->playAnimaitonWalk(Direction::left);
				m_isRight = false;
			}
			m_hero->setPosition(pos.x - moveSpeed, pos.y - moveSpeed);
		}

		break;
	case JoystickEnum::D_RIGHT_DOWN:
		m_isStand = false;
		if (getisAllowToRightDown() && m_hero->getPositionY() > 45.0f)
		{
			
			m_hero->setPosition(pos.x + moveSpeed, pos.y);
			if (!m_isRight)
			{
				m_isRight = true;
				m_hero->playAnimaitonWalk(Direction::right);
				m_isLeft = false;
			}
			__rollmapForward();
		}
		
		break;
	case JoystickEnum::DEFAULT:
		if (!m_isStand)
		{
			m_isStand = true;
			if (m_isRight)
			{
				m_hero->playAnimaitonStand(Direction::right);
			}
			else if (m_isLeft)
			{
				m_hero->playAnimaitonStand(Direction::left);
			}
			else
			{
				m_hero->playAnimaitonStand(Direction::right);
			}

			
		}
		break;
	}

}

void ControllerMoveBase::__rollmapForward(){
	//log("hero location===%f", m_hero->getPositionX());
	log("hero scene location===%f", m_map->convertToWorldSpace(m_hero->getPosition()).x);
	if (m_map->convertToWorldSpace(m_hero->getPosition()).x >= 640){
		m_map->setPosition(Vec2(m_map->getPositionX() - getiSpeed(), m_map->getPositionY()));
	}
}

void ControllerMoveBase::__rollmapBackward(){

}