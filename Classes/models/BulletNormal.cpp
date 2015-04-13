#include "BulletNormal.h"
#include "Hero.h"
USING_NS_CC;
#define BULLETDEFAULTSPEED 50.0
BulletNormal::BulletNormal(){
	m_speed = 2;
}
BulletNormal::~BulletNormal(){
}

BulletNormal* BulletNormal::create(Sprite* sprite){
	BulletNormal* bulletNormal = new BulletNormal();
	if (bulletNormal&&bulletNormal->init(sprite))
	{
		bulletNormal->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bulletNormal);
	}
	return bulletNormal;
}

bool BulletNormal::init(Sprite* sprite){
	bindSprite(sprite);
	return true;
}

bool BulletNormal::init(){
	bool bRet = false;
	do
	{
		bRet = true;
	} while (0);
	return bRet;
}

void BulletNormal::onLockAim(Hero* hero){
	m_isArrive = false;
	normalShoot(hero);
}

void BulletNormal::moveEnd(){
	m_isArrive = true;
}

void BulletNormal::normalShoot(Hero* hero){
	Point aimWorldPos = hero->getParent()->convertToWorldSpace(hero->getPosition());
	Point dstPos = Vec2(aimWorldPos.x - this->getPositionX(), aimWorldPos.y - this->getPositionY());

	cocos2d::Size size = Director::getInstance()->getVisibleSize();
	Vec2 screenLenght = Vec2(size.width, size.height);
	float distance = screenLenght.length();
	float moveDistance = dstPos.length();

	float thisX = this->getPositionX();
	float thisY = this->getPositionY();

	Vec2 destinationPos;
	if (this->getPosition() != aimWorldPos)
	{
		float destinationPosX = thisX + (aimWorldPos.x - thisX)*distance / moveDistance;
		float destinationPosY = thisY + (aimWorldPos.y - thisY)*distance / moveDistance;
		destinationPos = Vec2(destinationPosX, destinationPosY);
	}
	auto moveTo = MoveTo::create(distance / BULLETDEFAULTSPEED, destinationPos);
	auto callFunc = CallFunc::create([&](){
		moveEnd();
	});
	auto actions = Sequence::create(moveTo, callFunc, NULL);
	this->runAction(actions);
}