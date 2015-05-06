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

	return true;
}

void LoadingScene::__jumpToGame(){
    
}


