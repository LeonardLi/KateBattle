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
#include "SoundsController.h"
#include "SoundsDef.h"
#include "TreasureBox.h"
#include "coin.h"
#define SHOOTRATE 0.5
#define MONSTER1WIDTH 75
#define MONSTER1HEIGHT 160

#define BOXADDBLOOD 50

USING_NS_CC;
using namespace cocostudio;
using namespace CocosDenshion;

#define DEFAULTVIEWRANGE 500.0f
#define DEFAULTATTACKTIME 2.0f
#define DEFAULTSPEEDRATE 0.5f
#define DEFAULTDEFENCEVALUE 0.0f

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
		setStun(NOTSTUN);	
		setboxTag(-1);
		setattackRange(100.0f);
		setAttackValue(10.0f);
		setDefenceValue(DEFAULTDEFENCEVALUE);
		setSpeedRate(DEFAULTSPEEDRATE);
		setHp(10.0f);
		setupperHp(10.0f);
		setattackTime(DEFAULTATTACKTIME);
		setviewRange(DEFAULTVIEWRANGE);

		setdirection(false);
		setAttacked(false);
		setisMoving(false);
		setisStanding(true);
		setisDead(false);
		setcanAttack(true);

		skillOrAttack = false;
		bossOrNot = false;
		
		setexistScreen(0);
		switch (type)
		{
		case  MonsterType::normalTypeLv1:
			_loadCSB("monster1/monster1.csb",17);
			m_monsterType = MonsterType::normalTypeLv1;
			monsterLevel = 1;
			setviewRange(500.0f);
			setHp(150);
			setupperHp(150);
			setAttackValue(60.0f);
			setDefenceValue(24.0f);
			setattackRange(100.0f);
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			createName("Brown Hyde Lv1", 90);
			break;
		case MonsterType::normalAggressiveTypeLv1:
			_loadCSB("monster1/monster1.csb", 17);
			m_monsterType = MonsterType::normalAggressiveTypeLv1;
			monsterLevel = 1;
			setHp(180);
			setupperHp(180);
			setattackRange(100.0f);
			setAttackValue(100.0f);
			setDefenceValue(26.0f);
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			createName("Cruel Manu Lv1", 90);
			break;
		case MonsterType::normalMoveFastTypeLv1:
			_loadCSB("monster1/monster1.csb", 17);
			m_monsterType = MonsterType::normalMoveFastTypeLv1;
			monsterLevel = 1;
			setHp(150);
			setupperHp(150);
			setattackRange(100.0f);
			setDefenceValue(20.0f);
			setAttackValue(60.0f);
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			setSpeedRate(0.9f);
			createName("Swift Doug Lv1", 90);
			
			break;
		case MonsterType::normalAttackFastTypeLv1:
			_loadCSB("monster1/monster1.csb", 17);
			m_monsterType = MonsterType::normalAttackFastTypeLv1;
			monsterLevel = 1;
			setHp(150);
			setupperHp(150);
			setattackRange(100.0f);
			setAttackValue(60.0f);
			setDefenceValue(25.0f);
			setattackTime(1.0f);
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			createName("Shadowless Lv1", 90);
			break;
		case MonsterType::normalFatTypeLv1:
			_loadCSB("monster9/monster9.csb", 33);
			m_monsterType = MonsterType::normalFatTypeLv1;
			monsterLevel = 1;
			setHp(250);
			setupperHp(250);
			setattackRange(120.0f);
			setAttackValue(70.0f);
			setDefenceValue(22.0f);
			setattackTime(2.0f);
			setContentSize(Size(105, 165));
			createName("Big Eater Lv1", 90);
			break;
		case MonsterType::normalIronTypeLv1:
			_loadCSB("monster2/monster2.csb", 19);
			m_monsterType = MonsterType::normalFatTypeLv1;
			monsterLevel = 1;
			setHp(60);
			setupperHp(60);
			setattackRange(100.0f);
			setDefenceValue(45.0f);
			setAttackValue(40.0f);
			setContentSize(Size(85, 105));
			createName("Stone Johnson Lv1", 90);
			break;	
		case MonsterType::shootTypeLv1:
			_loadCSB("monster8/monster8.csb", 31);
			setContentSize(Size(100, 140));
			setviewRange(600.0f);
			setHp(50);
			setupperHp(50);
			setDefenceValue(10.0f);
			m_monsterType = MonsterType::shootTypeLv1;
			monsterLevel = 1;
			setattackRange(500.0);
			createName("EF Shooter Lv1", 90);
			break;
		case MonsterType::shootAggressiveTypeLv1:
			_loadCSB("monster8/monster8.csb", 31);
			setContentSize(Size(100, 140));
			setHp(60);
			setupperHp(60);
			setDefenceValue(12.0f);
			m_monsterType = MonsterType::shootAggressiveTypeLv1;
			monsterLevel = 1;
			setattackRange(500.0);
			createName("EF Master Shooter Lv1", 90);
			break;
		case MonsterType::shootSlowTypeLv1:
			_loadCSB("monster8/monster8.csb", 31);
			setContentSize(Size(100, 140));
			setattackRange(600.0);
			setHp(60);
			setupperHp(60);		
			setDefenceValue(10.0f);
			m_monsterType = MonsterType::shootSlowTypeLv1;
			monsterLevel = 1;
			setattackRange(500.0);
			createName("EF Slug Lv1", 90);
			break;
		case  MonsterType::normalTypeLv2:
			_loadCSB("monster1/monster1.csb", 17);
			m_monsterType = MonsterType::normalTypeLv2;
			setHp(200);
			setupperHp(200);
			setviewRange(500.0f);
			setattackRange(100.0f);
			setAttackValue(180.0f);
			setDefenceValue(40.0f);
			monsterLevel = 2;
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			createName("Brown Hyde Lv2", 90);
			break;
		case MonsterType::normalAggressiveTypeLv2:
			_loadCSB("monster1/monster1.csb", 17);
			m_monsterType = MonsterType::normalAggressiveTypeLv2;
			setHp(270);
			setupperHp(270);
			setattackRange(100.0f);
			monsterLevel = 2;
			setAttackValue(240.0f);
			setDefenceValue(55.0f);
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			createName("Cruel Manu Lv2", 90);
			break;
		case MonsterType::normalMoveFastTypeLv2:
			_loadCSB("monster1/monster1.csb", 17);
			m_monsterType = MonsterType::normalMoveFastTypeLv2;
			setHp(200);
			setupperHp(200);
			setattackRange(100.0f);
			setAttackValue(200.0f);
			setDefenceValue(50.0f);
			monsterLevel = 2;
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			setSpeedRate(1.0f);
			createName("Swift Doug Lv2", 90);
			break;
		case MonsterType::normalAttackFastTypeLv2:
			_loadCSB("monster1/monster1.csb", 17);
			m_monsterType = MonsterType::normalAttackFastTypeLv2;
			setHp(200);
			setupperHp(200);
			setattackRange(100.0f);
			setAttackValue(200.0f);
			setDefenceValue(50.0f);
			setattackTime(1.0f);
			monsterLevel = 2;
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			createName("Shadowless Lv2", 90);
			break;
		case MonsterType::normalFatTypeLv2:
			_loadCSB("monster9/monster9.csb", 33);
			m_monsterType = MonsterType::normalFatTypeLv2;
			setHp(400);
			setupperHp(400);
			setattackRange(120.0f);
			setAttackValue(300.0f);
			setDefenceValue(50.0f);
			setattackTime(3.0f);
			monsterLevel = 2;
			setContentSize(Size(105, 165));
			createName("Big Eater Lv2", 90);
			break;
		case MonsterType::normalIronTypeLv2:
			_loadCSB("monster2/monster2.csb", 19);
			m_monsterType = MonsterType::normalFatTypeLv2;
			setHp(140);
			setupperHp(140);
			setattackRange(100.0f);
			setAttackValue(200.0f);
			setDefenceValue(95.0f);
			monsterLevel = 2;
			setContentSize(Size(85, 105));
			createName("Stone Johnson Lv2", 90);
			break;
		case MonsterType::shootTypeLv2:
			_loadCSB("monster8/monster8.csb", 31);
			setContentSize(Size(100, 140));
			setviewRange(600.0f);
			setHp(120);
			setupperHp(120);
			setDefenceValue(30.0f);
			monsterLevel = 2;
			m_monsterType = MonsterType::shootTypeLv2;
			setattackRange(600.0);
			createName("EF Shooter Lv2", 90);
			break;
		case MonsterType::shootAggressiveTypeLv2:
			_loadCSB("monster8/monster8.csb", 31);
			setContentSize(Size(100, 140));

			setHp(140);
			setupperHp(140);
			setDefenceValue(40.0f);
			monsterLevel = 2;
			m_monsterType = MonsterType::shootAggressiveTypeLv2;
			setattackRange(600.0);
			createName("EF Master Shooter Lv2", 90);
			break;
		case MonsterType::shootSlowTypeLv2:
			_loadCSB("monster8/monster8.csb", 31);
			setContentSize(Size(100, 140));

			setHp(140);
			setupperHp(140);
			setDefenceValue(30.0f);
			monsterLevel = 2;
			m_monsterType = MonsterType::shootSlowTypeLv2;
			setattackRange(600.0);
			createName("EF Slug Lv2", 90);
			break;

		case  MonsterType::normalTypeLv3:
			_loadCSB("monster1/monster1.csb", 17);
			m_monsterType = MonsterType::normalTypeLv3;
			setHp(600);
			setupperHp(600);
			setviewRange(500.0f);
			setattackRange(100.0f);
			setAttackValue(400.0f);
			setDefenceValue(75.0f);
			monsterLevel = 3;
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			createName("Brown Hyde Lv3", 90);
			break;
		case MonsterType::normalAggressiveTypeLv3:
			_loadCSB("monster1/monster1.csb", 17);
			m_monsterType = MonsterType::normalAggressiveTypeLv3;
			setHp(800);
			setupperHp(800);
			setattackRange(100.0f);
			monsterLevel = 3;
			setAttackValue(500.0f);
			setDefenceValue(90.0f);
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			createName("Cruel Manu Lv3", 90);
			break;
		case MonsterType::normalMoveFastTypeLv3:
			_loadCSB("monster1/monster1.csb", 17);
			m_monsterType = MonsterType::normalMoveFastTypeLv3;
			setHp(600);
			setupperHp(600);
			setattackRange(100.0f);
			setAttackValue(240.0f);
			setDefenceValue(95.0f);
			monsterLevel = 3;
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			setSpeedRate(1.0f);
			createName("Swift Doug Lv3", 90);
			break;
		case MonsterType::normalAttackFastTypeLv3:
			_loadCSB("monster1/monster1.csb", 17);
			m_monsterType = MonsterType::normalAttackFastTypeLv3;
			setHp(600);
			setupperHp(600);
			setattackRange(100.0f);
			setAttackValue(180.0f);
			setattackTime(1.0f);
			setDefenceValue(80.0f);
			monsterLevel = 3;
			setContentSize(Size(MONSTER1WIDTH, MONSTER1HEIGHT));
			createName("Shadowless Lv3", 90);
			break;
		case MonsterType::normalFatTypeLv3:
			_loadCSB("monster9/monster9.csb", 33);
			m_monsterType = MonsterType::normalFatTypeLv3;
			setHp(1200);
			setupperHp(1200);
			setattackRange(120.0f);
			setAttackValue(650.0f);
			setattackTime(3.0f);
			setDefenceValue(100.0f);
			monsterLevel = 3;
			setContentSize(Size(105, 165));
			createName("Big Eater Lv3", 90);
			break;
		case MonsterType::normalIronTypeLv3:
			_loadCSB("monster2/monster2.csb", 19);
			m_monsterType = MonsterType::normalFatTypeLv3;
			setHp(450);
			setupperHp(450);
			setattackRange(100.0f);
			setAttackValue(500.0f);
			setDefenceValue(240.0f);
			monsterLevel = 3;
			setContentSize(Size(85, 105));
			createName("Stone Johnson Lv3", 90);
			break;
		case MonsterType::shootTypeLv3:
			_loadCSB("monster8/monster8.csb", 31);
			setContentSize(Size(100, 140));
			setviewRange(600.0f);
			setHp(280);
			setupperHp(280);
			setDefenceValue(50.0f);
			monsterLevel = 3;
			m_monsterType = MonsterType::shootTypeLv3;
			setattackRange(600.0);
			createName("EF Shooter Lv3", 90);
			break;
		case MonsterType::shootAggressiveTypeLv3:
			_loadCSB("monster8/monster8.csb", 31);
			setContentSize(Size(100, 140));
			setHp(200);
			setupperHp(200);
			setDefenceValue(60.0f);
			monsterLevel = 3;
			m_monsterType = MonsterType::shootAggressiveTypeLv3;
			setattackRange(600.0);
			createName("EF Master Shooter Lv3", 90);
			break;
		case MonsterType::shootSlowTypeLv3:
			_loadCSB("monster8/monster8.csb", 31);
			setContentSize(Size(100, 140));

			setHp(150);
			setupperHp(150); 
			setDefenceValue(50.0f);
			monsterLevel = 3;
			m_monsterType = MonsterType::shootSlowTypeLv3;
			setattackRange(600.0);
			createName("EF Slug Lv3", 90);
			break;

		case MonsterType::num1ShootType:
			_loadCSB("monster8/monster8.csb", 31);
			m_monsterType = MonsterType::num1ShootType;
			setContentSize(Size(100,140));
			setattackRange(1500.0);
			setHp(200);
			setupperHp(200);
			setDefenceValue(40.0f);
			createName("Helper", 90);
			break;
		case MonsterType::num1BoxType:
			break;
		case  MonsterType::block:
			bindSprite(sprite);
			m_monsterType = MonsterType::block;
			setcanAttack(false);
			break;
		case  MonsterType::num3CarType:
			bindSprite(sprite);
			m_monsterType = MonsterType::num3CarType;
			setcanAttack(false);
			break;
		case  MonsterType::num3BoxType:
			m_monsterType = MonsterType::num3BoxType;
			_loadCSB("jbox/jbox.csb", 9);
			setHp(100);
			setupperHp(100);
			setContentSize(Size(330,260));	
			createName("Box", 90);
			break;
		case MonsterType::monsterBossNum2Assister:
			m_monsterType = MonsterType::monsterBossNum2Assister;
			_loadCSB("monster7/monster7.csb", 29);
			setHp(50);
			setupperHp(50);
			setcanAttack(false);
			skillOrAttack = true;
			break;
		default:
			break;
		}
		if (getcanAttack()==true)
		{
			createBloodBar(false);
		}
		
		m_FSM = MonsterFSM::createWithMonster(this);
		bRet = true;
	} while (0);
	
	return bRet;
}

