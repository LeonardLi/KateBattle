//
//  Monster.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "Monster.h"
#include "MonsterFSM.h"
#include "BulletBase.h"
#include "BulletNormal.h"
#include "Hero.h"
#include "cocos2d.h"
#include "I_State.h"
#include "StateAttack.h"
#include "StateUseSkill.h"
#define SKILLRUSHSPEED 200
#define SPEEDRATE 0.5
USING_NS_CC;


Monster* Monster::create(Sprite* sprite, MonsterType type){
	Monster* monster = new Monster();
	if (monster&&monster->init(sprite,type))
	{
		monster->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monster);
	}
	return monster;
}

bool Monster::init(Sprite* sprite, MonsterType type){
	bool bRet = false;
	do
	{
		
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);
		m_FSM = MonsterFSM::createWithMonster(this);
	

		setviewRange(1500.0);
		setcanAttack(true);
		setattackTime(2.0f);
	
		skillOrAttack = false;
		
		switch (type)
		{
		case  MonsterType::normalType:
			m_monsterType = MonsterType::normalType;
			setattackRange(100.0);
			break;
		case MonsterType::shootType:
			m_monsterType = MonsterType::shootType;
			setattackRange(400.0);
			break;
		case MonsterType::monsterBossNum1:
			m_monsterType = MonsterType::monsterBossNum1;
			setattackRange(200.0);
			break;
		case MonsterType::num1ShootType:
			m_monsterType = MonsterType::num1ShootType;
			setattackRange(1500.0);
			break;
		case  MonsterType::block:
			m_monsterType = MonsterType::block;
			setcanAttack(false);
			break;
		case MonsterType::monsterBossNum2Assister:
			m_monsterType = MonsterType::monsterBossNum2Assister;
			setcanAttack(false);
			skillOrAttack = true;
			break;
		default:
			break;
		}
		bRet = true;
	} while (0);
	
	return bRet;
}

MonsterFSM* Monster::getFSM(){
	return this->m_FSM;
}

void Monster::attackSequence(){
	switch (m_monsterType)
	{
	case MonsterType::normalType:
	case MonsterType::monsterBossNum1:
		break;
	case MonsterType::shootType:
		__initBullet(1);
		break;

	case MonsterType::num1ShootType:
		__initBullet(2);

		break;
	case MonsterType::monsterBossNum3:
		this->scheduleOnce(schedule_selector(MonsterBossNum3::showTheCar), 5.0f);
		break;
	case MonsterType::monsterBossNum2Assister:
		log("assister attack");
		break;
	default:
		break;
	}
	log("monster attackSequence_______");
	this->__readyForAttack(1.0f);
}

void Monster::__initBullet(int bulletType){
	BulletBase* bullet = NULL;

	for (int i = 0; i < 10; i++)
	{
		switch (bulletType)
		{
		case 1:
			bullet = BulletNormal::create(Sprite::create("CloseNormal.png"));
			bullet->setBulletValue(10, 1.0f, 0.0f, 0.0f);
			break;
		case 2:
			bullet = BulletNormal::create(Sprite::create("CloseNormal.png"));
			bullet->setBulletValue(10, 0.0f, 0.5f, 5.0f);
			break;
		default:
			break;
		}		
		bullet->setUsed(false);
		m_bulletList.pushBack(bullet);
		this->getParent()->addChild(bullet);
	}
	this->schedule(schedule_selector(Monster::__bulletLogicCheck));
}

void Monster::__bulletLogicCheck(float dt){
	for (auto bullet : m_bulletList)
	{
		if (bullet->isUsed())
		{
			auto aim = bullet->getTarget();
			if (aim != NULL)
			{
				if (bullet->getBoundingBox().intersectsRect(targetHero->getBoundingBox()))
				{
					log("hero get hurt~~~~~~~");
					
						targetHero->getHurt(bullet->bulletDamage,bullet->bulletStunTime,bullet->bulletSlowDown,bullet->bulletSlowDownTime);
					
					bullet->stopAllActions();
					bullet->m_isArrive = true;
				}
				if (bullet->isArrive())
				{
					log("bullet Arrive!---------- - ");
					bullet->setUsed(false);
				}
			}
		}
	}
}

