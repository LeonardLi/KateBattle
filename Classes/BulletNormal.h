#ifndef __KateBattle__BulletNormal__
#define __KateBattle__BulletNormal__

#include "cocos2d.h"
#include "BulletBase.h"
class Hero;
class BulletNormal : public BulletBase{
public:
	BulletNormal();
	~BulletNormal();
	CREATE_FUNC(BulletNormal);
	virtual bool init();

	static BulletNormal* create(cocos2d::Sprite* sprite);
	bool init(cocos2d::Sprite* sprite);
protected:
	void onLockAim(Hero* hero);
private:
	void moveEnd();


};

#endif