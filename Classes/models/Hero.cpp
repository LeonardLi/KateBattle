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
#include "SoundsDef.h"
#include "SoundsController.h"

//default speed
#define DEFAULTSPEED 1.0f
//default attack value
#define DEFAULTATTACKVALUE 10.0f
//default hp
#define DEFAULTHP 100.0f
//default defence
#define DEFAULTDEFENCE 0.0f
//default intelligence value
#define DEFAULTINTELLIGENCEVALUE 5.0f
//default attack speed
#define DEFAULTATTACKSPEED 1.0f

float defaultHp = 100.0f;
float defaultAttackValue = 10.0f;
float defaultDefenceValue = 0.0f;
float defaultSpeed = 1.0f;
float defaultIntelligenceValue = 5.0f;
float defautlAttackSpeed = 1.5f;


USING_NS_CC;
using namespace cocostudio;
using namespace CocosDenshion;
Hero::Hero() :
m_curSpeed(1.0f),
m_moveSpeed(1.0f),

m_attackRange(100.0f),

m_curAttackValue(10.0f),
m_equipAttackValue(10.0f),

m_curHp(100.0f),
m_upperHp(100.0f),

m_equipDefenceValue(0.0f),
m_curDefenceValue(0.0f),

m_intelligenceValue(5.0f),
m_curIntelligenceValue(5.0f),

m_curAttackSpeed(1.5f),
m_equipAttackSpeed(1.5f),

m_heroExistScreen(1),
m_AttackPos(1),
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
	if (getisDead()==true)
	{
		bloodBar->setPercent(0.0f);
	}
	bloodBar->setPercent(getcurHp() / getupperHp()*100.0f);
	
	if (getStun()!=STUN && m_isDead==false&&m_canControl==true)
	m_moveController->simpleMove(m_direction);

}


void Hero::ChangeDirection(JoystickEnum direction){
	
	m_direction = direction;
}

void Hero::onDead(){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_16.c_str());
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

void Hero::changeCanControl(float time){
	m_canControl = true;
}

void Hero::herostun(float time)
{
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_15.c_str());
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
	int pos = getAttackPos();
	float damageAddition=0.0f;
	heroNotControl(1.0f);
	switch (pos)
	{
	case 1:
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_5.c_str());
		this->m_armature->getAnimation()->play("attack1", -1, 0);
		setAttackPos(2);
		break;
	case 2:
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_6.c_str());
		this->m_armature->getAnimation()->play("attack2", -1, 0);
		damageAddition = this->getcurAttackValue() / 5;
		setAttackPos(3);
		break;
	case 3:
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_7.c_str());
		this->m_armature->getAnimation()->play("attack3", -1, 0);
		damageAddition = this->getcurAttackValue() / 3;
		if (this->isScheduled(schedule_selector(Hero::recoverAttackPosture)))
		{
			this->unschedule(schedule_selector(Hero::recoverAttackPosture));
		}
		setAttackPos(1);
		break;
	default:
		break;
	}
	if (this->isScheduled(schedule_selector(Hero::recoverAttackPosture)))
	{
		this->unschedule(schedule_selector(Hero::recoverAttackPosture));
		this->scheduleOnce(schedule_selector(Hero::recoverAttackPosture), 3.0f);
	}
	else
		this->scheduleOnce(schedule_selector(Hero::recoverAttackPosture), 3.0f);

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
			float randomNum = CCRANDOM_0_1();
			float randomNum2 = CCRANDOM_0_1();
			float attackRate = randomNum2 / 2 + 0.75;
			if (randomNum>0.8)
			{
				monster->monsterGetHurt((this->getcurAttackValue()+damageAddition) * 2 * attackRate, 0.0f,true);
			}
			else
				monster->monsterGetHurt((this->getcurAttackValue() + damageAddition) * attackRate, 0.0f,false);
			return;
		}
	}	
}

void Hero::recoverAttackPosture(float dt){
	setAttackPos(1);
}

void Hero::heroNotControl(float time){
	m_canControl = false;
	this->scheduleOnce(schedule_selector(Hero::changeControlType), time);
}

void Hero::changeControlType(float dt){
	if (m_canControl == false)
		m_canControl = true;
}