void Monster::_loadCSB(std::string csbfile,int tagNum){
	mViewNode = static_cast<Node*>(CSLoader::createNode(csbfile));
	m_armature = static_cast<Armature*>(mViewNode->getChildByTag(tagNum));	
	m_armature->getAnimation()->play("stand");
	mViewNode->setScale(0.5, 0.5);
	setAnchorPoint(Vec2(0.5, 0.5));
	addChild(mViewNode);
}

MonsterFSM* Monster::getFSM(){
	return m_FSM;
}

void Monster::attackSequence(){
	switch (m_monsterType)
	{
	case MonsterType::normalTypeLv1:
	case MonsterType::monsterBossNum1:
	case MonsterType::monsterBossNum2Assister:
		break;
	case MonsterType::shootTypeLv1:
		__initBullet(1);
		break;
	case MonsterType::num1ShootType:
		__initBullet(2);
		break;
	case MonsterType::shootAggressiveTypeLv1:
		__initBullet(3);
		break;
	case MonsterType::shootSlowTypeLv1:
		__initBullet(4);
		break;
	case MonsterType::shootTypeLv2:
		__initBullet(5);
		break;
	case MonsterType::shootAggressiveTypeLv2:
		__initBullet(6);
		break;
	case MonsterType::shootSlowTypeLv2:
		__initBullet(7);
		break;
	case MonsterType::shootTypeLv3:
		__initBullet(8);
		break;
	case MonsterType::shootAggressiveTypeLv3:
		__initBullet(9);
		break;
	case MonsterType::shootSlowTypeLv3:
		__initBullet(10);
		break;
	case MonsterType::monsterBossNum3:
		this->schedule(schedule_selector(MonsterBossNum3::isHeroCloseToBoss));
		break;
	default:
		break;
	}
	log("monster attackSequence_______");
	__readyForAttack(1.0f);
}

