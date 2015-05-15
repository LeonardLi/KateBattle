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
#include "JsonUtility.h"

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

m_curAttackValue(32.0f),
m_equipAttackValue(32.0f),

m_curHp(288.0f),
m_upperHp(288.0f),

m_equipDefenceValue(0.0f),
m_curDefenceValue(0.0f),

m_intelligenceValue(26.0f),
m_curIntelligenceValue(26.0f),

m_curAttackSpeed(12.0f),
m_equipAttackSpeed(12.0f),

m_equipDecreaseValue(0.0f),
m_curDecreaseValue(0.0f),

m_heroExistScreen(1),
m_AttackPos(1),
m_direction(JoystickEnum::DEFAULT),
m_canControl(true),
m_isDead(false),
m_moveController(nullptr),
m_armature(nullptr),
infengkuangBuff(0),
inmianyiBuff(0),
injifengBuff(0),
inzhiliBuff(0),
jifengBuff(nullptr),
fengkuangBuff(nullptr),
mianyiBuff(nullptr),
zhiliBuff(nullptr)

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
		flashHero();
		bRet = true;
	} while (0);
	this->scheduleUpdate();
	return bRet;
}

void Hero::flashHero(){
	User user = JsonUtility::getInstance()->user;
	setMoveSpeed(1.2 + user.UserMoveRate*0.01);
	setCurSpeed(1.2+ user.UserMoveRate*0.01);
	setequipAttackValue(user.UserAttack);
	setcurAttackValue(user.UserAttack);
	setupperHp(user.UserHealth);
	setcurHp(user.UserCulHealth);
	setequipDefenceValue(user.UserDefense);
	setcurDefenceValue(user.UserDefense);
	setintelligenceValue(user.UserIntelligence);
	setcurIntelligenceValue(user.UserIntelligence);
	setequipAttackSpeed(user.UserAttackRate);
	setcurAttackSpeed(user.UserAttackRate);
}

void Hero::flashHeroDefault(){
	User user = JsonUtility::getInstance()->user;

}

void Hero::_loadCSB(std::string csbfile){
	mViewNode = static_cast<Node*>(CSLoader::createNode(csbfile));
	m_armature = static_cast<Armature*>(mViewNode->getChildByTag(21));
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
	User user = JsonUtility::getInstance()->user;

	bloodBar->setPercent(user.UserCulHealth / user.UserHealth*100.0f);
	
	if (getStun()!=STUN && m_isDead==false&&m_canControl==true)
	m_moveController->simpleMove(m_direction);

}


void Hero::ChangeDirection(JoystickEnum direction){
	m_direction = direction;
}

void Hero::onDead(){
	this->stopAllActions();
	this->m_armature->getAnimation()->stop();
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
	if (getisDead()==false)
	{
		this->m_armature->getAnimation()->play("stand");
	}

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

void Hero::resetDirection(){
	this->m_moveController->m_isStand = true;
	this->m_moveController->m_isLeft = false;
	this->m_moveController->m_isRight = false;
	this->m_moveController->m_isUp = false;
	this->m_moveController->m_isDown = false;
}

void Hero::attack(){
	int pos = getAttackPos();
	float damageAddition=0.0f;
	heroNotControl(0.8f);
	if (getisDead()==true)
	{
		return;
	}
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
		damageAddition = this->getcurAttackValue() / 6;
		setAttackPos(3);
		break;
	case 3:
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_7.c_str());
		this->m_armature->getAnimation()->play("attack3", -1, 0);
		damageAddition = this->getcurAttackValue() / 4;
		if (this->isScheduled(schedule_selector(Hero::recoverAttackPosture)))
		{
			this->unschedule(schedule_selector(Hero::recoverAttackPosture));
		}
		setAttackPos(1);
		break;
	default:
		break;
	}
    
	if (isScheduled(schedule_selector(Hero::changeToStand)))
	{
		this->unschedule(schedule_selector(Hero::changeToStand));
		this->scheduleOnce(schedule_selector(Hero::changeToStand), 1.0f);
	}
	else
	{
		this->scheduleOnce(schedule_selector(Hero::changeToStand), 1.0f);
	}

	if (this->isScheduled(schedule_selector(Hero::recoverAttackPosture)))
	{
		this->unschedule(schedule_selector(Hero::recoverAttackPosture));
		this->scheduleOnce(schedule_selector(Hero::recoverAttackPosture), 3.0f);
	}
	else
		this->scheduleOnce(schedule_selector(Hero::recoverAttackPosture), 3.0f);

	resetDirection();

	Rect rect;
	if (this->m_moveController->leftOrRight == false)
	{
		rect = Rect(this->getPositionX() - this->getattackRange(), this->getPositionY()-30, this->getattackRange()-45, this->getattackRange() / 2+20);
	}
	else
	{
		rect = Rect(this->getPositionX() + this->getContentSize().width-20, this->getPositionY()-30, this->getattackRange() - 35.0f, this->getattackRange() / 2+20);
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
				monster->monsterGetHurt((this->getcurAttackValue()+damageAddition) * 1.6 * attackRate, 0.0f,true,false);
			}
			else
				monster->monsterGetHurt((this->getcurAttackValue() + damageAddition) * attackRate, 0.0f,false,false);
			return;
		}
	}	
	
	
}

