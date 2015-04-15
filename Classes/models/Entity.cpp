//
//  Entity.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "Entity.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

Entity::Entity()
{
	this->mViewSprite = nullptr;
	m_isDead = false;
	this->setAnchorPoint(Vec2(0.5, 0.5));
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
	mViewSprite->setPosition(Point(size.width*0.5f, size.height*0.5f));
	this->setContentSize(size);
}

void Entity::bindSprite(std::string csbfile){
	mViewSprite = static_cast<Sprite*>(CSLoader::createNode(csbfile));
	this->addChild(mViewSprite);
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