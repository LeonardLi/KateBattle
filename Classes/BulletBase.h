#ifndef __KateBattle__BulletBase__
#define __KateBattle__BulletBase__

#include "Entity.h"
#include "cocos2d.h"
class Hero;
class BulletBase : public Entity{
public:
	BulletBase();
	~BulletBase();
	cocos2d::Vec2 getHeroPoint();
	bool isArrive();
	bool isUsed();
	void setUsed(bool isUsed);
	void lockTarget(Hero* hero);
	Hero* getTarget();
	void setBulletValue(float damage,float stuntime,float slowValue,float slowTime);
	virtual void onLockAim(Hero* hero) = 0;
public:
	float bulletDamage;
	float bulletStunTime;
	float bulletSlowDown;
	float bulletSlowDownTime;
private:
	CC_SYNTHESIZE(int, m_iAtkValue, iAtkValue);
	CC_SYNTHESIZE(int, m_speed, speed);
	Hero* m_targetHero;
	bool m_isArrive;
	bool m_isUsed;
};
#endif