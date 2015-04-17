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
using namespace cocostudio::timeline;

Entity::Entity():
mViewSprite(nullptr),
mViewNode(nullptr),
m_isDead(false),
m_Stun(NOTSTUN),
mTimeLine(nullptr)
{	
}

bool Entity::init(){
	if (!Node::init())
	{	
		return false;
	}

	//load view from csbfile

	this->setAnchorPoint(Vec2(0.5, 0.5));
	return true;
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
	mViewSprite->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(mViewSprite);

	this->setAnchorPoint(Vec2(0.5,0.5));
	Size size = mViewSprite->getContentSize();
	mViewSprite->setPosition(Point(size.width*0.5f, size.height*0.5f));
	
	this->setContentSize(size);
}

void Entity::_loadCSB(std::string csbfile){
	mViewNode = static_cast<Node*>(CSLoader::createNode(csbfile));
	mTimeLine = CSLoader::createTimeline(csbfile);
	
	this->setAnchorPoint(Vec2(0.5,0.5));
	this->setContentSize(Size(70,90));
	
	this->addChild(mViewNode);

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



void Entity::hurtMe(float iHurtValue){
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