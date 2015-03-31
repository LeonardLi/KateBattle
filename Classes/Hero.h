//
//  Hero.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__Hero__
#define __KateBattle__Hero__
#include "Entity.h"
#include "ControllerMoveBase.h"
class Hero : public Entity{
public:
	Hero();
	static Hero* create(cocos2d::Sprite* sprite);
	virtual bool init(cocos2d::Sprite* sprite);
	static Hero* initFromJson();
private:
	CC_SYNTHESIZE(int, m_hp, Hp);
public:
	ControllerMoveBase* m_moveController;
private:
	
};


#endif /* defined(__KateBattle__Hero__) */
