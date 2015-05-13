//
//  AboutLayer.h
//  KateBattle
//
//  Created by Leonard on 15/5/13.
//
//
#include "cocos2d.h"

class AboutLayer : public cocos2d::Layer{
public:
    AboutLayer();
    ~AboutLayer();
    static AboutLayer* create();
private:
    bool init();
    void __loadCSB();
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    void onBackClicked(cocos2d::Ref*);
    
};