void Hero::changeToStand(float dt){
	this->getMoveController()->m_isStand = false;
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
	resetDirection();
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
					monster->monsterGetHurt(this->getcurIntelligenceValue()*2, 2.5f,false,true);
				}
			}
		}
	});
	this->runAction(Sequence::create(DelayTime::create(1.5f), callFunc, NULL));
	if (isScheduled(schedule_selector(Hero::changeToStand)))
	{
		this->unschedule(schedule_selector(Hero::changeToStand));
		this->scheduleOnce(schedule_selector(Hero::changeToStand), 1.7f);
	}
	else
	{
		this->scheduleOnce(schedule_selector(Hero::changeToStand), 1.7f);
	}

}

void Hero::addDefenceValue(){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_10.c_str());
	int value = getcurIntelligenceValue() * 2 - 15;
	Label* label = Label::create("Defence + " + std::to_string(value) + " !", "fonts/Marker Felt.ttf", 30);
	label->setPosition(this->getBoundingBox().size.width / 2, this->getBoundingBox().size.height + 80);
	label->setColor(Color3B::BLACK);
	this->addChild(label);
	FadeIn* action1 = FadeIn::create(1.0f);
	MoveBy* action2 = MoveBy::create(3.0f, Vec2(0, 30));
	FadeOut* action3 = FadeOut::create(1.0f);
	Sequence* seq1 = Sequence::create(action2, action3, NULL);
	Sequence* seq2 = Sequence::create(action1, seq1, NULL);
	label->runAction(seq2);
	this->setcurDefenceValue(getequipDefenceValue() + value);
	this->scheduleOnce(schedule_selector(Hero::recoverDefenceValue),10.0f);
}

void Hero::recoverDefenceValue(float dt){

	this->setcurDefenceValue(getequipDefenceValue());
}

void Hero::blink(){
	heroNotControl(1.5f);
	Vec2 desPoint;
	int direction;
	resetDirection();
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
		desPoint = Vec2(this->getPositionX() - (175 + 3*getcurIntelligenceValue()), this->getPositionY());		
	}
	else
	{
		direction = 1;
		desPoint = Vec2(this->getPositionX() + (175 + 3 * getcurIntelligenceValue()), this->getPositionY());
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
	//need amend!!!!!!!============================================

	auto callFunc = CallFunc::create([=](){
		this->setPosition(desPoint);
	});
	this->runAction(Sequence::create(DelayTime::create(0.5), callFunc, NULL));
	if (isScheduled(schedule_selector(Hero::changeToStand)))
	{
		this->unschedule(schedule_selector(Hero::changeToStand));
		this->scheduleOnce(schedule_selector(Hero::changeToStand), 1.5f);
	}
	else
	{
		this->scheduleOnce(schedule_selector(Hero::changeToStand), 1.5f);
	}

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

		int hurtValue = (afterValue - getcurDefenceValue())*(1 - getcurDecreaseValue());

		if (stunTime > 0)
		{
			this->herostun(stunTime);
			if (isScheduled(schedule_selector(Hero::changeToStand)))
			{
				this->unschedule(schedule_selector(Hero::changeToStand));
				this->scheduleOnce(schedule_selector(Hero::changeToStand), stunTime);
			}
			else
			{
				this->scheduleOnce(schedule_selector(Hero::changeToStand), stunTime);
			}
			resetDirection();
		}

		if (slowValue > 0.01)
		{
			int time = slowTime;
			Label* label = Label::create("Slow !!!" , "fonts/Marker Felt.ttf", 30);
			label->setPosition(Vec2(this->getBoundingBox().size.width / 2, this->getBoundingBox().size.height + 60));
			this->addChild(label, 4);
			FadeIn* action1 = FadeIn::create(0.5f);
			MoveBy* action2 = MoveBy::create(1.0f, Vec2(0, 20));
			FadeOut* action3 = FadeOut::create(0.5f);
			Sequence* seq1 = Sequence::create(action2, action3, NULL);
			Sequence* seq2 = Sequence::create(action1, seq1, NULL);
			label->runAction(seq2);
			this->herostun(stunTime);
			this->changeSpeed(slowValue, slowTime);
		}

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
		float iAfterHp = iCurHp - hurtValue;

		User& User = JsonUtility::getInstance()->user;
		if (iAfterHp > 0)
		{
			setcurHp(iAfterHp);
			User.UserCulHealth = iAfterHp;
		}
		else
		{
			setcurHp(0);
			User.UserCulHealth =0;
			this->setisDead(true);
			onDead();
			return;
		}

		
	
	}
}

