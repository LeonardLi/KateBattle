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

	}
	else{
		CC_SAFE_DELETE(instance);
	}

	return instance;
}

void Kernal::startGame(){
	auto firstScene = GameScene::createScene();

	Director::getInstance()->runWithScene(firstScene);
	
}


bool Kernal::_initFromFile(){

	log("init from file begin");

	return true;
}