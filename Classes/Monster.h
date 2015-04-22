//
//  Monster.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__Monster__
#define __KateBattle__Monster__

#include "Entity.h"
#include "cocos2d.h"
class MonsterFSM;
class Hero;
class BulletBase;
enum class JoystickEnum;
enum class MonsterType
{
	normalType,
	shootType,
	monsterBossNum1,
	num1ShootType,
	block,
	monsterBossNum3,
	num3CarType,
};


class Monster : public Entity{
public:
	static Monster* create(cocos2d::Sprite* sprite, MonsterType Type);
	bool init(cocos2d::Sprite* sprite,MonsterType type);

	virtual void update(float delta);
	
	void monsterGetHurt(int iValue, int time);
	MonsterFSM* getFSM();
	void attackSequence();
	void useSkillSequence();
	void skillRush(float dt);
	void isCollide(float dt);
	void skillFinish(float dt);
protected:
	void onDead();
	void onHurt();
private:
	//move
	void __monsterMoveToHero(float dt);
	void __monsterRandomMove();

	//attack
	void __readyForAttack(float dt);
	void __attack();
	
	void __attackWithHand();
	void __attackafterMove();
	void __finishAttack(float dt);

	//skill
	void __readyForUseSkill(float dt);
	void __skill();
	
	void __useSkill(float dt);

	//remote attack
	void __initBullet(int bulletType);
	void __attackWithBullet();
	void __bulletLogicCheck(float dt);
	BulletBase* __getAnyUnUsedBullet();

	//judge state
	
	void __intoAttackSequence(float dt);
	void __intoSkillSequence(float dt);

	//distance judge
	void __isInViewRange(float dt);


	
	void __moveCloseToHero(cocos2d::Vec2 distance);
	

	//post message
	void __postBossAttackMessage(float dt);
	void __postBossSkillMessage(float dt);


public:
	cocos2d::Vec2 heroLocation;
	cocos2d::Vector<BulletBase*> m_bulletList;
	Hero* targetHero;
	
	Monster* m_boxes;
	MonsterType m_monsterType;
	MonsterFSM* m_FSM;
	bool skillOrAttack;

private:
	
	CC_SYNTHESIZE(int, m_Hp, Hp);
	CC_SYNTHESIZE(int, m_Attack, Attack);
	CC_SYNTHESIZE(double, m_attackRange, attackRange);
	CC_SYNTHESIZE(float, m_attackTime, attackTime);
	CC_SYNTHESIZE(float, m_viewRange, viewRange);
	
};


class MonsterBossNum1 :public Monster{

public:
	static MonsterBossNum1* create(cocos2d::Sprite* sprite, cocos2d::Vector<Monster*> monsterList);
	bool init(cocos2d::Sprite* sprite, cocos2d::Vector<Monster*> monsterList);
	cocos2d::Vector<Monster*> shootMonsterList;
	void skillRushBox(float dt);
	
private:

public:
	Monster* box;
};

class MonsterBossNum3 :public Monster{

public:
	static MonsterBossNum3* create(cocos2d::Sprite* sprite, cocos2d::Vector<Monster*> monsterList);
	bool init(cocos2d::Sprite* sprite, cocos2d::Vector<Monster*> monsterList);
	cocos2d::Vector<Monster*> carMonsterList;
	void showTheCar(float dt);
	
	void bossRunOutOfGround(float dt);

private:
	void __runTheCar(float dt);
	void __runNumber1Car(float dt);
	void __runNumber2Car(float dt);
	void __runNumber3Car(float dt);
	void __removeTheCar(float dt);
	void __isCarCollide(float dt); 
	void __skillDropBox(float dt);
	void __dropBoxCollide(float dt);
	void __findAnyVacantPlace(float dt);
	void __dropBoxEnd(float dt);
	void __showTheShadow(int locationNum);

private:
	int isPlaceVacant[4];
	cocos2d::Vector<Monster*> boxList;
	cocos2d::Vector<Monster*> notFallBoxList;
	cocos2d::Vector<Monster*> shadowList;
	int lastBoxNumber;
};




#endif /* defined(__KateBattle__Monster__) */
