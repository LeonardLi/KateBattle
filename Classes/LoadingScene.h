//
//  LoadingScene.h
//  KateBattle
//
//  Created by Leonard on 15/5/5.
//
//

#pragma once
#include "cocos2d.h"

class LoadingScene : public cocos2d::Layer{
public:
    CREATE_FUNC(LoadingScene);
    LoadingScene();
    ~LoadingScene();
    static cocos2d::Scene* createScene();
    
private:
    virtual bool init();
    void __jumpToGame();
    
};
