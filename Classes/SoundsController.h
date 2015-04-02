//
//  SoundsController.h
//  KateBattle
//
//  Created by Leonard on 15/3/19.
//
//

#ifndef __KateBattle__SoundsController__
#define __KateBattle__SoundsController__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

enum class MusicEnum{
	MUSIC_1,
	MUSIC_2,
	MUSIC_COUNTS
};

enum class EffectsEnum{
	EFFECT_1,
	EFFECT_2,
	EFFECT_3,
};

class CocosDenshion::SimpleAudioEngine;

class SoundsController:public CocosDenshion::SimpleAudioEngine{
public:


	char* getMusicFileName(MusicEnum);

	char* getEffectsFileName(EffectsEnum);


};
#endif /* defined(__KateBattle__SoundsController__) */
