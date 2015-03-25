//
//  Hero.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "Hero.h"
USING_NS_CC;
Hero::Hero(){

}

Hero* Hero::create(Sprite* sprite){
	Hero* hero = new Hero();
	if (hero&&hero->init(sprite)){
		hero->autorelease();
	}
	else{
		CC_SAFE_DELETE(hero);
	}

	return hero;
}


bool Hero::init(Sprite* sprite){
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);
		bRet = true;
	} while (0);

	return bRet;
}