void Monster::__readyForAttack(float dt){
	if (this->getFSM()->getState()==MonsterFSM::toAttack||this->getFSM()->getState()==MonsterFSM::BossToAttack)
	{
		log("attack state!!~~");
		this->schedule(schedule_selector(Monster::__intoAttackSequence));
	}

	else
	{
		skillOrAttack = true;
	}
}

void Monster::__intoAttackSequence(float dt){
	if (skillOrAttack == false)
	{
		this->unschedule(schedule_selector(Monster::__intoAttackSequence));
		this->schedule(schedule_selector(Monster::__isInViewRange));
	}
}

void Monster::__isInViewRange(float dt){
	Vec2 distance = Vec2(heroLocation.x - this->getPositionX(), heroLocation.y - this->getPositionY());
	if (distance.length() <= this->getviewRange())
	{
		log("hero  InView!!!!!!!!!!");
		__attack();
		this->unschedule(schedule_selector(Monster::__isInViewRange));
	}
}

void Monster::__attack(){
	float randomNum = CCRANDOM_0_1();
	float moveAndAttack = 0.25;
	double standRate = 0.1;
	
	switch (m_monsterType)
	{
	case MonsterType::num1ShootType:
		//never random move
		moveAndAttack = 0.5;
		standRate = 0.5;
		break;
	default:
		break;
	}
		
	if (randomNum > moveAndAttack)
	{
		log("move to hero!!!!!!");
		this->schedule(schedule_selector(Monster::__monsterMoveToHero));
	}
	else if (randomNum >= standRate&&randomNum <= moveAndAttack)
	{
		log("random move!!!!");
		__monsterRandomMove();
	}
	else if (randomNum>0 && randomNum<standRate)
	{
		log("stand for 2s~~~~");
		this->scheduleOnce(schedule_selector(Monster::__readyForAttack), 2.0f);
	}
}

void Monster::__monsterMoveToHero(float dt){
	Vec2 distance = Vec2(heroLocation.x - this->getPositionX(), heroLocation.y - this->getPositionY());
	if (distance.length() > this->getattackRange())
	{
		__moveCloseToHero(distance);
	}
	else
	{
		log("hero in range");
		this->unschedule(schedule_selector(Monster::__monsterMoveToHero));
		this->__attackafterMove();
	}
	if (CCRANDOM_0_1() < 0.001)
	{
		//stop
		this->unschedule(schedule_selector(Monster::__monsterMoveToHero));
		this->scheduleOnce(schedule_selector(Monster::__readyForAttack), 2.0f);
	}
}

void Monster::__monsterRandomMove(){
	Vec2 move = Vec2(0, 0);
	float randomNumX = (CCRANDOM_0_1()-0.5)*80;
	float randomNumY = (CCRANDOM_0_1()-0.5)*100;

	if (this->getPositionY()<75&&randomNumY<0)
	{
		randomNumY*=(-1);
	}
	if (this->getPositionY()>800&&randomNumY>0)
	{
		randomNumY *= (-1);
	}

	move = Vec2(randomNumX, randomNumY);
	
	this->runAction(MoveBy::create(1.0f, move));
	this->scheduleOnce(schedule_selector(Monster::__readyForAttack), 2.0f);
}

void Monster::__attackafterMove(){
	float randomNum = CCRANDOM_0_1();
	if (randomNum > 0.25)
	{
		log("monster attack!!! after move ");
		switch (m_monsterType)
		{
		case MonsterType::monsterBossNum1:
		case MonsterType::normalType:
		case MonsterType::monsterBossNum2:
			//this->schedule();
			__attackWithHand();
			break;
		case MonsterType::shootType:
		case MonsterType::num1ShootType:
			__attackWithBullet();
			break;
		default:
			break;
		}
	}
	else
	{
		log("stand---------------");
	}
	this->scheduleOnce(schedule_selector(Monster::__finishAttack), m_attackTime);
}

