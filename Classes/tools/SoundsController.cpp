//
//  SoundsController.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/19.
//
//
#include "SoundsController.h"
#include "GameScene.h"
#include "SoundsDef.h"
USING_NS_CC;
using namespace CocosDenshion;

char* SoundsController::getMusicFileName(std::string FileName){

	std::string suffix = NULL;
	std::string music = FileName;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	suffix = ".mp3";
#else  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	suffix = ".mp3";
#endif
	music = music + suffix;
		return  const_cast<char*>(music.c_str());
}

char* SoundsController::getEffectsFileName(std::string FileName){

	std::string suffix = NULL;
	std::string effect = FileName;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	suffix = ".wav";
#else  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	suffix = ".ogg";
#endif
	effect = effect + suffix;
	return const_cast<char*>(effect.c_str());
}

SoundsController* SoundsController::getInstance()
{
	static SoundsController s_SharedEngine;
	return &s_SharedEngine;
}

void SoundsController::setMusicVolum(float volum) //调整所有音乐的音量，包括音乐以及音效
{
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volum);
	SimpleAudioEngine::getInstance()->setEffectsVolume(volum);
	m_EffectMusicVolum = m_BackMusicVolum = volum;
}

void SoundsController::stopBackgroundMusic()//关闭背景音乐,音乐从当前音乐大小逐次减小
{
	Director::getInstance()->getScheduler()->Scheduler::schedule(schedule_selector(SoundsController::_setBackVolumLogic), this, 1, false);
	m_BackMusicVolum = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
}

void SoundsController::stopBackgroundMusic(ScenarioEnum scen)
{
	Director::getInstance()->getScheduler()->Scheduler::schedule(schedule_selector(SoundsController::_setBackSceneVolumLogic), this, 1, false);
	m_BackMusicVolum = SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
	scenario = scen;
}
void SoundsController::stopEffect()//关闭音效音乐,音效从当前音乐大小逐次减小
{
	Director::getInstance()->getScheduler()->Scheduler::schedule(schedule_selector(SoundsController::_setEffectVolumLogic), this, 1, false);
	m_EffectMusicVolum = SimpleAudioEngine::getInstance()->getEffectsVolume();
}

void SoundsController::_setBackVolumLogic(float dt)
{
	m_BackMusicVolum -= 0.25;
	if (m_BackMusicVolum > 0)
	{
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(m_BackMusicVolum);
	}
	else
	{
		this->unschedule(schedule_selector(SoundsController::_setBackVolumLogic));
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
}

void SoundsController::_setBackSceneVolumLogic(float dt)
{
	m_BackMusicVolum -= 0.25;
	if (m_BackMusicVolum > 0)
	{
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(m_BackMusicVolum);
	}
	else
	{
		this->unschedule(schedule_selector(SoundsController::_setBackSceneVolumLogic));
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
		switch (scenario)
		{
		case ScenarioEnum::Port:
			SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_3.c_str());
			break;
		case ScenarioEnum::Market:
			SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_2.c_str());
			break;
		case ScenarioEnum::Sewer:
			SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_4.c_str());
			break;
		default:
			break;
		}
	}
}

void SoundsController::_setEffectVolumLogic(float dt)
{
	m_EffectMusicVolum -= 0.15;
	if (m_EffectMusicVolum > 0)
	{
		SimpleAudioEngine::getInstance()->setEffectsVolume(m_EffectMusicVolum);
	}
	else
	{
		this->unschedule(schedule_selector(SoundsController::_setEffectVolumLogic));
		SimpleAudioEngine::getInstance()->stopAllEffects();
	}
}
