#ifndef __KateBattle__BulletManager__
#define __KateBattle__BulletManager__

#include "cocos2d.h"

class BulletBase;
class BulletManager : public cocos2d::Node{
public:
	BulletManager();
	~BulletManager();
	static BulletManager* create();
	bool init();
	BulletBase* getAnyUnUsedBullet();

private:
	cocos2d::Vector<BulletBase*> m_bulletList;
	void createBullets();
	void bulletLogicCheck(float dt);
};

#endif