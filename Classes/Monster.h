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
class MonsterFSM;
class Monster : public Entity{
public:
	static Monster* create(cocos2d::Sprite* sprite);
	bool init(cocos2d::Sprite* sprite);

	void attack();
	void useSkill();
	MonsterFSM* getFSM();

protected:
	virtual void onDead();
	virtual void onHurt();
private:
	CC_SYNTHESIZE(int, m_monsterType, monsterType);
	CC_SYNTHESIZE(int, m_Hp, Hp);
	CC_SYNTHESIZE(int, m_Attack, Attack);

	MonsterFSM* m_FSM;
};

#endif /* defined(__KateBattle__Monster__) */
