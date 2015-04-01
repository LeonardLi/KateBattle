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

class Entity:public cocos2d::Node
{
public:
    Entity();
	//�󶨾���
	void bindSprite(cocos2d::Sprite* sprite);
	//��ȡ�󶨾���
	cocos2d::Sprite* getSprite();
	//�Ƿ�����
	bool isDead();
	//�ܵ�����ʱ�߼�����
	void hurtMe(int iHurtValue);

protected:
	//����ʱ��Ϊ����
	virtual void onDead() = 0;
	//�ܵ�����ʱ��Ϊ����
	virtual void onHurt() = 0;
private: 

public:
protected:
    cocos2d::Sprite* mViewSprite;
	bool m_isDead;

private:

    
};

#endif /* defined(__KateBattle__Entity__) */
