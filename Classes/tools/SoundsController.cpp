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
	this->setBackgroundMusicVolume(volum);
	this->setEffectsVolume(volum);
	m_EffectMusicVolum = m_BackMusicVolum = volum;
}

void SoundsController::stopBackgroundMusic()//关闭背景音乐,音乐从当前音乐大小逐次减小
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background.mp3");
	//CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SoundsController::Update), this, 0.1, false);
	//CCDirector::sharedDirector()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&SoundsController::_setBackVolumLogic), this, 1, false);
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SoundsController::_setBackVolumLogic), this, 1, false);
	//this->schedule(schedule_selector(SoundsController::_setBackVolumLogic));
	m_BackMusicVolum = this->getBackgroundMusicVolume();
}


void SoundsController::stopEffect()//关闭音效音乐,音效从当前音乐大小逐次减小
{
	SimpleAudioEngine::sharedEngine()->playEffect("background.mp3");
		log("effectMusic");
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(SoundsController::_setEffectVolumLogic), this, 1, false);
	m_EffectMusicVolum = this->getEffectsVolume();
}

void SoundsController::_setBackVolumLogic(float dt)
{
	log("***********************************************");
	log("volum:%f",m_BackMusicVolum);
	log("***********************************************");
	m_BackMusicVolum -= 0.1;
	if (m_BackMusicVolum > 0)
	{
		this->setBackgroundMusicVolume(m_BackMusicVolum);
	}
	else
	{
		//CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
		//CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(SoundsController::_setBackVolumLogic), this);
		//CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(SEL_SCHEDULE(&SoundsController::_setBackVolumLogic), this);
		//this->unschedule(schedule_selector(SoundsController::_setBackVolumLogic));
		this->unschedule(schedule_selector(SoundsController::_setBackVolumLogic));
		SimpleAudioEngine::stopBackgroundMusic(true);
	}
}
void SoundsController::_setEffectVolumLogic(float dt)
{
	log("***********************************************");
	log("volum:%f", m_EffectMusicVolum);
	log("***********************************************");
	m_EffectMusicVolum -= 0.1;
	if (m_EffectMusicVolum > 0)
	{
		this->setEffectsVolume(m_EffectMusicVolum);
	}
	else
	{
		this->unschedule(schedule_selector(SoundsController::_setEffectVolumLogic));
		SimpleAudioEngine::stopAllEffects();
	}
}
