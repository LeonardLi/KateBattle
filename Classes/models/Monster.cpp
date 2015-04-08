//
//  Monster.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "Monster.h"

Monster* Monster::create(cocos2d::Sprite* sprite){
	Monster* monster = new Monster();
	if (monster&&monster->init(sprite))
	{
		monster->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(monster);
	}
	return monster;
}

bool Monster::init(cocos2d::Sprite* sprite){
	bool bRet = false;
	
	do
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);
		bRet = true;
	} while (0);

	return bRet;
}


void Monster::onDead(){
	CCASSERT(false," ");
	
}

void Monster::onHurt(){
	CCASSERT(false, " ");
}