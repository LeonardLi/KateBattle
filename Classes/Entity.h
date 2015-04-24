//
//  Entity.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__Entity__
#define __KateBattle__Entity__
#include <cocos2d.h>
#include "cocostudio/CocoStudio.h"
#define STUN 0
#define NOTSTUN 1
#define NOTSTUNFOREVER 2

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
	void hurtMe(float iHurtValue);

protected:
	//死亡时行为函数
	void onDead();
	//受到攻击时行为函数
	void onHurt();

	void _loadCSB(std::string);
	virtual bool init();

private: 

public:
protected:
    cocos2d::Sprite* mViewSprite;
	cocos2d::Node* mViewNode;
	cocostudio::timeline::ActionTimeline* mTimeLine;
	bool m_isDead;
	//int m_Stun;//3types
private:
	CC_SYNTHESIZE(int, m_Stun, Stun);
    
};

class BackupEntity :public cocos2d::Node{
public:

protected:
	bool loadfromCSB();
};
#endif /* defined(__KateBattle__Entity__) */