void Monster::__initBullet(int bulletType){
	BulletBase* bullet = NULL;

	for (int i = 0; i < 5; i++)
	{
		switch (bulletType)
		{
		case 1:
			bullet = BulletNormal::create(Sprite::create("bullet.png"));
			bullet->setBulletValue(55, 1.0f, 0.0f, 0.0f);
			break;
		case 2:
			bullet = BulletNormal::create(Sprite::create("bullet.png"));
			bullet->setBulletValue(300, 0.0f, 0.5f, 5.0f);
			break;
		case 3:
			bullet = BulletNormal::create(Sprite::create("bullet.png"));
			bullet->setBulletValue(65, 0.0f, 0.0f, 0.0f);
			break;
		case 4:
			bullet = BulletNormal::create(Sprite::create("bullet.png"));
			bullet->setBulletValue(5, 0.0f, 0.5f, 5.0f);
			break;
		case 5:
			bullet = BulletNormal::create(Sprite::create("bullet.png"));
			bullet->setBulletValue(2400, 0.0f, 0.5f, 5.0f);
			break;
		case 6:
			bullet = BulletNormal::create(Sprite::create("bullet.png"));
			bullet->setBulletValue(300, 0.0f, 0.0f, 0.0f);
			break;
		case 7:
			bullet = BulletNormal::create(Sprite::create("bullet.png"));
			bullet->setBulletValue(50, 0.0f, 0.5f, 5.0f);
			break;
		case 8:
			bullet = BulletNormal::create(Sprite::create("bullet.png"));
			bullet->setBulletValue(500, 0.0f, 0.5f, 5.0f);
			break;
		case 9:
			bullet = BulletNormal::create(Sprite::create("bullet.png"));
			bullet->setBulletValue(700, 0.0f, 0.0f, 0.0f);
			break;
		case 10:
			bullet = BulletNormal::create(Sprite::create("bullet.png"));
			bullet->setBulletValue(10, 0.0f, 0.5f, 5.0f);
			break;


		default:
			break;
		}		
		bullet->setUsed(false);
		m_bulletList.pushBack(bullet);
		this->targetHero->getParent()->addChild(bullet);
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
				if (bullet->getBoundingBox().intersectsRect(targetHero->getBoundingBox())&&targetHero->getisDead()==false)
				{
					log("hero get hurt~~~~~~~");		
					targetHero->getHurt(bullet->bulletDamage,bullet->bulletStunTime,bullet->bulletSlowDown,bullet->bulletSlowDownTime);
					bullet->stopAllActions();
					bullet->m_isArrive = true;
				}
				if (bullet->isArrive())
				{
					bullet->setUsed(false);
				}
			}
		}
	}
}

void Monster::__readyForAttack(float dt){
	if (this->getFSM()->getState() == MonsterFSM::toAttack || this->getFSM()->getState() == MonsterFSM::BossToAttack)
	{
		log("attack state!!~~");
		this->schedule(schedule_selector(Monster::__intoAttackSequence));
	}

	if (this->getFSM()->getState() == MonsterFSM::toUseSkill || this->getFSM()->getState() == MonsterFSM::BosstoUseSkill)
	{
		skillOrAttack = true;
	}	
}

void Monster::__intoAttackSequence(float dt){
	if (skillOrAttack==false)
	{
		this->unschedule(schedule_selector(Monster::__intoAttackSequence));
		this->schedule(schedule_selector(Monster::__isInViewRange));
	}
}

void Monster::__isInViewRange(float dt){

	Vec2 distance = Vec2(targetHero->getPositionX() - this->getPositionX(), targetHero->getPositionY() - this->getPositionY());
	if (distance.length() <= this->getviewRange())
	{
		log("hero  InView!!!!!!!!!!");
		__attack();
		this->unschedule(schedule_selector(Monster::__isInViewRange));
	}
	
}

void Monster::__attack(){
	if (getStun() == STUN || getisDead() == true)
	{
		return;
	}
	float randomNum = CCRANDOM_0_1();
	float moveAndAttack = 0.3;
	double standRate = 0.1;
	setisStanding(true);
	setisMoving(false);
	choiceDirectionToAction("stand");
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
	else if (randomNum > 0 && randomNum < standRate)
	{
		if (getisStanding() == false && getisMoving() == true)
		{
			setisStanding(true);
			setisMoving(false);
			choiceDirectionToAction("stand");
		}
		log("stand for 2s~~~~");
		this->scheduleOnce(schedule_selector(Monster::__readyForAttack), 2.0f);
	}
}

void Monster::__monsterMoveToHero(float dt){	
	Vec2 distance = Vec2(targetHero->getPositionX() - this->getPositionX(), targetHero->getPositionY() - this->getPositionY());
	if (getStun() == STUN||getisDead()==true)
	{
		this->unschedule(schedule_selector(Monster::__monsterMoveToHero));
		return;
	}
	if (distance.length() > this->getattackRange())
	{
		if (getisMoving() == false && getisStanding() == true)
		{
			setisStanding(false);
			setisMoving(true);
			choiceDirectionToAction("walk");
		}
		if (getAttacked()==true)
		{
			setAttacked(false);
			choiceDirectionToAction("walk");
		}

		if (getisMoving() == true)
		{
			bool dir;
			if (this->targetHero->getPositionX() < this->getPositionX())
			{
				dir = false;
			}
			else
				dir = true;
			if (dir != getdirection())
			{
				setisMoving(false);
				setisStanding(true);
			}
		}
		__moveCloseToHero(distance);
	}
	else
	{
		log("hero in range");
		this->unschedule(schedule_selector(Monster::__monsterMoveToHero));
		setisMoving(false);
		setisStanding(true);
		choiceDirectionToAction("stand");
		this->__attackafterMove();
	}
	if (CCRANDOM_0_1() < 0.001)
	{
		this->unschedule(schedule_selector(Monster::__monsterMoveToHero));
		if (getisStanding() == false && getisMoving() == true)
		{
			setisStanding(true);
			setisMoving(false);
			choiceDirectionToAction("stand");
		}
		this->scheduleOnce(schedule_selector(Monster::__readyForAttack), 2.0f);
	}
}

void Monster::__monsterRandomMove(){
	if (this->getStun() == STUN || getisDead() == true)
	{
		return;
	}
	Vec2 move = Vec2(0, 0);
	float randomNumX = (CCRANDOM_0_1() - 0.5) * 120;
	float randomNumY = (CCRANDOM_0_1() - 0.5) * 150;

	if (this->getPositionY()<75 && randomNumY<0)
	{
		randomNumY *= (-1);
	}
	if (this->getPositionY()>350 && randomNumY>0)
	{
		randomNumY *= (-1);
	}

	move = Vec2(randomNumX, randomNumY);
	if (getisStanding() == true && getisMoving() == false&&getStun()!=STUN)
	{
		setisStanding(false);
		setisMoving(true);
		if (randomNumX <= 0)
		{
			setdirection(false);
			m_armature->setScale(1.0f, 1.0f);
			this->m_armature->getAnimation()->play("walk");
		}
		else
		{
			setdirection(true);
			m_armature->setScale(-1.0f, 1.0f);
			this->m_armature->getAnimation()->play("walk");
		}
	}
	if (getStun() == STUN || getisDead() == true)
	{
		return;
	}
	else
	{
		this->runAction(MoveBy::create(1.0f, move));
		this->scheduleOnce(schedule_selector(Monster::__readyForAttack), 2.0f);
	}
}

void Monster::__attackafterMove(){
	if (getStun() == STUN||getisDead()==true)
	{
		return;
	}
	float randomNum = CCRANDOM_0_1();
	if (randomNum > 0.2)
	{
		log("monster attack!!! after move ");
		switch (m_monsterType)
		{	
		case MonsterType::normalTypeLv1:
		case MonsterType::normalFatTypeLv1:
		case MonsterType::normalAggressiveTypeLv1:
		case MonsterType::normalAttackFastTypeLv1:
		case MonsterType::normalIronTypeLv1:
		case MonsterType::normalMoveFastTypeLv1:

		case MonsterType::normalTypeLv2:
		case MonsterType::normalFatTypeLv2:
		case MonsterType::normalAggressiveTypeLv2:
		case MonsterType::normalAttackFastTypeLv2:
		case MonsterType::normalIronTypeLv2:
		case MonsterType::normalMoveFastTypeLv2:

		case MonsterType::normalTypeLv3:
		case MonsterType::normalFatTypeLv3:
		case MonsterType::normalAggressiveTypeLv3:
		case MonsterType::normalAttackFastTypeLv3:
		case MonsterType::normalIronTypeLv3:
		case MonsterType::normalMoveFastTypeLv3:

		case MonsterType::monsterBossNum1:
		case MonsterType::monsterBossNum2:
		case MonsterType::monsterBossNum3:

			__attackWithHand();
			break;
		case MonsterType::num1ShootType:
		case MonsterType::shootTypeLv1:
		case MonsterType::shootAggressiveTypeLv1:
		case MonsterType::shootSlowTypeLv1:
		case MonsterType::shootTypeLv2:
		case MonsterType::shootAggressiveTypeLv2:
		case MonsterType::shootSlowTypeLv2:
		case MonsterType::shootTypeLv3:
		case MonsterType::shootAggressiveTypeLv3:
		case MonsterType::shootSlowTypeLv3:

			__attackWithBullet();
			break;
		default:
			break;
		}
	}
	else
	{
		setisMoving(false);
		setisStanding(true);
		choiceDirectionToAction("stand");
		log("stand---------------");
		this->scheduleOnce(schedule_selector(Monster::__finishAttack), 2.0f);
	}
}

