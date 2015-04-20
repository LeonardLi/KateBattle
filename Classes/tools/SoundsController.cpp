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

void SoundsController::setMusicVolum(float volum) //调整所有音乐的音量，包括音乐以及音效
{
	this->setBackgroundMusicVolume(volum);
	this->setEffectsVolume(volum);
	m_musicVolum = volum;
	CCAssert(0, "");
}

void SoundsController::newStopBackgroundMusic()//关闭背景音乐,音乐从当前音乐大小逐次减小
{
	this->schedule(schedule_selector(SoundsController::setVolumLogic));
	CCAssert(0, "");
}

void SoundsController::newStopEffect()//关闭音效音乐,音效从当前音乐大小逐次减小
{
	CCAssert(0, "");
}

void SoundsController::setVolumLogic(float t)
{
	if (m_musicVolum > 0)
	{
		m_musicVolum -= 1;
	}
	if (m_musicVolum <= 0)
	{
		this->unschedule(schedule_selector(SoundsController::setVolumLogic));
		this->stopBackgroundMusic();
	}
	CCAssert(0, "");
}