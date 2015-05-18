#include "ControllerMoveBase.h"
#include "Hero.h"
#include "Monster.h"
#include "JoyStick.h"
#include "GameScene.h"
#define SPEED 1

#define LEFT 2
#define RIGHT 3





USING_NS_CC;

ControllerMoveBase::ControllerMoveBase() :
m_isMoving(false),
m_hero(nullptr),
m_map(nullptr),
m_isLeft(false),
m_isRight(true),
m_isStand(false),
m_isUp(false),
m_isDown(false),
leftOrRight(true)
{

}

ControllerMoveBase::~ControllerMoveBase(){

}

ControllerMoveBase* ControllerMoveBase::create(Hero* hero, Sprite* map, ScenarioEnum scenario, SubScenarioEnum subscenario){
	ControllerMoveBase* ctrMoveBase = new ControllerMoveBase();

	if (ctrMoveBase && ctrMoveBase->init(hero, map, scenario, subscenario)){
	}
	else{
		CC_SAFE_DELETE(ctrMoveBase);
	}
	return ctrMoveBase;

}

bool ControllerMoveBase::init(Hero* hero, Sprite* map, ScenarioEnum scenario, SubScenarioEnum subscenario){

	if (hero == nullptr || map == nullptr)
	{
		return false;
	}
	this->m_hero = hero;
	this->m_map = map;
	m_scenario = scenario;
	m_subscenario = subscenario;

	m_rightBoundary = -1 * (m_map->getContentSize().width - 1280.0f);	
	m_leftBoundary = 0.0f;

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


			if ((isUpThanBlock > 0 && isDownThanBlock > 0 )|| (isUpThanBlock < 0 && isDownThanBlock < 0))
			{
				if (isLeftThanBlock >= 0 && isRightThanBlock <= 0)
				{
					setisAllowToRight(false);
					setisAllowToRightDown(false);
					setisAllowToRightUp(false);
				}
				if (isLeftThanBlock <= 0 && isRightThanBlock >= 0)
				{
					setisAllowToLeft(false);
					setisAllowToLeftDown(false);
					setisAllowToLeftUp(false);
				}
			}

			else if ((isLeftThanBlock > 0 && isRightThanBlock > 0 )|| (isLeftThanBlock < 0 && isRightThanBlock < 0))
			{
				if (isUpThanBlock >= 0 && isDownThanBlock <= 0)
				{
					setisAllowToDown(false);
					setisAllowToLeftDown(false);
					setisAllowToRightDown(false);
				}
				if (isUpThanBlock <= 0 && isDownThanBlock >= 0)
				{
					setisAllowToUp(false);
					setisAllowToRightUp(false);
					setisAllowToLeftUp(false);
				}
			}


			else if (isUpThanBlock <= 0 && isDownThanBlock >= 0 && isLeftThanBlock >= 0 && isRightThanBlock <= 0)
			{
				setisAllowToUp(false);
				setisAllowToRightUp(false);
				setisAllowToRight(false);
				setisAllowToLeftUp(false);
				setisAllowToRightDown(false);
			}
			else if (isUpThanBlock >= 0 && isDownThanBlock <= 0 && isLeftThanBlock >= 0 && isRightThanBlock <= 0)
			{
				setisAllowToRight(false);
				setisAllowToDown(false);
				setisAllowToRightDown(false);
				setisAllowToRightUp(false);
				setisAllowToLeftDown(false);
			}
			else if (isUpThanBlock >= 0 && isDownThanBlock <= 0 && isLeftThanBlock <= 0 && isRightThanBlock >= 0)
			{
				setisAllowToLeftDown(false);
				setisAllowToLeft(false);
				setisAllowToDown(false);
				setisAllowToLeftUp(false);
				setisAllowToRightDown(false);
			}
			else if (isUpThanBlock <= 0 && isDownThanBlock >= 0 && isLeftThanBlock <= 0 && isRightThanBlock >= 0)
			{
				setisAllowToUp(false);
				setisAllowToLeftUp(false);
				setisAllowToLeft(false);
				setisAllowToRightUp(false);
				setisAllowToLeftDown(false);
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

void ControllerMoveBase::setBoundary(){
	if (m_subscenario == SubScenarioEnum::LV3)
	{
		switch (m_scenario)
		{
		case ScenarioEnum::Port:
			m_rightBoundary = -3000.0f;
			break;
		case ScenarioEnum::Market:
			m_rightBoundary = -3000.0f;
			break;
		case ScenarioEnum::Sewer:
			m_rightBoundary = -2691.0f;
			break;	
		default:
			break;
		}
	}
	else{
		m_rightBoundary = -1 * (m_map->getContentSize().width * 2 - 1280.0f);
		
	}
	m_leftBoundary = -1 * (m_map->getContentSize().width);
}

void ControllerMoveBase::simpleMove(JoystickEnum direction){

	heroDirection = direction;

	Point pos = m_hero->getPosition();
	float moveSpeed = this->m_hero->getCurSpeed();
	resetHeroDirection();
	judgeBlock();
	switch (heroDirection)
	{

	case JoystickEnum::D_UP:
		m_isStand = false;
		if (getisAllowToUp() && m_hero->getPositionY() < 350.0f)
		{
			m_hero->setPosition(pos.x, pos.y + moveSpeed);
			if (!m_isRight && !m_isUp)
			{	
				m_isUp = true;
                m_isRight = true;
                m_isDown = false;
                m_isLeft = false;
				m_hero->playAnimaitonWalk(Direction::right);
			}
			else if (!m_isLeft && !m_isUp){
				m_isUp = true;
                m_isLeft = true;
                m_isDown = false;
                m_isRight = false;
				m_hero->playAnimaitonWalk(Direction::left);
			}
		}	
		break;
	case JoystickEnum::D_DOWN:
		m_isStand = false;
		if (getisAllowToDown() && m_hero->getPositionY() > 45.0f)
		{
			m_hero->setPosition(pos.x, pos.y - moveSpeed);
			if (!m_isRight && !m_isDown)
			{	
				m_isDown = true;
                m_isRight = true;
                m_isUp = false;
                m_isLeft = false;
				m_hero->playAnimaitonWalk(Direction::right);
			}
			else if(!m_isLeft && !m_isDown)
			{
				m_isDown = true;
                m_isLeft = true;
                m_isUp = false;
                m_isRight = false;
				m_hero->playAnimaitonWalk(Direction::left);
			}
		}
		break;
	case JoystickEnum::D_LEFT:
		m_isStand = false;
		if (getisAllowToLeft() && m_map->convertToWorldSpace(m_hero->getPosition()).x >= 50)
		{
			leftOrRight = false;
            
			m_hero->setPosition(pos.x - moveSpeed, pos.y);
			if (!m_isLeft)
			{
                
				
				m_hero->playAnimaitonWalk(Direction::left);
                m_isLeft = true;
				m_isRight = false;
                m_isUp = false;
                m_isDown = false;
			}
			__rollmapBackward();
		}
		break;
	case JoystickEnum::D_RIGHT:	
		m_isStand = false;
		if (getisAllowToRight() && m_map->convertToWorldSpace(m_hero->getPosition()).x <= 1230.0f)
		{
			leftOrRight = true;
			m_hero->setPosition(pos.x + moveSpeed, pos.y);
			if (!m_isRight)
			{
				
				m_hero->playAnimaitonWalk(Direction::right);
                m_isRight = true;
				m_isLeft = false;
                m_isUp = false;
                m_isDown = false;
			}
			__rollmapForward();
		}
		break;
	case JoystickEnum::D_LEFT_UP:
		m_isStand = false;		
		if (getisAllowToLeftUp() && m_hero->getPositionY() < 350.0f && m_map->convertToWorldSpace(m_hero->getPosition()).x >= 50)
		{
			leftOrRight = false;
			m_hero->setPosition(pos.x - moveSpeed, pos.y + moveSpeed);
			if (!m_isLeft)
			{
				
				m_hero->playAnimaitonWalk(Direction::left);
                m_isLeft = true;
				m_isRight = false;
                m_isUp = false;
                m_isDown = false;
			}
			__rollmapBackward();
		}
		
		break;
	case JoystickEnum::D_RIGHT_UP:
		m_isStand = false;
		if (getisAllowToRightUp() && m_hero->getPositionY() < 350.0f && m_map->convertToWorldSpace(m_hero->getPosition()).x < 1230.0f)
		{
			leftOrRight = true;
			m_hero->setPosition(pos.x + moveSpeed, pos.y + moveSpeed);
			if (!m_isRight)
			{
				
				m_hero->playAnimaitonWalk(Direction::right);
                m_isRight = true;
				m_isLeft = false;
                m_isUp = false;
                m_isDown = false;
			}
			__rollmapForward();
		}
	
		break;
	case JoystickEnum::D_LEFT_DOWN:
		m_isStand = false;
		if (getisAllowToLeftDown() && m_hero->getPositionY() >= 45.0f && m_map->convertToWorldSpace(m_hero->getPosition()).x >= 50)
		{
			leftOrRight = false;
			m_hero->setPosition(pos.x - moveSpeed, pos.y - moveSpeed);
			if (!m_isLeft)
			{
				
				m_hero->playAnimaitonWalk(Direction::left);
                m_isLeft = true;
				m_isRight = false;
                m_isUp = false;
                m_isDown = false;
			}
			__rollmapBackward();
		}

		break;
	case JoystickEnum::D_RIGHT_DOWN:
		m_isStand = false;
		if (getisAllowToRightDown() && m_hero->getPositionY() > 45.0f && m_map->convertToWorldSpace(m_hero->getPosition()).x < 1230.0f)
		{
			leftOrRight = true;
			m_hero->setPosition(pos.x + moveSpeed, pos.y - moveSpeed);
			if (!m_isRight)
			{
				
				m_hero->playAnimaitonWalk(Direction::right);
                m_isRight = true;
				m_isLeft = false;
                m_isUp = false;
                m_isDown = false;
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
                m_isRight = false;
                m_isUp = false;
                m_isDown = false;
                m_isLeft = false;
			}
			else if (m_isLeft)
			{
                m_hero->playAnimaitonStand(Direction::left);
                m_isLeft = false;
                m_isUp = false;
                m_isDown = false;
                m_isRight = false;

            }
            else
            {
                if(leftOrRight){
                    m_hero->playAnimaitonStand(Direction::right);
                }
                else
                {
                    m_hero->playAnimaitonStand(Direction::left);
                }
            }
			
		}
		break;
	}

}

void ControllerMoveBase::__rollmapForward(){
	if (m_map->convertToWorldSpace(m_hero->getPosition()).x >= 640 && m_map->getPosition().x >= m_rightBoundary){
		m_map->setPosition(Vec2(m_map->getPositionX() - m_hero->getCurSpeed(), m_map->getPositionY()));	
	}
}

void ControllerMoveBase::__rollmapBackward(){
	if (m_map->convertToWorldSpace(m_hero->getPosition()).x <= 50 && m_map->getPosition().x <= m_leftBoundary)
	{
		m_map->setPosition(Vec2(m_map->getPositionX() + m_hero->getCurSpeed(), m_map->getPositionY()));
	}
}