void Hero::hitGroundSkill()
{
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_9.c_str());
	this->m_armature->getAnimation()->play("aoe",-1,0);
	heroNotControl(1.7f);
	Label* label = Label::create("Tear the ground!", "fonts/Marker Felt.ttf", 30);
	label->setPosition(this->getBoundingBox().size.width / 2, this->getBoundingBox().size.height + 80);
	label->setColor(Color3B::BLACK);
	this->addChild(label);
	FadeIn* action1 = FadeIn::create(1.0f);
	MoveBy* action2 = MoveBy::create(3.0f, Vec2(0, 30));
	FadeOut* action3 = FadeOut::create(1.0f);
	Sequence* seq1 = Sequence::create(action2, action3, NULL);
	Sequence* seq2 = Sequence::create(action1, seq1, NULL);
	label->runAction(seq2);
	auto callFunc = CallFunc::create([=](){
		for (auto monster : m_heroMonsterList)
		{
			if (monster->getisDead() == false && monster->getcanAttack() == true)
			{
				Vec2 distance = Vec2(this->getPositionX() - monster->getPositionX(), this->getPositionY() - monster->getPositionY());
				if (distance.length() <= 400)
				{
					monster->monsterGetHurt(10+this->getcurIntelligenceValue()*2, 1.0f,false);
				}
			}
		}
	});
	this->runAction(Sequence::create(DelayTime::create(1.5f), callFunc, NULL));
}

void Hero::addDefenceValue(){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_10.c_str());
	Label* label = Label::create("Add defence value!", "fonts/Marker Felt.ttf", 30);
	label->setPosition(this->getBoundingBox().size.width / 2, this->getBoundingBox().size.height + 80);
	label->setColor(Color3B::BLACK);
	this->addChild(label);
	FadeIn* action1 = FadeIn::create(1.0f);
	MoveBy* action2 = MoveBy::create(3.0f, Vec2(0, 30));
	FadeOut* action3 = FadeOut::create(1.0f);
	Sequence* seq1 = Sequence::create(action2, action3, NULL);
	Sequence* seq2 = Sequence::create(action1, seq1, NULL);
	label->runAction(seq2);
	this->setcurDefenceValue(getequipDefenceValue() + 50);
	this->scheduleOnce(schedule_selector(Hero::recoverDefenceValue),5.0f);
}

void Hero::recoverDefenceValue(float dt){

	this->setcurDefenceValue(getequipDefenceValue());
}

void Hero::blink(){
	heroNotControl(0.8f);
	Vec2 desPoint;
	int direction;
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_8.c_str());
	Label* label = Label::create("Blink!", "fonts/Marker Felt.ttf", 30);
	label->setPosition(this->getBoundingBox().size.width / 2, this->getBoundingBox().size.height + 80);
	label->setColor(Color3B::BLACK);
	this->addChild(label);
	FadeIn* action1 = FadeIn::create(1.0f);
	MoveBy* action2 = MoveBy::create(3.0f, Vec2(0, 30));
	FadeOut* action3 = FadeOut::create(1.0f);
	Sequence* seq1 = Sequence::create(action2, action3, NULL);
	Sequence* seq2 = Sequence::create(action1, seq1, NULL);
	label->runAction(seq2);
	this->m_armature->getAnimation()->play("blink", -1, 0);
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
	if (desPoint.x<0)
	{
		desPoint.x = 30;
	}
	auto callFunc = CallFunc::create([=](){
		this->setPosition(desPoint);
	});
	this->runAction(Sequence::create(DelayTime::create(0.5), callFunc, NULL));
}

void Hero::getHurt(float ivalue,float stunTime,float slowValue,float slowTime){
	if (this->getisDead() == false)
	{
		float iCurHp = getcurHp();
		float randomNum2 = CCRANDOM_0_1();
		float attackRate = randomNum2 / 2 + 0.75;
		float afterValue = ivalue*attackRate;

		

		if (afterValue<getcurDefenceValue())
		{
			return;
		}

		int hurtValue = afterValue;
		auto string = std::to_string(hurtValue);
		Label* label = Label::create(string, "fonts/Marker Felt.ttf", 30);
		label->setPosition(this->getBoundingBox().size.width/2,this->getBoundingBox().size.height+40);
		label->setColor(Color3B::BLACK);
		this->addChild(label);
		FadeIn* action1 = FadeIn::create(1.0f);
		MoveBy* action2 = MoveBy::create(1.0f, Vec2(0, 30));
		FadeOut* action3 = FadeOut::create(1.0f);
		Sequence* seq1 = Sequence::create(action2, action3, NULL);
		Sequence* seq2 = Sequence::create(action1, seq1, NULL);
		label->runAction(seq2);
		float iAfterHp = iCurHp - ivalue;

		
		if (iAfterHp > 0)
		{
			setcurHp(iAfterHp);
		}
		//����
		else
		{
			setcurHp(0);
			this->setisDead(true);
			onDead();
			return;
		}

		if (stunTime > 0)
		{
			this->herostun(stunTime);
		}
		if (slowValue > 0.01)
		{
			this->changeSpeed(slowValue, slowTime);
		}
	}
}

void Hero::changeSpeed(float slowValue, float slowTime){
	float speed = this->getMoveSpeed();
	if (speed==this->getMoveSpeed())
	{
		this->setCurSpeed(speed*(1 - slowValue));
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
	this->setCurSpeed(this->getMoveSpeed());
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
