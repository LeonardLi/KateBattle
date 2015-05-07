//
//  LoadingScene.cpp
//  KateBattle
//
//  Created by Leonard on 15/5/5.
//
//

#include "LoadingScene.h"
#include "cocos2d.h"
#include "VisibleRect.h"
#include "cocostudio/CocoStudio.h"

using namespace cocostudio::timeline;
USING_NS_CC;
LoadingScene::LoadingScene(){

}

LoadingScene::~LoadingScene(){
}

Scene* LoadingScene::createScene(){
    Scene* scene = Scene::create();
    LoadingScene* load = LoadingScene::create();
    scene->addChild(load);
    return scene;
}

bool LoadingScene::init(){
    if (!Layer::init()) {
        return false;
    }

	Node* rootNode = CSLoader::createNode("loa/loa.csb");
	ActionTimeline* timeline = CSLoader::createTimeline("loa/loa.csb");
	timeline->gotoFrameAndPlay(0, 30, true);
	rootNode->runAction(timeline);

	this->addChild(rootNode);
   /* Sprite* loadingBackgournd = Sprite::create("loadingbackground.png");
    loadingBackgournd->setPosition(VisibleRect::center());
    this->addChild(loadingBackgournd);
    
    Sprite* loadingProgressbar = Sprite::create("loadingprogressbar.png");
    ProgressTimer *progress = ProgressTimer::create(loadingProgressbar);
    progress->setPosition(Vec2(640.0f, 360.0f));
    progress->setType(ProgressTimer::Type::BAR);

    progress->setMidpoint(Vec2(0.0f, 0.0f));
    progress->setBarChangeRate(Vec2(1.0f, 0.0f));
    progress->setPercentage(100.0f);
    this->addChild(progress);
    ProgressTo *to = ProgressTo::create(5.0f, 100.0f);
    ActionInstant *jumptoGame = CallFunc::create(this, callfunc_selector(LoadingScene::__jumpToGame));
    Sequence *Sequence = Sequence::create(to,  jumptoGame, NULL);
    progress->runAction(Sequence);
	*/
    return true;
}

void LoadingScene::__jumpToGame(){
    
}


