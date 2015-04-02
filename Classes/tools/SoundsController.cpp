//
//  SoundsController.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/19.
//
//

#include "SoundsController.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

char* SoundsController::getMusicFileName(MusicEnum musicType){

	std::string suffix = NULL;
	std::string music = NULL;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	suffix = ".mp3";
#else  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	suffix = ".mp3";
#endif
	switch (musicType)
	{
	case MusicEnum::MUSIC_1:

		break;
	case MusicEnum::MUSIC_2:
		break;
	case MusicEnum::MUSIC_COUNTS:
		break;
	default:
		break;
	}	
		return  const_cast<char*>(music.c_str());
}

char* SoundsController::getEffectsFileName(EffectsEnum effectType){

	std::string suffix = NULL;
	std::string effect = NULL;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	suffix = ".wav";
#else  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	suffix = ".ogg";
#endif
	switch (effectType)
	{
	case EffectsEnum::EFFECT_1:
		break;
	case EffectsEnum::EFFECT_2:
		break;
	case EffectsEnum::EFFECT_3:
		break;
	default:
		break;
	}
	return const_cast<char*>(effect.c_str());
}