void Monster::__attackWithHand(){
	float num = CCRANDOM_0_1();
	if (num < 0.8)
	{
		this->__postBossSkillMessage(1.0f);
	}
	log("attack with hand!");
}

void Monster::__attackWithBullet(){
	BulletBase* bullet = this->__getAnyUnUsedBullet();
	if (bullet != NULL)
	{
		bullet->setPosition(this->getPosition());
		bullet->onLockAim(targetHero);
	}

}

BulletBase* Monster::__getAnyUnUsedBullet(){
	for (auto bullet : m_bulletList)
	{
		if (bullet->isUsed() == false)
		{
			bullet->setUsed(true);
			return bullet;
		}
	}
	return NULL;
}

void Monster::__finishAttack(float dt){
	this->__readyForAttack(1.0f);
	log("finish attack~~~~");
}

void Monster::useSkillSequence(){
	__readyForUseSkill(0.0f);
}

void Monster::__readyForUseSkill(float dt){
	if (this->getFSM()->getState() == MonsterFSM::toUseSkill)
	{
		this->m_Stun = NOTSTUN;
		this->schedule(schedule_selector(Monster::__intoSkillSequence));
		log("ready to skill!!~~");
	}

	else if (this->getFSM()->getState() == MonsterFSM::BosstoUseSkill)
	{
		this->m_Stun = NOTSTUN;
		this->schedule(schedule_selector(Monster::__intoSkillSequence));
		log("ready to skill!!~~");
	}

	else
	{
		skillOrAttack = false;
	}
}

void Monster::__intoSkillSequence(float dt){
	if (skillOrAttack == true)
	{
		this->unschedule(schedule_selector(Monster::__intoSkillSequence));
		this->__skill();
	}

}

void Monster::__skill(){
	switch (m_monsterType)
	{
	case MonsterType::monsterBossNum1:
		log("Boss1 Skill~~~~~~~~");
		this->scheduleOnce(schedule_selector(MonsterBossNum1::intoBoss1SkillSequence), 0.0f);
		break;
	case MonsterType::monsterBossNum3:
		log("Number3 BOSS!-------- skill!!");
		this->scheduleOnce(schedule_selector(MonsterBossNum3::intoBoss3SkillSequence),0.0f);
		break;
	case MonsterType::monsterBossNum2:
		log("boss num 2 skill-++++++++++++++++++");
		this->scheduleOnce(schedule_selector(MonsterBossNum2::intoBoss2SkillSequence), 0.0f);
		break;
	case MonsterType::monsterBossNum2Assister:
		//this->schedule(schedule_selector(Monster::skillShot),2.0f);
		log("Boss 2 assister skill------------------");
		break;
	default:
		break;
	}
}

void Monster::__moveCloseToHero(Vec2 distance){
	Vec2 speed = distance / distance.length();
	speed.x *= SPEEDRATE;
	speed.y *= SPEEDRATE;
	this->setPosition(this->getPositionX() + speed.x, this->getPositionY() + speed.y);
}

void Monster::skillFinish(float dt){
	log("finishskill!");
	skillOrAttack = false;
	__postBossAttackMessage(1.0f);
	//readyForUseSkill(1.0f);
}

void Monster::isCollide(float dt){
	if (this->getBoundingBox().intersectsRect(m_boxes->getBoundingBox()))
	{	
		this->unschedule(schedule_selector(Monster::isCollide));
		this->m_Stun = STUN;
		this->targetHero->m_blockArea.eraseObject(m_boxes);
		this->getParent()->removeChild(m_boxes);
	}
}

void Monster::__postBossAttackMessage(float dt){
	this->getFSM()->OnRecvBossWantToAttack(this);
}

void Monster::__postBossSkillMessage(float dt){
	this->getFSM()->OnRecvBossWantToUseSkill(this);
}


void Monster::onDead(){
	CCASSERT(false," ");
	
}

void Monster::onHurt(){
	CCASSERT(false, " ");
}

void Monster::update(float dt){
}

