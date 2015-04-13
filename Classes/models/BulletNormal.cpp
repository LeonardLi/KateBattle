#include "BulletNormal.h"
#include "Hero.h"
USING_NS_CC;
#define BULLETDEFAULTSPEED 100.0
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
		Sprite* sprite = Sprite::create("CloseNormal.png");
		CC_BREAK_IF(!sprite);
		CC_BREAK_IF(!init(sprite));
		bRet = true;
	} while (0);
	return bRet;
}

void BulletNormal::onLockAim(Hero* hero){
	m_isArrive = false;
	Point aimWorldPos = hero->getParent()->convertToWorldSpace(hero->getPosition());
	Point dstPos = this->getParent()->convertToNodeSpace(aimWorldPos);

	float distance = dstPos.length();
	
	/*float x = heroLocation.x;
	float y = heroLocation.y;
	float x1 = this->getPositionX();
	float y1 = this->getPositionY();

	float time = sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1)) / SKILLRUSHSPEED;
	this->runAction(MoveTo::create(time, heroLocation));*/

	auto moveTo = MoveTo::create(distance / BULLETDEFAULTSPEED, dstPos);
	auto callFunc = CallFunc::create([&](){
		moveEnd();
	});
	auto actions = Sequence::create(moveTo, callFunc, NULL);
	this->runAction(actions);
}

void BulletNormal::moveEnd(){
	m_isArrive = true;
}