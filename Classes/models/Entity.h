//
//  Entity.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__Entity__
#define __KateBattle__Entity__

#include <stdio.h>
#include <cocos2d.h>

class Entity{
public:
    Entity();
    virtual bool injectSprite(cocos2d::Sprite* injectSprite);
protected:
private:

public:
protected:
    cocos2d::Sprite mViewSprite;
private:
    
    
};

#endif /* defined(__KateBattle__Entity__) */