void Hero::getMoney(bool BossOrNot,int level){
	log("==============money!!==============");


}


void Hero::useFastMedicines(){
	if (injifengBuff==1)
	{
		jifengBuff->setPercentage(100.0f);
	}
	else
	{
		jifengBuff = ProgressTimer::create(Sprite::create("jifeng.png"));
		jifengBuff->setPosition(450, 565);
		this->getParent()->getParent()->addChild(jifengBuff, 3, 1);
		jifengBuff->setType(ProgressTimer::Type::RADIAL);
	}
	injifengBuff = 1;
	auto to2 = Sequence::createWithTwoActions(ProgressTo::create(0, 100), ProgressTo::create(15.0f, 0));
	jifengBuff->runAction(to2);

	if (isScheduled(schedule_selector(Hero::promoteSpeed))==false)
	this->schedule(schedule_selector(Hero::promoteSpeed));
	if (isScheduled(schedule_selector(Hero::recoverSpeed)))
	{
		this->unschedule(schedule_selector(Hero::recoverSpeed));
		this->scheduleOnce(schedule_selector(Hero::recoverSpeed), 15.0f);
	}
	else
	{
		this->scheduleOnce(schedule_selector(Hero::recoverSpeed), 15.0f);
	}
}

void Hero::promoteSpeed(float dt){
	setCurSpeed(3.0f);
}

void Hero::recoverSpeed(float dt){
	this->unschedule(schedule_selector(Hero::promoteSpeed));
	User& user = JsonUtility::getInstance()->user;
	this->setCurSpeed(1.2+0.01*user.UserMoveRate);
}

void Hero::useCrazyMedicines(){
	if (infengkuangBuff==1)
	{
		fengkuangBuff->setPercentage(100.0f);
	}
	else
	{
		fengkuangBuff = ProgressTimer::create(Sprite::create("fengkuang.png"));
		fengkuangBuff->setPosition(550, 565);
		this->getParent()->getParent()->addChild(fengkuangBuff);
		fengkuangBuff->setType(ProgressTimer::Type::RADIAL);
	}
	infengkuangBuff = 1;
	auto to2 = Sequence::createWithTwoActions(ProgressTo::create(0, 100), ProgressTo::create(15.0f, 0));
	fengkuangBuff->runAction(to2);
	
	if (isScheduled(schedule_selector(Hero::promoteAttackSpeed)) == false)
		this->schedule(schedule_selector(Hero::promoteAttackSpeed));
	if (isScheduled(schedule_selector(Hero::promoteAttackSpeed)))
	{
		this->unschedule(schedule_selector(Hero::recoverAttackSpeed));
		this->scheduleOnce(schedule_selector(Hero::recoverAttackSpeed), 15.0f);
	}
	else
	{
		this->scheduleOnce(schedule_selector(Hero::recoverAttackSpeed), 15.0f);
	}
	if (isScheduled(schedule_selector(Hero::promoteAttackValue)) == false)
		this->schedule(schedule_selector(Hero::promoteAttackValue));
	if (isScheduled(schedule_selector(Hero::promoteAttackValue)))
	{
		this->unschedule(schedule_selector(Hero::recoverAttackValue));
		this->scheduleOnce(schedule_selector(Hero::recoverAttackValue), 15.0f);
	}
	else
	{
		this->scheduleOnce(schedule_selector(Hero::recoverAttackValue), 15.0f);
	}
}

