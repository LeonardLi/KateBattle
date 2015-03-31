//
//  Entity.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "Entity.h"
USING_NS_CC;

Entity::Entity()
{
	this->mViewSprite = nullptr;
}

Sprite* Entity::getSprite()
{
	return mViewSprite;

}

void Entity::bindSprite(Sprite* sprite)
{
	if (this->mViewSprite != nullptr)
	mViewSprite->removeFromParentAndCleanup(true);

	this->mViewSprite = sprite;
	this->addChild(mViewSprite);

	Size size = mViewSprite->getContentSize();
	this->setContentSize(size);

}

bool Entity::isDead()
{
	return m_isDead;
}

void Entity::onDead()
{
	//死亡时行为
}

void Entity::onHurt()
{
	//被攻击时行为
}



void Entity::hurtMe(int iHurtValue){
	if (m_isDead)
	{
		return;
	}

	/*
	if(iHurtValue<=getDefense())
	{
	iHurtValue=1;
	}
	//设置血量
	int iCurHp = getiHp();
	int iAfterHp = iCurHp - iHurtValue; 

	onHurt(iHurtValue);

	if(iAfterHp>0)
	{
	setHp(iAfterHp);
	}
	//死亡
	else
	{
	m_isDead=true;
	onDead();
	}
	*/
}