void Monster::monsterGetHurt(int iValue, int time){

}

void Monster::skillShot(float dt){
	static int times;
	times++;
	auto fireBall = Sprite::create("CloseSelected.png");
	fireBall->setPosition(this->getPositionX(), this->getPositionY());
	this->getParent()->addChild(fireBall);
	Vec2 temporaryLocation = Vec2(this->targetHero->getPositionX(), this->targetHero->getPositionY());
	
	auto mark = Sprite::create("CloseSelected.png");
	mark->setPosition(this->targetHero->getPositionX(), this->targetHero->getPositionY());
	this->getParent()->addChild(mark);

	auto callfunc = CallFunc::create([=](){
		this->getParent()->removeChild(fireBall);
		this->getParent()->removeChild(mark);
		this->showFire(temporaryLocation);
	});
	ccBezierConfig bezierCon;
	bezierCon.controlPoint_1 = Vec2(this->getPositionX(), this->getPositionY());
	bezierCon.controlPoint_2 = Vec2((this->getPositionX() + this->targetHero->getPositionX()) / 2, (this->getPositionX() + this->targetHero->getPositionX())/2+200);
	bezierCon.endPosition = Vec2(this->targetHero->getPositionX(), this->targetHero->getPositionY());
	//throw time
	BezierTo* bezierAction = BezierTo::create(4.0f, bezierCon);

	fireBall->runAction(Sequence::create(bezierAction, callfunc, NULL));	
	
	if (times>3)
	{
		times = 0;
		this->unschedule(schedule_selector(Monster::skillShot));
	}
}

void Monster::showFire(Vec2 location){
	auto fire = Monster::create(Sprite::create("wolf.png"), MonsterType::block);
	fire->setPosition(location);
	this->getParent()->addChild(fire);
	dangerousAreaList.pushBack(fire);
	auto callfunc = CallFunc::create([=](){
		this->getParent()->removeChild(fire);
		dangerousAreaList.eraseObject(fire);
	});
	//disappear time 
	fire->runAction(Sequence::create(DelayTime::create(10.0f), callfunc,NULL));
}

void Monster::skillShotQuickly(float dt){

}

void Monster::boss2AssistStartSkill(){
	// interval time
	this->schedule(schedule_selector(Monster::skillShot), 8.0f);
}


//Boss number 1

MonsterBossNum1* MonsterBossNum1::create(Sprite* sprite, Vector<Monster*> monsterList){
	MonsterBossNum1* number1Boss = new MonsterBossNum1();
	if (number1Boss&&number1Boss->init(sprite, monsterList))
	{
		number1Boss->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(number1Boss);
	}
	return number1Boss;
}

bool MonsterBossNum1::init(Sprite* sprite, Vector<Monster*> monsterList){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);
		m_FSM = MonsterFSM::createWithMonster(this);

		shootMonsterList = monsterList;
		//set attribute
		setviewRange(700.0);

		setattackTime(2.0f);
		//attackrange+100 = move range
		skillOrAttack = false;	
		m_monsterType = MonsterType::monsterBossNum1;
		setattackRange(200.0);
		bRet = true;
	} while (0);
	return bRet;
}

void MonsterBossNum1::__skillRushBox(float dt){
	this->schedule(schedule_selector(MonsterBossNum1::__skillRush), 0.0, kRepeatForever, 5.0f);
	auto box = Monster::create(Sprite::create("wolf.png"), MonsterType::block);
	Vec2 boxPoint = Vec2(0, 0);
	
	float locationX = this->getPositionX();
	float locationY = this->getPositionY();
	if (locationX<=400&&locationY<=300)
	{
		boxPoint = Vec2(600, 400);
	}

	else if (locationX > 400 && locationY <= 300)
	{
		boxPoint = Vec2(200, 400);
	}
	else if (locationX > 400 && locationY > 300)
	{
		boxPoint = Vec2(200, 200);
	}
	else
		boxPoint = Vec2(600, 200);

	box->setPosition(boxPoint);
	this->getParent()->addChild(box);
	m_boxes = box;
	
	targetHero->m_blockArea.pushBack(box);

	static int monsterExist = 0;
	if (monsterExist <= 3)
	{
		auto monster = shootMonsterList.at(monsterExist);
		this->getParent()->addChild(monster);
		monster->getFSM()->OnRecvWantToAttack(monster);
		monsterExist ++;
	}

	this->schedule(schedule_selector(Monster::isCollide));
}