void Monster::__attackWithHand(){
	if (getStun() == STUN || getisDead() == true)
	{
		return;
	}
	auto callFunc = CallFunc::create([=](){		
		if (getStun() == STUN || getisDead() == true)
		{
			return;
		}
		if (this->targetHero->getPositionX() < this->getPositionX())
		{
			setdirection(false);
			m_armature->setScale(1.0f, 1.0f);
			m_armature->getAnimation()->play("attack", -1, 0);
		}
		else
		{
			setdirection(true);
			m_armature->setScale(-1.0f, 1.0f);
			m_armature->getAnimation()->play("attack", -1, 0);
		}
		__judgeAttackHero();	
	});
	this->m_armature->getAnimation()->gotoAndPause(0);
	this->runAction(Sequence::create(DelayTime::create(getattackTime()), callFunc, NULL));
	if (m_monsterType==MonsterType::monsterBossNum1||m_monsterType==MonsterType::monsterBossNum2)
	{
		float randomNum = CCRANDOM_0_1();
		if (randomNum >= 0.25&&randomNum <= 0.8)
		{
			this->getFSM()->OnRecvBossWantToUseSkill(this);
		}
	}
	this->scheduleOnce(schedule_selector(Monster::__finishAttack), 3.0f + getattackTime());
}

void Monster::__judgeAttackHero(){
	Rect rect;
	if (getStun() == STUN || getisDead() == true)
	{
		return;
	}
	
	if (m_direction==false)
	{
		rect = Rect(this->getPositionX() - this->getattackRange()*0.85, this->getPositionY(), this->getattackRange()*0.85+30, this->getattackRange()/2);
	}
	else
		rect = Rect(this->getPositionX(), this->getPositionY(), this->getattackRange()*0.85 + 30, this->getattackRange() / 2);


	if (this->targetHero->getBoundingBox().intersectsRect(rect)&&this->targetHero->getisDead()==false)
	{
		float time = 0.0f;
		if (getAttackValue()-this->targetHero->getcurDefenceValue()>30)
		{
			time = 1.5f;
		}
		this->targetHero->getHurt(getAttackValue(), time, 0.0f, 0.0);
	}

}

void Monster::__attackWithBullet(){
	if (getStun() == STUN || getisDead() == true)
	{
		return;
	}
	//Rect rect = this->getBoundingBox();
	//auto s = Director::getInstance()->getWinSize();
	//auto draw = DrawNode::create();
	//this->getParent()->addChild(draw, 10);
	////Vec2 points[] = { Vec2(0, 0), Vec2(rect.size.width, 0), Vec2(rect.size.width, rect.size.height), Vec2(0, rect.size.height) };
	//Vec2 points[] = { Vec2(rect.origin.x, rect.origin.y), Vec2(rect.origin.x + rect.size.width, rect.origin.y), Vec2(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height), Vec2(rect.origin.x, rect.origin.y + rect.size.height) };
	//draw->drawPolygon(points, sizeof(points) / sizeof(points[0]), Color4F(1, 0, 0, 0.5), 4, Color4F(0, 0, 1, 1));

	float randomNum = CCRANDOM_0_1();
	{
		if (randomNum <= SHOOTRATE)
		choiceDirectionToAction("attack");
		BulletBase* bullet = this->__getAnyUnUsedBullet();
		if (bullet != NULL)
		{
			SimpleAudioEngine::getInstance()->playEffect(EFFECTS_20.c_str());
			bullet->setPosition(this->getPositionX(),this->getPositionY()+this->getContentSize().height/2);
			bullet->onLockAim(targetHero);
		}
	}
	this->scheduleOnce(schedule_selector(Monster::__finishAttack), 2.0f);
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
	if (getStun() == STUN || getisDead() == true)
	{
		return;
	}
	if (getisStanding()==false&&getisMoving()==true)
	{
		setisStanding(true);
		setisMoving(false);
		choiceDirectionToAction("stand");
	}
	this->__readyForAttack(1.0f);
	log("finish attack~~~~");
}

void Monster::useSkillSequence(){
	__readyForUseSkill(0.0f);
}

void Monster::__readyForUseSkill(float dt){
	if (this->getFSM()->getState() == MonsterFSM::toUseSkill)
	{
		this->schedule(schedule_selector(Monster::__intoSkillSequence));
	}

	else if (this->getFSM()->getState() == MonsterFSM::BosstoUseSkill)
	{
		this->schedule(schedule_selector(Monster::__intoSkillSequence));
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
	case MonsterType::monsterBossNum2:
		log("boss num 2 skill-++++++++++++++++++");
		this->scheduleOnce(schedule_selector(MonsterBossNum2::intoBoss2SkillSequence), 0.0f);
		break;
	case MonsterType::monsterBossNum3:
		log("Number3 BOSS!-------- skill!!");
		this->scheduleOnce(schedule_selector(MonsterBossNum3::intoBoss3SkillSequence),0.0f);
		break;
	case MonsterType::monsterBossNum2Assister:
		log("Boss 2 assister skill------------------");
		break;
	default:
		break;
	}
}

void Monster::__moveCloseToHero(Vec2 distance){
	
	Vec2 speed = distance / distance.length();
	speed.x *= getSpeedRate();
	speed.y *= getSpeedRate();
	this->setPosition(this->getPositionX() + speed.x, this->getPositionY() + speed.y);
}

void Monster::skillFinish(float dt){
	log("finishskill!");
	skillOrAttack = false;
	__postBossAttackMessage(1.0f);
	//readyForUseSkill(1.0f);
	
	
}

void Monster::__postBossAttackMessage(float dt){
	this->getFSM()->OnRecvBossWantToAttack(this);
}

void Monster::__postBossSkillMessage(float dt){
	this->getFSM()->OnRecvBossWantToUseSkill(this);
}

void Monster::choiceDirectionToAction(std::string action){
	if (this->targetHero->getPositionX() < this->getPositionX())
	{
		setdirection(false);
		m_armature->setScale(1.0f, 1.0f);
		m_armature->getAnimation()->play(action);
		
	}
	else
	{	
		setdirection(true);
		m_armature->setScale(-1.0f, 1.0f);
		m_armature->getAnimation()->play(action);		
	}
}

void Monster::onDead(){
	this->stopAllActions();
	if (this->m_monsterType==MonsterType::num3BoxType)
	{
	}
	else
	{
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_25.c_str());
		this->m_armature->getAnimation()->stop();
		if (this->targetHero->getPositionX() < this->getPositionX())
		{
			m_armature->setScale(1.0f, 1.0f);
			this->m_armature->getAnimation()->play("dead",-1,0);

		}
		else
		{
			m_armature->setScale(-1.0f, 1.0f);
			m_armature->getAnimation()->play("dead",-1,0);
		}
		if (bossOrNot == true)
		{
			this->targetHero->getMoney(true,this->monsterLevel);
		}
		else
			this->targetHero->getMoney(false,this->monsterLevel);

	}

	if (this->m_monsterType != MonsterType::num3BoxType)
	{
		if (this->bossOrNot==true)
		{
			auto box = TreasureBox::create(static_cast<ScenarioEnum>(this->monsterLevel - 1));
			box->setPosition(this->getPositionX(), this->getPositionY() - 40);
			this->getParent()->addChild(box);
		}
		else
		{
			float randomNum = RandomHelper::random_real(0.0f, 1.0f);
			if (randomNum>0.8)
			{
				auto box = TreasureBox::create(static_cast<ScenarioEnum>(this->monsterLevel - 1));
				box->setPosition(this->getPositionX(), this->getPositionY() - 40);
				this->getParent()->addChild(box);
			}
			else
			{
				float randomNum1 = RandomHelper::random_real(0.0f, 1.0f);
				if (randomNum1>0.4)
				{
					auto coin = Coin::create(static_cast<ScenarioEnum>(this->monsterLevel - 1));
					coin->setPosition(this->getPositionX(), this->getPositionY() - 40);
					this->getParent()->addChild(coin);
				}
			}
		}


	}
}

