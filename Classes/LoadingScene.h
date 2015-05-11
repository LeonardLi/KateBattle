//
//  LoadingScene.h
//  KateBattle
//
//  Created by Leonard on 15/5/5.
//
//

#pragma once
#include "cocos2d.h"


enum class ScenarioEnum;
enum class SubScenarioEnum;
class LoadingScene : public cocos2d::Layer{
public:
	static LoadingScene* create(ScenarioEnum, SubScenarioEnum);
    LoadingScene();
    ~LoadingScene();
	static cocos2d::Scene* createScene(ScenarioEnum, SubScenarioEnum);
    
private:
	virtual bool init(ScenarioEnum, SubScenarioEnum);
	ScenarioEnum m_scenario;
	SubScenarioEnum m_subscenario;
};