void MonsterBossNum1::__skillRush(float dt){
	if (this->m_Stun == 0)
	{
		this->unschedule(schedule_selector(MonsterBossNum1::__skillRush));
		this->outBoss1SkillSequence(1.0f);
	}
	else
	{
		Vec2 distance = Vec2(heroLocation.x - this->getPositionX(), heroLocation.y - this->getPositionY());
		Vec2 speed = distance / distance.length();
		speed.x *= 1.0;
		speed.y *= 1.0;
		this->setPosition(this->getPositionX() + speed.x, this->getPositionY() + speed.y);
	}
}

void MonsterBossNum1::intoBoss1SkillSequence(float dt){
	this->__skillRushBox(1.0f);
}

void MonsterBossNum1::outBoss1SkillSequence(float dt){
	this->scheduleOnce(schedule_selector(Monster::skillFinish), 5.0f);
}

//BOSS number 2
MonsterBossNum2* MonsterBossNum2::create(Sprite* sprite, Monster* monster){
	MonsterBossNum2* number2Boss = new MonsterBossNum2();
	if (number2Boss&&number2Boss->init(sprite, monster))
	{
		number2Boss->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(number2Boss);
	}
	return number2Boss;

}

bool MonsterBossNum2::init(Sprite* sprite, Monster* monster){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);
		m_FSM = MonsterFSM::createWithMonster(this);
		//set attribute
		setviewRange(700.0);
		setattackTime(2.0f);
		setcanAttack(true);
		//attackrange+100 = move range
		skillOrAttack = true;
		m_monsterType = MonsterType::monsterBossNum2;
		setattackRange(200.0);
		monsterAssist = monster;
		bRet = true;
	} while (0);
	return bRet;
}

void MonsterBossNum2::intoBoss2SkillSequence(float dt){
	this->schedule(schedule_selector(MonsterBossNum2::__dangerousAreaJudge));
	
	this->__bossJump();

	//this->monsterAssist->boss2AssistStartSkill();
}

void MonsterBossNum2::__dangerousAreaJudge(float dt){
	for (auto monster:this->monsterAssist->dangerousAreaList)
	{
		if (monster->getBoundingBox().intersectsRect(this->targetHero->getBoundingBox()))
		{
			this->targetHero->getHurt(1.0f, 0.0f, 0.0f, 0.0f);
			log("================on the fire===========");
		}
	}

}

void MonsterBossNum2::__bossJump(){
	ccBezierConfig bezierCon;
	bezierCon.controlPoint_1 = Vec2(this->getPositionX(), this->getPositionY());
	bezierCon.controlPoint_2 = Vec2((this->getPositionX() + this->targetHero->getPositionX()) / 2, (this->getPositionX() + this->targetHero->getPositionX()) / 2 + 100);
	bezierCon.endPosition = Vec2(this->targetHero->getPositionX(), this->targetHero->getPositionY());
	//throw time
	BezierTo* bezierAction = BezierTo::create(3.0f, bezierCon);
	auto callfunc = CallFunc::create([=](){
		this->__bossRotate();
	});

	this->runAction(Sequence::create(DelayTime::create(3.0f),bezierAction,DelayTime::create(3.0f),callfunc,NULL));

}

void MonsterBossNum2::__bossRotate(){
	log("===========boss rotate========");
	this->schedule(schedule_selector(MonsterBossNum2::__rotateAreaJudge));
	//load the rotate animation
	this->scheduleOnce(schedule_selector(MonsterBossNum2::__bossRotateStop), 5.0f);

}

