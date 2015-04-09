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


class CocosDenshion::SimpleAudioEngine;

class SoundsController:public CocosDenshion::SimpleAudioEngine{
public:


	char* getMusicFileName(std::string);

	char* getEffectsFileName(std::string);




};
#endif /* defined(__KateBattle__SoundsController__) */
