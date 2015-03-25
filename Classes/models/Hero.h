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
class Hero : public Entity{
public:
	Hero();
	static Hero* create(cocos2d::Sprite* sprite);
	virtual bool init(cocos2d::Sprite* sprite);

	static Hero* initFromJson();
private:

public:
private:
	CC_SYNTHESIZE(int, m_hp, Hp);
};


#endif /* defined(__KateBattle__Hero__) */