void MonsterBossNum2::__rotateAreaJudge(float dt){
	if (this->getBoundingBox().intersectsRect(this->targetHero->getBoundingBox()))
	{
		this->targetHero->getHurt(10.0f, 0.0f, 0.2f, 1.0f);
		log("=============== hurt and slow ==============");
	}
}

void MonsterBossNum2::__bossRotateStop(float dt){
	this->unschedule(schedule_selector(MonsterBossNum2::__rotateAreaJudge));
	//load the stun animation
	this->scheduleOnce(schedule_selector(MonsterBossNum2::__bossRushToBox), 5.0f);
	this->runAction(Sequence::create(DelayTime::create(2.0f),MoveTo::create(2.0f, Vec2(200, 300)),NULL));
}

void MonsterBossNum2::__bossRushToBox(float dt){
	float y = this->targetHero->getPositionY() - this->getPositionY();
	float x = this->targetHero->getPositionX() - this->getPositionX();
	this->schedule(schedule_selector(MonsterBossNum2::__bossRushJudge));
	if (x>0)
	{
		float angle = atanf(abs(y) / x);
		float degrees = CC_RADIANS_TO_DEGREES(angle);
		if (degrees<30)
		{
			this->runAction(MoveBy::create(2.0f,Vec2(1000, 0)));
			this->monsterAssist->monsterGetHurt(50, 0.0);
		}

		else if (y>0)
		{
			this->runAction(MoveTo::create(2.0f, Vec2(300 / tanf(y / x), 600)));
		}

		else
			this->runAction(MoveTo::create(2.0f, Vec2(-300 / tanf(y / x), 0)));
	}

	else
	{
		this->runAction(MoveTo::create(2.0f, this->targetHero->getPosition()));
	}

	this->scheduleOnce(schedule_selector(MonsterBossNum2::outBoss2SkillSequence),5.0f);
}

void MonsterBossNum2::__bossRushJudge(float dt){
	if (this->getBoundingBox().intersectsRect(this->targetHero->getBoundingBox()))
	{
		log("=========boss rush hurt ===============");
		this->targetHero->getHurt(10.0f, 2.0f, 0.0, 0.0);
		this->unschedule(schedule_selector(MonsterBossNum2::__bossRushJudge));
	}
}

void MonsterBossNum2::outBoss2SkillSequence(float dt){
	this->unschedule(schedule_selector(MonsterBossNum2::__dangerousAreaJudge));
	this->scheduleOnce(schedule_selector(Monster::skillFinish), 5.0f);
}


//Boss number 3

MonsterBossNum3* MonsterBossNum3::create(Sprite* sprite, Vector<Monster*> monsterList){
	MonsterBossNum3* number3Boss = new MonsterBossNum3();
	if (number3Boss&&number3Boss->init(sprite, monsterList))
	{
		number3Boss->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(number3Boss);
	}
	return number3Boss;
}

bool MonsterBossNum3::init(Sprite* sprite, Vector<Monster*> monsterList){
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);
		m_FSM = MonsterFSM::createWithMonster(this);

		carMonsterList = monsterList;
		//set attribute
		setviewRange(700.0);

		setattackTime(2.0f);

		
		//attackrange+100 = move range
		skillOrAttack = true;
		m_monsterType = MonsterType::monsterBossNum3;
		setattackRange(200.0);
		bRet = true;
	} while (0);
	return bRet;
}

void MonsterBossNum3::intoBoss3SkillSequence(float dt){
	this->__bossRunOutOfGround(1.0f);
}

void MonsterBossNum3::outBoss3SkillSequence(float dt){
	this->scheduleOnce(schedule_selector(Monster::skillFinish), 5.0f);
}

void MonsterBossNum3::showTheCar(float dt){
	
	carMonsterList.at(0)->setPosition(1300, 75);
	carMonsterList.at(1)->setPosition(1300, 225);
	carMonsterList.at(2)->setPosition(1300, 375);
	
	for (auto monster : carMonsterList)
	{
		this->getParent()->addChild(monster);
	}

	this->scheduleOnce(schedule_selector(MonsterBossNum3::__runTheCar), 2.0f);
}

