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
	//����ʱ��Ϊ
}

void Entity::onHurt()
{
	//������ʱ��Ϊ
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
	//����Ѫ��
	int iCurHp = getiHp();
	int iAfterHp = iCurHp - iHurtValue; 

	onHurt(iHurtValue);

	if(iAfterHp>0)
	{
	setHp(iAfterHp);
	}
	//����
	else
	{
	m_isDead=true;
	onDead();
	}
	*/
}