void Monster::onHurt(){
	
	if (this->m_monsterType == MonsterType::num3BoxType || this->m_monsterType == MonsterType::monsterBossNum1 || this->m_monsterType == MonsterType::monsterBossNum3 || this->m_monsterType == MonsterType::monsterBossNum2)
	{
	}
	else
	{
		if (getisDead()==false)
		{
			this->m_armature->getAnimation()->play("hurt", -1, 0);
		}
		auto callFunc = CallFunc::create([=](){
			this->setAttacked(true);
		});
		this->runAction(Sequence::create(DelayTime::create(1.0f), callFunc, NULL));
	}
	
}

void Monster::update(float dt){
}

void Monster::__changeStun(float){
	if (getisDead()==false)
	{
		this->choiceDirectionToAction("stand");
		if (getStun() == STUN)
		{
			setStun(NOTSTUN);
		}
	}	
}

void Monster::monsterGetHurt(float iValue, float time, bool isCrit, bool isMagic){
	
	
	float iCurHp = getHp();
	float attatkValue;
	if (isMagic==true)
	{
		attatkValue = iValue;
	}
	else
	{
		attatkValue = iValue - getDefenceValue();
	}
	if (attatkValue <= 0)
	{
		attatkValue = 0;
	}
	
	else
	{
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_23.c_str());
	}

	int valueInt = attatkValue;
	auto value = std::to_string(valueInt);
		
	Label* label = Label::create(value, "fonts/Marker Felt.ttf", 30);
	label->setPosition(Vec2(this->getBoundingBox().size.width / 2, this->getBoundingBox().size.height + 40));
	this->addChild(label,4);
	FadeIn* action1 = FadeIn::create(0.5f);
	MoveBy* action2 = MoveBy::create(1.0f, Vec2(0, 40));
	FadeOut* action3 = FadeOut::create(0.5f);
	Sequence* seq1 = Sequence::create(action2, action3, NULL);
	Sequence* seq2 = Sequence::create(action1, seq1, NULL);
	auto seq3 = seq2->clone();	
		
	if (isCrit)
	{
		label->setColor(Color3B::RED);
		auto sprite = Sprite::create("crit.png");
		sprite->setPosition(Vec2(this->getBoundingBox().size.width / 2, this->getBoundingBox().size.height + 40));
		this->addChild(sprite,3);
		sprite->runAction(seq3);	
	}
	else
	label->setColor(Color3B::WHITE);
	label->runAction(seq2);
	


	float iAfterHp = iCurHp - attatkValue ;

	if (iAfterHp > 0)
	{
		this->onHurt();
		setHp(iAfterHp);
		if (getcanAttack()==true)
		{
			this->blood->setPercentage(iAfterHp / getupperHp()*100.0f);
		}
	}


	else
	{
		setHp(0.0);
		if (this->getcanAttack() == true)
		{
			bloodBar->setVisible(false);
			nameLabel->setVisible(false);
		}
		
		this->setisDead(true);
		onDead();
		if (getcanAttack() == true)
		{
			this->blood->setPercentage(0.0f);
		}
	}

	if (this->getStun() == NOTSTUN&&time > 0.5&&this->m_monsterType != MonsterType::num3BoxType)
	{

		this->setStun(STUN);
		if (getisDead()==false)
		{
			this->choiceDirectionToAction("dizzy");
		}		
	}

	if (m_isDead)
	{	
		if (isScheduled(schedule_selector(Monster::__readyForAttack)))
		{
			unschedule(schedule_selector(Monster::__readyForAttack));
		}
		return;
	}

	if (this->getStun() == STUN)
	{
		if (isScheduled(schedule_selector(Monster::__changeStun)))
		{
			unschedule(schedule_selector(Monster::__changeStun));
			this->scheduleOnce(schedule_selector(Monster::__changeStun), time);
		}
		else
			this->scheduleOnce(schedule_selector(Monster::__changeStun), time);

		if (isScheduled(schedule_selector(Monster::__readyForAttack)))
		{
			unschedule(schedule_selector(Monster::__readyForAttack));
			this->scheduleOnce(schedule_selector(Monster::__readyForAttack), time + 0.3f);
		}
		else
			this->scheduleOnce(schedule_selector(Monster::__readyForAttack), time + 0.3f);

	}
}

void Monster::skillShot(float dt){
	if (getisDead() == true)
	{
		this->unschedule(schedule_selector(Monster::skillShot));
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_21.c_str());
	this->m_armature->getAnimation()->play("attack",-1,0);
	static int times;
	times++;
	auto fireBall = Sprite::create("yuan.png");
	fireBall->setPosition(this->getPositionX(), this->getPositionY());
	this->getParent()->addChild(fireBall);
	Vec2 temporaryLocation = Vec2(this->targetHero->getPositionX(), this->targetHero->getPositionY());
	
	auto mark = Sprite::create("mark.png");
	mark->setPosition(this->targetHero->getPositionX(), this->targetHero->getPositionY());
	this->getParent()->addChild(mark);

	auto callfunc = CallFunc::create([=](){
		if (getisDead()==false)
		{
			this->m_armature->getAnimation()->play("stand");
		}	
		this->getParent()->removeChild(fireBall);
		this->getParent()->removeChild(mark);
		this->showFire(temporaryLocation);
	});
	ccBezierConfig bezierCon;
	bezierCon.controlPoint_1 = Vec2(this->getPositionX(), this->getPositionY());
	bezierCon.controlPoint_2 = Vec2((this->getPositionX() + this->targetHero->getPositionX()) / 2, (this->getPositionY() + this->targetHero->getPositionY())/2+200);
	bezierCon.endPosition = Vec2(this->targetHero->getPositionX(), this->targetHero->getPositionY());
	//throw time
	BezierTo* bezierAction = BezierTo::create(4.0f, bezierCon);

	fireBall->runAction(Sequence::create(bezierAction, callfunc, NULL));	
	
	if (times>2)
	{
		times = 0;
		this->unschedule(schedule_selector(Monster::skillShot));
	}
}

void Monster::showFire(Vec2 location){
	if (getisDead() == true)
	{
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_22.c_str());
	auto fire = Monster::create(Sprite::create("water.png"), MonsterType::block);
	fire->setPosition(location);
	this->getParent()->addChild(fire,-1);
	dangerousAreaList.pushBack(fire);
	auto callfunc = CallFunc::create([=](){
		this->getParent()->removeChild(fire);
		dangerousAreaList.eraseObject(fire);
	});
	//disappear time 
	fire->runAction(Sequence::create(DelayTime::create(10.0f), callfunc,NULL));
}

void Monster::boss2AssistStartSkill(){
	// interval time
	this->schedule(schedule_selector(Monster::skillShot), 6.0f);
}

void Monster::castMessage(std::string message){
	Label* label = Label::create(message, "fonts/Marker Felt.ttf", 30);
	label->setPosition(Vec2(targetHero->getBoundingBox().size.width/2,targetHero->getBoundingBox().size.height+100));
	label->setColor(Color3B::BLACK);
	this->targetHero->addChild(label, 2);
	FadeIn* action1 = FadeIn::create(0.5f);
	MoveBy* action2 = MoveBy::create(4.0f, Vec2(0, 40));
	FadeOut* action3 = FadeOut::create(0.5f);
	Sequence* seq1 = Sequence::create(action2, action3, NULL);
	Sequence* seq2 = Sequence::create(action1, seq1, NULL);
	label->runAction(seq2);
}

void Monster::createBloodBar(bool isBossOrNot){
	if (isBossOrNot==false)
	{
		blood = ProgressTimer::create(Sprite::create("blood.png"));
		blood->setType(ProgressTimer::Type::BAR);
		blood->setMidpoint(Vec2(0, 0));
		blood->setBarChangeRate(Vec2(1, 0));
		blood->setPercentage(100.0f);
		blood->setPosition(Vec2(getBoundingBox().size.width / 2 + 11, getBoundingBox().size.height + 60));
		blood->setScale(0.6f);
		addChild(blood, 2, 1);
		bloodBar = Sprite::create("bloodBar.png");
		bloodBar->setPosition(Vec2(getBoundingBox().size.width / 2, getBoundingBox().size.height + 60));
		bloodBar->setScale(0.6f);
		addChild(bloodBar, 1, 1);
	}
	else
	{
		blood = ProgressTimer::create(Sprite::create("blood.png"));
		blood->setType(ProgressTimer::Type::BAR);
		blood->setMidpoint(Vec2(0, 0));
		blood->setBarChangeRate(Vec2(1, 0));
		blood->setPercentage(100.0f);
		blood->setPosition(Vec2(getBoundingBox().size.width / 2 + 19, getBoundingBox().size.height + 80));
		blood->setScale(0.8f);
		this->addChild(blood, 2, 1);
		bloodBar = Sprite::create("bossBloodBar.png");
		bloodBar->setPosition(Vec2(getBoundingBox().size.width / 2, getBoundingBox().size.height + 80));
		bloodBar->setScale(0.8f);
		this->addChild(bloodBar, 1, 1);

	}
}

