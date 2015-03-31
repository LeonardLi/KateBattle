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

class Entity:public cocos2d::Node
{
public:
    Entity();
	//绑定精灵
	void bindSprite(cocos2d::Sprite* sprite);
	//获取绑定精灵
	cocos2d::Sprite* getSprite();
	//是否死亡
	bool isDead();
	//受到攻击时逻辑函数
	void hurtMe(int iHurtValue);
    //virtual bool injectSprite(cocos2d::Sprite* injectSprite)=0;
protected:
	//死亡时行为函数
	virtual void onDead();
	//受到攻击时行为函数
	virtual void onHurt();
private:

public:
protected:
    cocos2d::Sprite* mViewSprite;
	bool m_isDead;

private:

    
};

#endif /* defined(__KateBattle__Entity__) */
