#include "BulletManager.h"
#include "BulletNormal.h"
USING_NS_CC;
BulletManager::BulletManager(){
}
BulletManager::~BulletManager(){
}

BulletManager* BulletManager::create(){
	BulletManager* bulletMgr = new BulletManager();
	if (bulletMgr&&bulletMgr->init())
	{
		bulletMgr->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bulletMgr);
	}
	return bulletMgr;
}

bool BulletManager::init(){
	
	createBullets();
	this->schedule(schedule_selector(BulletManager::bulletLogicCheck));
	return true;
}

void BulletManager::createBullets(){
	BulletBase* bullet = NULL;
	for (int i = 0; i < 3; i++)
	{
		bullet = BulletNormal::create();
		bullet->setUsed(false);
		m_bulletList.pushBack(bullet);
		this->addChild(bullet);
	}
}

void BulletManager::bulletLogicCheck(float dt){
	for (auto bullet:m_bulletList)
	{
		if (bullet->isUsed())
		{
			auto aim = bullet->getTarget();
			if (aim!=NULL)
			{
				if (bullet->isArrive())
				{
					log("bullet Arrive!---------- - ");
					bullet->setUsed(false);
				}
			}
		}
	}
}

BulletBase* BulletManager::getAnyUnUsedBullet(){
	for (auto bullet:m_bulletList)
	{
		if (bullet->isUsed()==false)
		{
			bullet->setUsed(true);
			return bullet;
		}	
	}
	return NULL;
}