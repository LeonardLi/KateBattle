//
//  Entity.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "Entity.h"
USING_NS_CC;

Entity::Entity(){

}

void Entity::bindSprite(Sprite* sprite)
{
	if (this->mViewSprite!= NULL)
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
}