void Hero::promoteAttackSpeed(float percent){
	User& user = JsonUtility::getInstance()->user;
	setcurAttackSpeed(user.UserAttackRate*1.2);
}

void Hero::recoverAttackSpeed(float dt){
	this->unschedule(schedule_selector(Hero::promoteAttackSpeed));
	User& user = JsonUtility::getInstance()->user;
	this->setcurAttackSpeed(user.UserAttackRate);
}

void Hero::promoteAttackValue(float percent){
	User& user = JsonUtility::getInstance()->user;
	setcurAttackSpeed(user.UserAttack*1.2);
}

void Hero::recoverAttackValue(float dt){
	this->unschedule(schedule_selector(Hero::promoteAttackValue));
	User& user = JsonUtility::getInstance()->user;
	this->setcurAttackValue(user.UserAttack);
}

void Hero::useIntelligenceMedicines(){
	if (inzhiliBuff==1)
	{
		zhiliBuff->setPercentage(100.0f);
	}
	else
	{
		zhiliBuff = ProgressTimer::create(Sprite::create("zhili.png"));
		zhiliBuff->setPosition(650, 565);
		this->getParent()->getParent()->addChild(zhiliBuff, 3, 1);
		zhiliBuff->setType(ProgressTimer::Type::RADIAL);
	}
	inzhiliBuff = 1;
	auto to2 = Sequence::createWithTwoActions(ProgressTo::create(0, 100), ProgressTo::create(30.0f, 0));
	zhiliBuff->runAction(to2);


	if (isScheduled(schedule_selector(Hero::promoteIntelligence)) == false)
		this->schedule(schedule_selector(Hero::promoteIntelligence));

	if (isScheduled(schedule_selector(Hero::recoverIntelligence)))
	{
		this->unschedule(schedule_selector(Hero::recoverIntelligence));
		this->scheduleOnce(schedule_selector(Hero::recoverIntelligence), 30.0f);
	}
	else
	{
		this->scheduleOnce(schedule_selector(Hero::recoverIntelligence), 30.0f);
	}
}

void Hero::promoteIntelligence(float percent){
	User& user = JsonUtility::getInstance()->user;
	setcurIntelligenceValue(user.UserIntelligence*1.2);
	

}

void Hero::recoverIntelligence(float dt){
	this->unschedule(schedule_selector(Hero::promoteIntelligence));
	User& user = JsonUtility::getInstance()->user;
	setcurIntelligenceValue(user.UserIntelligence);
}


void Hero::useUnmatchedMedicines(){
	if (inmianyiBuff==1)
	{
		mianyiBuff->setPercentage(100.0f);
	}
	else
	{
		mianyiBuff = ProgressTimer::create(Sprite::create("mianyi.png"));
		mianyiBuff->setPosition(350, 565);
		this->getParent()->getParent()->addChild(mianyiBuff);
		mianyiBuff->setType(ProgressTimer::Type::RADIAL);
	}
	inmianyiBuff = 1;
	auto to2 = Sequence::createWithTwoActions(ProgressTo::create(0, 100), ProgressTo::create(15.0f, 0));	
	mianyiBuff->runAction(to2);
	promoteDefence(0.7f);
}

void Hero::recoverHealth(float value){
	float blood = getcurHp();
	float upperBlood = getupperHp();
	float usedBlood = blood + value;
	User& user = JsonUtility::getInstance()->user;
	if (usedBlood>upperBlood)
	{
		setcurHp(upperBlood);
		user.UserCulHealth = upperBlood;
	}
	else
	{
		setcurHp(usedBlood);
		user.UserCulHealth = usedBlood;
	}
}

void Hero::changeSpeed(float slowValue, float slowTime){
	float speed = this->getCurSpeed();
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

void Hero::promoteDefence(float percent){
	setcurDecreaseValue(percent);
	if (this->isScheduled(schedule_selector(Hero::recoverDefence)))
	{
		this->unschedule(schedule_selector(Hero::recoverDefence));
		this->scheduleOnce(schedule_selector(Hero::recoverDefence), 15.0f);
	}
	else
		this->scheduleOnce(schedule_selector(Hero::recoverDefence), 15.0f);
}

void Hero::recoverDefence(float dt){
	setcurDecreaseValue(getequipDecreaseValue());
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
	this->getMoveController()->m_isStand = false;
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
