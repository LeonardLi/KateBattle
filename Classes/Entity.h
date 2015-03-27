//
//  Entity.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__Entity__
#define __KateBattle__Entity__

#include <stdio.h>
#include <cocos2d.h>

class Entity:public cocos2d::Node{
public:
    Entity();
	void bindSprite(cocos2d::Sprite* sprite);
	cocos2d::Sprite* getSprite();
	bool isDead();
    //virtual bool injectSprite(cocos2d::Sprite* injectSprite)=0;
protected:
	void onDead();
private:

public:
protected:
    cocos2d::Sprite* mViewSprite;
	bool m_isDead;

private:
    
    
};

#endif /* defined(__KateBattle__Entity__) */