void Monster::createName(std::string str,int height){
	nameLabel = Label::create(str, "fonts/Marker Felt.ttf", 24);
	nameLabel->setPosition(Vec2(this->getBoundingBox().size.width / 2, this->getBoundingBox().size.height + height));
	nameLabel->setColor(Color3B::BLACK);
	this->addChild(nameLabel, 4);
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
		bossOrNot = true;
		skillOrAttack = false;
		setisDead(false);

		_loadCSB("monster5/monster5.csb", 25);
		shootMonsterList = monsterList;
		//set attribute
		setviewRange(700.0);
		setattackRange(160.0);
		setDefenceValue(93.0f);
		setattackTime(2.0f);
		setAttackValue(220.0f);
		setHp(1200.0f);
		setupperHp(1200.0f);
		setSpeedRate(0.6f);
		setcanAttack(true);	
		setStun(NOTSTUNFOREVER);
		this->setContentSize(Size(85, 160));
		monsterLevel = 2;
		m_monsterType = MonsterType::monsterBossNum1;
		createName("Hercules", 110);
		createBloodBar(true);

		m_FSM = MonsterFSM::createWithMonster(this);

		bRet = true;
	} while (0);
	return bRet;
}

void MonsterBossNum1::__skillRushBox(float dt){
	if (getisDead() == true)
	{
		return;
	}
	
	this->schedule(schedule_selector(MonsterBossNum1::__skillRush), 0.0, kRepeatForever, 10.0f);
	auto box = Monster::create(Sprite::create("box.png"), MonsterType::block);
	Vec2 boxPoint = Vec2(0, 0);
	
	float locationX = this->getPositionX();
	float locationY = this->getPositionY();
	if (locationX<=3700&&locationY<=175)
	{
		boxPoint = Vec2(4100,75);
	}

	else if (locationX > 3700 && locationY <= 175)
	{
		boxPoint = Vec2(3300, 280);
	}
	else if (locationX > 3700 && locationY > 175)
	{
		boxPoint = Vec2(3300, 75);
	}
	else
		boxPoint = Vec2(4100, 280);

	box->setPosition(boxPoint);
	this->getParent()->addChild(box);
	m_boxes = box;
	castMessage("hide behind the box!!!");
	targetHero->m_blockArea.pushBack(box);

	static int monsterExist = 0;
	if (monsterExist <= 2)
	{
		auto monster = shootMonsterList.at(monsterExist);
		this->getParent()->addChild(monster);
		this->targetHero->m_heroMonsterList.pushBack(monster);
		monster->getFSM()->OnRecvWantToAttack(monster);
		monsterExist ++;
	}

	this->schedule(schedule_selector(MonsterBossNum1::__isCollide), 0.0, kRepeatForever, 5.0f);
}

void MonsterBossNum1::__isCollide(float dt){
	
	if (this->getBoundingBox().intersectsRect(m_boxes->getBoundingBox()))
	{
		this->unschedule(schedule_selector(MonsterBossNum1::__isCollide));
		this->monsterGetHurt(100, 0.0f,false,true);
		if (getisDead()==false)
		{
			this->m_armature->getAnimation()->play("dizzy");
		}
		this->targetHero->m_blockArea.eraseObject(m_boxes);
		this->getParent()->removeChild(m_boxes);
		if (this->getHp()>0)
		{
			this->m_Stun = BOSSSTUN;
		}
		else
		{
			this->unschedule(schedule_selector(MonsterBossNum1::__skillRush));
			return;
		}
	}
	if (this->getBoundingBox().intersectsRect(this->targetHero->getBoundingBox()))
	{
		this->unschedule(schedule_selector(MonsterBossNum1::__isCollide));
		this->m_Stun = BOSSSTUN;
		this->targetHero->m_blockArea.eraseObject(m_boxes);
		this->getParent()->removeChild(m_boxes);
		this->targetHero->getHurt(50, 2.0f, 0, 0);
	}

}

void MonsterBossNum1::__skillRush(float dt){
	if (getisDead() == true)
	{
		return;
	}


	if (this->m_Stun == BOSSSTUN)
	{
		this->m_armature->getAnimation()->play("dizzy");
		this->unschedule(schedule_selector(MonsterBossNum1::__skillRush));
		setStun(NOTSTUNFOREVER);
		this->outBoss1SkillSequence(5.0f);
	}
	else
	{
		Vec2 distance = Vec2(targetHero->getPositionX() - this->getPositionX(), targetHero->getPositionY() - this->getPositionY());
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
		_loadCSB("monster6/monster6.csb",27);
		
		m_monsterType = MonsterType::monsterBossNum2;
		monsterAssist = monster;

		bossOrNot = true;
		skillOrAttack = false;
		setisDead(false);
		setStun(NOTSTUNFOREVER);

		setviewRange(1500.0);
		setattackTime(2.0f);
		setattackRange(150.0);
		setAttackValue(800.0f);
		setHp(2000.0f);
		setupperHp(2000.0f);
		setDefenceValue(120.0f);
		setSpeedRate(0.6f);
		setcanAttack(true);
		setContentSize(Size(90, 110));
		monsterLevel = 3;
		createBloodBar(true);
		createName("Evil Twins", 110);
		m_FSM = MonsterFSM::createWithMonster(this);
		bRet = true;
	} while (0);
	return bRet;
}

void MonsterBossNum2::intoBoss2SkillSequence(float dt){
	this->schedule(schedule_selector(MonsterBossNum2::__dangerousAreaJudge),1.0f);
	
	this->__bossJump();

	this->monsterAssist->boss2AssistStartSkill();
}

void MonsterBossNum2::__dangerousAreaJudge(float dt){
	for (auto monster:this->monsterAssist->dangerousAreaList)
	{
		if (monster->getBoundingBox().intersectsRect(this->targetHero->getBoundingBox()))
		{
			this->targetHero->getHurt(5.0f, 0.0f, 0.0f, 0.0f);
		}
	}

}

void MonsterBossNum2::__bossJump(){
	castMessage("run away!!!");
	setcanAttack(false);
	ccBezierConfig bezierCon;
	bezierCon.controlPoint_1 = Vec2(this->getPositionX(), this->getPositionY());
	bezierCon.controlPoint_2 = Vec2((this->getPositionX() + this->targetHero->getPositionX()) / 2, (this->getPositionY() + this->targetHero->getPositionY()) / 2 + 200);
	bezierCon.endPosition = Vec2(this->targetHero->getPositionX(), this->targetHero->getPositionY());
	//throw time
	BezierTo* bezierAction = BezierTo::create(3.0f, bezierCon);
	auto callfunc = CallFunc::create([=](){
		setcanAttack(true);
		this->__bossRotate();
	});

	this->runAction(Sequence::create(DelayTime::create(3.0f),bezierAction,DelayTime::create(3.0f),callfunc,NULL));

}

void MonsterBossNum2::__bossRotate(){
	if (getisDead() == true)
	{
		return;
	}
	this->m_armature->getAnimation()->play("circle");
	setcanAttack(false);
	this->schedule(schedule_selector(MonsterBossNum2::__rotateAreaJudge),1.0f);
	//load the rotate animation
	this->scheduleOnce(schedule_selector(MonsterBossNum2::__bossRotateStop), 5.0f);

}

void MonsterBossNum2::__rotateAreaJudge(float dt){
	if (this->getBoundingBox().intersectsRect(this->targetHero->getBoundingBox()))
	{
		this->targetHero->getHurt(600.0f, 0.0f, 0.2f, 1.0f);
		log("=============== hurt and slow ==============");
	}
}

