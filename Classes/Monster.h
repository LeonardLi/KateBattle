//
//  Monster.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__Monster__
#define __KateBattle__Monster__

#include <stdio.h>
#include "Entity.h"
#include "cocos2d.h"
class MonsterFSM;
class Hero;
class BulletBase;
class Monster : public Entity{
public:
	static Monster* create(cocos2d::Sprite* sprite,int Type);
	bool init(cocos2d::Sprite* sprite,int type);

	virtual void update(float delta);

	void monsterMoveToHero(float dt);
	void monsterRandomMove();
	void monsterStay(float dt);
	void attackafterMove(float dt);
	void attackSequence();
	void readyForAttack(float dt);
	void attack(float dt);
	void useSkillSequence();
	void useSkill(float dt);
	void isInViewRange(float dt);
	void attackWithBullet(int bulletType);
	void attackWithHand();
	void initBullet();
	void bulletLogicCheck(float dt);
	MonsterFSM* getFSM();
	BulletBase* getAnyUnUsedBullet();
protected:
	void onDead();
	void onHurt();
private:
	CC_SYNTHESIZE(int, m_Hp, Hp);
	CC_SYNTHESIZE(int, m_Attack, Attack);
	CC_SYNTHESIZE(double, m_attackRange, attackRange);
	CC_SYNTHESIZE(float, m_attackTime, attackTime);
	CC_SYNTHESIZE(float, m_viewRange, viewRange);
public:
	cocos2d::Vec2 heroLocation;
	cocos2d::Vector<BulletBase*> m_bulletList;
	Hero* targetHero;
	int m_monsterType;
	enum monsterType
	{
		normalType,
		shootType,
		monsterBossNum1,
	};
private:
	MonsterFSM* m_FSM;
	
};


class monsterBossNum1 :public Monster{
public:

private:


};

#endif /* defined(__KateBattle__Monster__) */
