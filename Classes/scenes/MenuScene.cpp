//
//  MenuScene.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "MenuScene.h"
#include "cocos2d.h"
USING_NS_CC;


Scene* MenuScene::createScene(){
	Scene* scene = Scene::create();

	Layer* layer = MenuScene::create();

	scene->addChild(layer);

	return scene;
}

bool MenuScene::init(){
	if (!Layer::init())
	{
		return false;
	}
	
	return true;

}