void MonsterBossNum3::__runTheCar(float dt){
	
	//random car move
	static int times = 0;
	float runTime1 = 0.0f;
	float runTime2 = 0.0f;
	float runTime3 = 0.0f;

	switch (times)
	{
	case  0:
		//312
		runTime1 = 2.0f;
		runTime2 = 4.0f;
		runTime3 = 6.0f;
		break;
	case 1:
		//231
		runTime1 = 4.5f;
		runTime2 = 1.5f;
		runTime3 = 3.0f;
		break;
	case 2:
		//321
		runTime1 = 3.0f;
		runTime2 = 2.0f;
		runTime3 = 1.0f;
		break;
	default:
		//123
		runTime1 = 2.0f;
		runTime2 = 4.0f;
		runTime3 = 6.0f;
		break;
	}
	
	times++;
	this->schedule(schedule_selector(MonsterBossNum3::__isCarCollide));
	this->scheduleOnce(schedule_selector(MonsterBossNum3::__runNumber1Car), runTime1);
	this->scheduleOnce(schedule_selector(MonsterBossNum3::__runNumber2Car), runTime2);
	this->scheduleOnce(schedule_selector(MonsterBossNum3::__runNumber3Car), runTime3);

	this->scheduleOnce(schedule_selector(MonsterBossNum3::__removeTheCar), 15.0f);	
}

void MonsterBossNum3::__runNumber1Car(float dt){
	this->carMonsterList.at(0)->runAction(EaseIn::create(MoveBy::create(5.0f, Vec2(-1400, 0)),3.0f));
}

void MonsterBossNum3::__runNumber2Car(float dt){
	this->carMonsterList.at(1)->runAction(EaseIn::create(MoveBy::create(5.0f, Vec2(-1400, 0)), 3.0f));
}

void MonsterBossNum3::__runNumber3Car(float dt){
	this->carMonsterList.at(2)->runAction(EaseIn::create(MoveBy::create(5.0f, Vec2(-1400, 0)), 3.0f));
}

void MonsterBossNum3::__removeTheCar(float dt){
	static int times;
	for (auto monster : carMonsterList)
	{
		this->getParent()->removeChild(monster);
	}
	if (times<=2)
	{	
		showTheCar(1.0f);
		times++;
	}
	else
	{
		times = 0;
		this->getFSM()->OnRecvBossWantToUseSkill(this);
	}

}

void MonsterBossNum3::__isCarCollide(float dt){
	for (auto monster:carMonsterList)
	{
		if (monster->getBoundingBox().intersectsRect(targetHero->getBoundingBox()))
		{		
			targetHero->getHurt(10, 2.0f, 0, 0);
			targetHero->runAction(MoveBy::create(1.0f,Vec2(-50,0)));
			this->unschedule(schedule_selector(MonsterBossNum3::__isCarCollide));
		}
	}
}

void MonsterBossNum3::__bossRunOutOfGround(float dt){
	ccBezierConfig bezierCon;
	bezierCon.controlPoint_1 = Vec2(this->getPositionX(), this->getPositionY());
	bezierCon.controlPoint_2 = Vec2((this->getPositionX() + 640) / 2, (((200) > (this->getPositionY())) ? (200) : (this->getPositionY())) + 300);
	bezierCon.endPosition = Vec2(640, 200);
	BezierTo* bezierAction = BezierTo::create(2.0f, bezierCon);
	this->runAction(Sequence::create(bezierAction,DelayTime::create(1.0f), MoveBy::create(3.0f, Vec2(0, 1000)), NULL));
	this->scheduleOnce(schedule_selector(MonsterBossNum3::__skillDropBox), 2.0f);
}

