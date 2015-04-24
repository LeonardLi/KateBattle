//
//  SoundsController.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/19.
//
//
#include "SoundsController.h"
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
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volum);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volum);
	m_EffectMusicVolum = m_BackMusicVolum = volum;
}

void SoundsController::stopBackgroundMusic()//关闭背景音乐,音乐从当前音乐大小逐次减小
{
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SoundsController::_setBackVolumLogic), this, 1, false);
	m_BackMusicVolum = SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume();
}

void SoundsController::stopEffect()//关闭音效音乐,音效从当前音乐大小逐次减小
{
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SoundsController::_setEffectVolumLogic), this, 1, false);
	m_EffectMusicVolum = SimpleAudioEngine::sharedEngine()->getEffectsVolume();
}

void SoundsController::_setBackVolumLogic(float dt)
{
	m_BackMusicVolum -= 0.15;
	if (m_BackMusicVolum > 0)
	{
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(m_BackMusicVolum);
	}
	else
	{
		this->unschedule(schedule_selector(SoundsController::_setBackVolumLogic));
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
	}
}

void SoundsController::_setEffectVolumLogic(float dt)
{
	m_EffectMusicVolum -= 0.15;
	if (m_EffectMusicVolum > 0)
	{
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(m_EffectMusicVolum);
	}
	else
	{
		this->unschedule(schedule_selector(SoundsController::_setEffectVolumLogic));
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
	}
}