void MonsterBossNum2::__bossRotateStop(float dt){
	this->unschedule(schedule_selector(MonsterBossNum2::__rotateAreaJudge));
	if (getisDead() == true)
	{
		return;
	}
	this->m_armature->getAnimation()->play("dizzy");
	setcanAttack(true);
	this->scheduleOnce(schedule_selector(MonsterBossNum2::__bossRushToBox), 10.0f);
	auto callFunc = CallFunc::create([=](){
		m_armature->setScale(-1.0f, 1.0f);
		this->m_armature->getAnimation()->play("ready"); 

	});
	auto callFunc1 = CallFunc::create([=](){
		m_armature->setScale(-1.0f, 1.0f);
		this->m_armature->getAnimation()->play("walk");
		SimpleAudioEngine::getInstance()->playEffect(EFFECTS_26.c_str());
		castMessage("move close to the boxes!!!");
	});
	this->runAction(Sequence::create(DelayTime::create(3.0f),callFunc1,MoveTo::create(2.0f, Vec2(3000, 300)),callFunc,NULL));
}

void MonsterBossNum2::__bossRushToBox(float dt){
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_27.c_str(),true);
	if (getisDead()==true)
	{
		return;
	}
	this->m_armature->getAnimation()->play("run");
	castMessage("move away!!!");
	float y = this->targetHero->getPositionY() - this->getPositionY();
	float x = this->targetHero->getPositionX() - this->getPositionX();
	this->schedule(schedule_selector(MonsterBossNum2::__bossRushJudge));
	if (x>0)
	{
		float angle = atanf(abs(y) / x);
		float degrees = CC_RADIANS_TO_DEGREES(angle);
		if (degrees<20)
		{
			auto callFunc = CallFunc::create([=](){
				SimpleAudioEngine::getInstance()->stopEffect(SimpleAudioEngine::getInstance()->playEffect(EFFECTS_27.c_str(), true));
				if (getisDead()==false)
				{
					this->m_armature->getAnimation()->play("dizzy");
				}				
				if (isScheduled(schedule_selector(MonsterBossNum2::__bossRushJudge)))
				{
					this->unschedule(schedule_selector(MonsterBossNum2::__bossRushJudge));
				}		
				if (this->monsterAssist->getisDead()==false)
				{
					this->monsterAssist->monsterGetHurt(25, 0.0, false, true);
				}		
				this->monsterGetHurt(200, 0.0, false,true);
			});

			this->runAction(Sequence::create(MoveBy::create(2.0f,Vec2(760, 0)),callFunc,NULL));			
		}

		else
			this->runAction(MoveTo::create(2.0f, Vec2(3000+(250 / tanf(abs(y) / x)), 50)));
	}

	else
	{
		this->runAction(MoveTo::create(2.0f, this->targetHero->getPosition()));
	}
	this->scheduleOnce(schedule_selector(MonsterBossNum2::outBoss2SkillSequence), 5.0f);
	
}

void MonsterBossNum2::__bossRushJudge(float dt){
	if (this->getBoundingBox().intersectsRect(this->targetHero->getBoundingBox()))
	{
		log("=========boss rush hurt ===============");
		this->targetHero->getHurt(800.0f, 2.0f, 0.0, 0.0);
		this->unschedule(schedule_selector(MonsterBossNum2::__bossRushJudge));
	}
}

void MonsterBossNum2::__bossRushMoveEnd(float dt){
	float stunTime = 5.0f;
	//dizzy
	this->scheduleOnce(schedule_selector(MonsterBossNum2::outBoss2SkillSequence), stunTime);
}

void MonsterBossNum2::outBoss2SkillSequence(float dt){
	this->unschedule(schedule_selector(MonsterBossNum2::__dangerousAreaJudge));
	//stand
	this->scheduleOnce(schedule_selector(Monster::skillFinish), 2.0f);
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
		bossOrNot = true;
		skillOrAttack = false;		
		_loadCSB("monster4/monster4.csb", 23);	
		setisDead(false);	
		setviewRange(700.0);
		setattackTime(2.0f);
		setattackRange(100.0);	
		setAttackValue(140.0f);
		setDefenceValue(33.0f);
		setHp(600.0f);
		setupperHp(600.0f);
		setSpeedRate(0.5);
		setcanAttack(true);
		setStun(NOTSTUNFOREVER);

		setContentSize(Size(80, 100));
		monsterLevel = 1;
		//attackrange+100 = move range
		carMonsterList = monsterList;
		m_monsterType = MonsterType::monsterBossNum3;
		createBloodBar(true);
		createName("Big Eye", 110);
		m_FSM = MonsterFSM::createWithMonster(this);
		bRet = true;
	} while (0);
	return bRet;
}

void MonsterBossNum3::intoBoss3SkillSequence(float dt){
	if (getisDead() == true)
	{
		return;
	}
	this->__bossRunOutOfGround(1.0f);
}

void MonsterBossNum3::outBoss3SkillSequence(float dt){
	this->scheduleOnce(schedule_selector(Monster::skillFinish), 10.0f);
}

void MonsterBossNum3::onDead(){
	notFallBoxList.clear();
	shadowList.clear();
	fallingBoxList.clear();
	boxList.clear();
	SimpleAudioEngine::getInstance()->playEffect(EFFECTS_25.c_str());
	this->m_armature->getAnimation()->stop();
	bloodBar->setVisible(false);
	nameLabel->setVisible(false);
	if (this->targetHero->getPositionX() < this->getPositionX())
	{
		m_armature->setScale(1.0f, 1.0f);
		this->m_armature->getAnimation()->play("dead", -1, 0);

	}
	else
	{
		m_armature->setScale(-1.0f, 1.0f);
		m_armature->getAnimation()->play("dead", -1, 0);
	}
	auto callFunc = CallFunc::create([=](){
		this->removeFromParentAndCleanup(true);
	});
	this->runAction(Sequence::create(DelayTime::create(2.0f), callFunc, NULL));
	
	auto box = TreasureBox::create(static_cast<ScenarioEnum>(this->monsterLevel - 1));
	box->setPosition(this->getPositionX(), this->getPositionY() - 40);
	this->getParent()->addChild(box);
}

void MonsterBossNum3::showTheCar(float dt){
	castMessage("avoid the cars!!!");
	carMonsterList.at(0)->setPosition(4200, 75);
	carMonsterList.at(1)->setPosition(4200, 185);
	carMonsterList.at(2)->setPosition(4200, 325);
	
	for (auto monster : carMonsterList)
	{
		this->getParent()->addChild(monster,0);
	}

	this->scheduleOnce(schedule_selector(MonsterBossNum3::__runTheCar), 2.0f);
}

void MonsterBossNum3::__runTheCar(float dt){
	if (getisDead() == true)
	{
		return;
	}
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
		runTime2 = 5.0f;
		runTime3 = 8.0f;
		break;
	case 1:
		//231
		runTime1 = 6.0f;
		runTime2 = 2.0f;
		runTime3 = 4.0f;
		break;
	case 2:
		//213
		runTime1 = 4.0f;
		runTime2 = 2.0f;
		runTime3 = 6.0f;
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
	this->carMonsterList.at(0)->runAction(Sequence::create(MoveBy::create(0.5f,Vec2(-30,0)),MoveBy::create(0.5f,Vec2(30,0)),EaseIn::create(MoveBy::create(6.0f, Vec2(-1400, 0)),4.0f),NULL));
}

void MonsterBossNum3::__runNumber2Car(float dt){
	this->carMonsterList.at(1)->runAction(Sequence::create(MoveBy::create(0.5f, Vec2(-30, 0)), MoveBy::create(0.5f, Vec2(30, 0)), EaseIn::create(MoveBy::create(6.0f, Vec2(-1400, 0)), 4.0f), NULL));
}

void MonsterBossNum3::__runNumber3Car(float dt){
	this->carMonsterList.at(2)->runAction(Sequence::create(MoveBy::create(0.5f, Vec2(-30, 0)), MoveBy::create(0.5f, Vec2(30, 0)), EaseIn::create(MoveBy::create(6.0f, Vec2(-1400, 0)), 4.0f), NULL));
}

void MonsterBossNum3::__removeTheCar(float dt){
	static int times;
	for (auto monster : carMonsterList)
	{
		this->getParent()->removeChild(monster);
	}
	if (times<2)
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
			targetHero->getHurt(130, 2.0f, 0, 0);
			this->unschedule(schedule_selector(MonsterBossNum3::__isCarCollide));
		}
	}
}

