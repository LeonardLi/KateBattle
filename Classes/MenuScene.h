//
//  MenuScene.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__MenuScene__
#define __KateBattle__MenuScene__

#include <cocos2d.h>

class MenuScene : public cocos2d::Layer{
public:
	CREATE_FUNC(MenuScene);
	static cocos2d::Scene* createScene();

private:
	virtual bool init();
	void menuCloseCallback(Ref* pSender);
};

#endif /* defined(__KateBattle__MenuScene__) */
