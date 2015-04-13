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
class BulletManager;
class Hero;
class Monster : public Entity{
public:
	static Monster* create(cocos2d::Sprite* sprite);
	bool init(cocos2d::Sprite* sprite);

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
	MonsterFSM* getFSM();

protected:
	void onDead();
	void onHurt();
private:
	CC_SYNTHESIZE(int, m_monsterType, monsterType);
	CC_SYNTHESIZE(int, m_Hp, Hp);
	CC_SYNTHESIZE(int, m_Attack, Attack);
	CC_SYNTHESIZE(double, m_attackRange, attackRange);
	CC_SYNTHESIZE(float, m_attackTime, attackTime);
	CC_SYNTHESIZE(float, m_viewRange, viewRange);
public:
	cocos2d::Vec2 heroLocation;
	Hero* targetHero;
private:
	MonsterFSM* m_FSM;
	BulletManager* bulletMgr;
	
};

#endif /* defined(__KateBattle__Monster__) */
