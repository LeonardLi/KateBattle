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
#include "GameScene.h"
#include "SoundsController.h"

using namespace cocostudio::timeline;
USING_NS_CC;
LoadingScene::LoadingScene(){

}

LoadingScene::~LoadingScene(){
}

LoadingScene* LoadingScene::create(ScenarioEnum scenario, SubScenarioEnum subscenario){
	auto scene = new (std::nothrow)LoadingScene;
	if (scene && scene->init(scenario, subscenario))
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);
	return scene;
}
Scene* LoadingScene::createScene(ScenarioEnum scenario, SubScenarioEnum subscenario){
    Scene* scene = Scene::create();
	LoadingScene* load = LoadingScene::create(scenario, subscenario);
    scene->addChild(load);
    return scene;
}

bool LoadingScene::init(ScenarioEnum scenario, SubScenarioEnum subscenario){
    if (!Layer::init()) {
        return false;
    }
	m_scenario = scenario;
	m_subscenario = subscenario;

	Node* rootNode = CSLoader::createNode("loa/loa.csb");
	ActionTimeline* timeline = CSLoader::createTimeline("loa/loa.csb");
	timeline->gotoFrameAndPlay(0, 30, true);
	rootNode->runAction(timeline);

	this->addChild(rootNode);
	
	auto jump = CallFunc::create([=](){
		Scene* scene = GameScene::createScene(m_scenario, m_subscenario);
		auto transition = TransitionFadeBL::create(3.8f, scene);
		Director::getInstance()->replaceScene(transition);
		SoundsController::getInstance()->stopBackgroundMusic(m_scenario);
	});
	this->runAction(Sequence::create(DelayTime::create(3.8f), jump, NULL));
    return true;
}