void MonsterBossNum3::__bossRunOutOfGround(float dt){
	if (getisDead()==true)
	{
		return;
	}
	setcanAttack(false);
	if (getPositionX()<=3800)
	{
		m_armature->setScale(-1.0f, 1.0f);
	}
	else
		m_armature->setScale(1.0f, 1.0f);
	m_armature->getAnimation()->play("stand");
	ccBezierConfig bezierCon;
	bezierCon.controlPoint_1 = Vec2(this->getPositionX(), this->getPositionY());
	bezierCon.controlPoint_2 = Vec2((this->getPositionX() + 3800) / 2, (((200) > (this->getPositionY())) ? (200) : (this->getPositionY())) + 300);
	bezierCon.endPosition = Vec2(3800, 200);
	BezierTo* bezierAction = BezierTo::create(2.0f, bezierCon);
	this->runAction(Sequence::create(bezierAction,DelayTime::create(1.0f), MoveBy::create(3.0f, Vec2(0, 1000)), NULL));
	this->scheduleOnce(schedule_selector(MonsterBossNum3::__skillDropBox), 2.0f);
}

void MonsterBossNum3::__skillDropBox(float dt){
	
	for (int i = 0; i < 4; i++)
	{
		auto box = Monster::create(Sprite::create("wolf.png"), MonsterType::num3BoxType);
		box->setboxTag(i);
		box->setPosition(2920+320 * (i + 1), 1000);
		this->boxList.pushBack(box);
		this->notFallBoxList.pushBack(box);
		this->getParent()->addChild(box,1);
		this->bloodBar->setVisible(true);
		auto shadow = Monster::create(Sprite::create("shadow.png"), MonsterType::block);
		shadowList.pushBack(shadow);

		//Rect rect = box->getBoundingBox();
		//auto s = Director::getInstance()->getWinSize();
		//auto draw = DrawNode::create();
		//box->addChild(draw, 10);
		//Vec2 points[] = { Vec2(0, 0), Vec2(rect.size.width, 0), Vec2(rect.size.width, rect.size.height), Vec2(0, rect.size.height) };
		////Vec2 points[] = { Vec2(rect.origin.x, rect.origin.y), Vec2(rect.origin.x + rect.size.width, rect.origin.y), Vec2(rect.origin.x + rect.size.width, rect.origin.y + rect.size.height), Vec2(rect.origin.x, rect.origin.y + rect.size.height) };
		//draw->drawPolygon(points, sizeof(points) / sizeof(points[0]), Color4F(1, 0, 0, 0.5), 4, Color4F(0, 0, 1, 1));

	}

	for (int i = 0; i < 4;i++)
	{
		isPlaceVacant[i] = 0;
	}
	this->schedule(schedule_selector(MonsterBossNum3::__isBoxNeedRemove));

	castMessage("avoid the boxes!!!");
	this->schedule(schedule_selector(MonsterBossNum3::__findAnyVacantPlace),8.0f);

}

void MonsterBossNum3::__isBoxNeedRemove(float dt){
	for (auto monster : boxList)
	{
		if (monster->getisDead() == true)
		{
			this->unschedule(schedule_selector(MonsterBossNum3::__isBoxNeedRemove));
			auto callFunc = CallFunc::create([=](){		
				monster->setPosition((monster->getboxTag() + 1) * 320 + 2920, 1000);
				monster->setHp(monster->getupperHp() + BOXADDBLOOD);
				monster->setupperHp(monster->getupperHp() + BOXADDBLOOD);
				monster->setisDead(false);
				monster->bloodBar->setVisible(true);
				monster->blood->setPercentage(100.0f);
				isPlaceVacant[monster->getboxTag()] = 0;
				notFallBoxList.pushBack(monster);
				this->targetHero->m_heroMonsterList.eraseObject(monster);
			});		
			this->schedule(schedule_selector(MonsterBossNum3::__isBoxNeedRemove),0.0,kRepeatForever,1.0f);
			monster->m_armature->getAnimation()->play("fade",-1,0);
			monster->runAction(Sequence::create(DelayTime::create(0.8f), callFunc, NULL));
		}
	}
}

void MonsterBossNum3::__dropBoxCollide(float dt){

	for (auto monster : fallingBoxList)
	{
		if (monster->getBoundingBox().intersectsRect(this->targetHero->getBoundingBox())&&this->targetHero->getisDead()==false)
		{
			isPlaceVacant[lastBoxNumber] = 0;
			this->getParent()->removeChild(shadowList.at(lastBoxNumber));
			this->targetHero->getHurt(150, 2.0f, 0.0f, 0.0f);
			this->unschedule(schedule_selector(MonsterBossNum3::__dropBoxCollide));
			monster->m_armature->getAnimation()->play("boom", -1, 0);
			auto callFunc = CallFunc::create([=](){
				monster->setPosition((monster->getboxTag() + 1) * 320+2920, 1000);
				monster->setHp(monster->getupperHp() + BOXADDBLOOD);
				monster->setupperHp(monster->getupperHp() + BOXADDBLOOD);
				monster->blood->setPercentage(100.0f); });
			this->runAction(Sequence::create(DelayTime::create(1.0f) , callFunc, NULL));
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
	fallingBoxList.clear();
	m_armature->setScale(1.0f, 1.0f);
	m_armature->getAnimation()->play("stand");

	auto callFunc = CallFunc::create([=](){
		this->monsterGetHurt(50, 0.0, 0,true);
		this->m_armature->setScale(1.0f, 1.0f);
		if (getisDead()==false)
		{
			this->m_armature->getAnimation()->play("dizzy");
		}	
	});
	setcanAttack(true);
	ccBezierConfig bezierCon;
	bezierCon.controlPoint_1 = Vec2(3800, 200);
	bezierCon.controlPoint_2 = Vec2(3700 , 400);
	bezierCon.endPosition = Vec2(3600,200);
	BezierTo* bezierAction = BezierTo::create(1.5f, bezierCon);
	this->runAction(Sequence::create(MoveBy::create(2.0f, Vec2(0, -1000)), bezierAction,callFunc, NULL));
	
	this->outBoss3SkillSequence(1.0f);
}

void MonsterBossNum3::__showTheShadow(int boxNumber){
	shadowList.at(boxNumber)->setScale(0.1f);
	shadowList.at(boxNumber)->setPosition(2920+320 * (lastBoxNumber + 1), 125);
	this->getParent()->addChild(shadowList.at(boxNumber),0);
	auto scaleby = ScaleBy::create(6.0f, 4.0f);
	shadowList.at(boxNumber)->runAction(scaleby);
}

void MonsterBossNum3::__findAnyVacantPlace(float dt){
	int boxNumber=0;
	static int boxQuantity;
	boxNumber = CCRANDOM_0_1() * 4 ;
	if (isScheduled(schedule_selector(MonsterBossNum3::__dropBoxCollide))==false)
	{
		this->schedule(schedule_selector(MonsterBossNum3::__dropBoxCollide));
	}
	auto callFunc = CallFunc::create([&](){
		fallingBoxList.eraseObject(boxList.at(lastBoxNumber));
		if (isPlaceVacant[lastBoxNumber]==1)
		{
			this->notFallBoxList.eraseObject(boxList.at(lastBoxNumber));
			this->targetHero->m_blockArea.pushBack(boxList.at(lastBoxNumber));			
			this->getParent()->removeChild(shadowList.at(lastBoxNumber));
		}		
	});
	if (boxQuantity<6)
	{
		if (isPlaceVacant[boxNumber] == 0)
		{
			isPlaceVacant[boxNumber] = 1;
			lastBoxNumber = boxNumber;
			boxList.at(boxNumber)->runAction(Sequence::create(DelayTime::create(6.0f), MoveBy::create(1.0f, Vec2(0, -835)), callFunc, NULL));
			fallingBoxList.pushBack(boxList.at(boxNumber));
			boxList.at(boxNumber)->m_armature->getAnimation()->play("stand");
			this->targetHero->m_heroMonsterList.pushBack(boxList.at(boxNumber));
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
					boxList.at(i)->runAction(Sequence::create(DelayTime::create(6.0f), MoveBy::create(1.0f, Vec2(0, -835)), callFunc, NULL));
					fallingBoxList.pushBack(boxList.at(i));
					boxList.at(i)->m_armature->getAnimation()->play("stand");
					this->targetHero->m_heroMonsterList.pushBack(boxList.at(i));
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

void MonsterBossNum3::isHeroCloseToBoss(float dt){
	if (Vec2(this->getPositionX() - targetHero->getPositionX(), this->getPositionY() - targetHero->getPositionY()).length()<=this->getviewRange())
	{
		this->scheduleOnce(schedule_selector(MonsterBossNum3::showTheCar), 5.0f);
		this->unschedule(schedule_selector(MonsterBossNum3::isHeroCloseToBoss));
	}
}