void MonsterBossNum3::__skillDropBox(float dt){
	
	for (int i = 0; i < 4; i++)
	{
		auto box = Monster::create(Sprite::create("wolf.png"), MonsterType::block);
		box->setPosition(258 * (i + 1), 1000);
		this->boxList.pushBack(box);
		this->notFallBoxList.pushBack(box);
		this->getParent()->addChild(box);

		auto shadow = Monster::create(Sprite::create("shadow.jpg"), MonsterType::block);
		shadowList.pushBack(shadow);
	}

	for (int i = 0; i < 4;i++)
	{
		isPlaceVacant[i] = 0;
	}
	
	this->schedule(schedule_selector(MonsterBossNum3::__dropBoxCollide));
	this->schedule(schedule_selector(MonsterBossNum3::__findAnyVacantPlace),8.0f);

}

void MonsterBossNum3::__dropBoxCollide(float dt){

	for (auto monster : notFallBoxList)
	{
		if (monster->getBoundingBox().intersectsRect(this->targetHero->getBoundingBox()))
		{
			this->getParent()->removeChild(monster);
			monster->setPosition((lastBoxNumber+1)*258,1000);
			
			
			//need amend
			monster->setHp(monster->getHp() + 500);
			this->getParent()->addChild(monster);
			this->getParent()->removeChild(shadowList.at(lastBoxNumber));
			isPlaceVacant[lastBoxNumber] = 0;
			log("collide---------------");
		}
	}
}

void MonsterBossNum3::__dropBoxEnd(float dt){
	
	for (auto box : boxList)
	{
		this->getParent()->removeChild(box);
	}
	targetHero->m_blockArea.clear();
	notFallBoxList.clear();
	shadowList.clear();
	boxList.clear();
	
	
	
	ccBezierConfig bezierCon;
	bezierCon.controlPoint_1 = Vec2(640, 200);
	bezierCon.controlPoint_2 = Vec2(540 , 600);
	bezierCon.endPosition = Vec2(440,200);
	BezierTo* bezierAction = BezierTo::create(1.5f, bezierCon);
	this->runAction(Sequence::create(MoveBy::create(2.0f, Vec2(0, -1000)), bezierAction, NULL));

	this->outBoss3SkillSequence(1.0f);
}

void MonsterBossNum3::__showTheShadow(int boxNumber){
	shadowList.at(boxNumber)->setScale(0.1f);
	shadowList.at(boxNumber)->setPosition(258 * (lastBoxNumber + 1), 200);
	this->getParent()->addChild(shadowList.at(boxNumber), -1);
	auto scaleby = ScaleBy::create(6.0f, 7.0f);
	shadowList.at(boxNumber)->runAction(scaleby);
}

void MonsterBossNum3::__findAnyVacantPlace(float dt){
	int boxNumber=0;
	static int boxQuantity;
	boxNumber = CCRANDOM_0_1() * 4 ;
	auto callFunc = CallFunc::create([&](){
		if (isPlaceVacant[lastBoxNumber]==1)
		{
			this->targetHero->m_blockArea.pushBack(boxList.at(lastBoxNumber));
			this->notFallBoxList.eraseObject(boxList.at(lastBoxNumber));
			this->getParent()->removeChild(shadowList.at(lastBoxNumber));
		}		
	});
	if (boxQuantity<=1)
	{
		if (isPlaceVacant[boxNumber] == 0)
		{
			isPlaceVacant[boxNumber] = 1;
			lastBoxNumber = boxNumber;
			boxList.at(boxNumber)->runAction(Sequence::create(DelayTime::create(6.0f), MoveBy::create(1.0f, Vec2(0, -800)), callFunc, NULL));
			boxQuantity++;
			__showTheShadow(boxNumber);
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				if (isPlaceVacant[i] == 0)
				{
					isPlaceVacant[i] = 1;
					lastBoxNumber = i;
					__showTheShadow(i);
					boxQuantity++;
					boxList.at(i)->runAction(Sequence::create(DelayTime::create(6.0f), MoveBy::create(1.0f, Vec2(0, -800)), callFunc, NULL));
					break;
				}
			}
		}
	}
	else{
		boxQuantity = 0;
		this->scheduleOnce(schedule_selector(MonsterBossNum3::__dropBoxEnd), 5.0f);
		this->unschedule(schedule_selector(MonsterBossNum3::__findAnyVacantPlace));
	}
	
}