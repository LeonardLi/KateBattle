//
//  Kernal.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/19.
//
//

#include "Kernal.h"
#include "JsonReader.h"
#include "GameScene.h"
#include "MenuScene.h"
#include "cocos2d.h"

USING_NS_CC;


Kernal::Kernal(){
}

Kernal::~Kernal(){

}

Kernal* Kernal::create(){
	Kernal* instance = new Kernal();
	if (instance && instance->_initFromFile())
	{
		instance->autorelease();
	}
	else{
		CC_SAFE_DELETE(instance);
	}

	return instance;
}

void Kernal::startGame(){
	auto firstScene = MenuScene::createScene();

	Director::getInstance()->runWithScene(firstScene);
	
}


bool Kernal::_initFromFile(){

	log("========== init from file ===========");

	return true;
}