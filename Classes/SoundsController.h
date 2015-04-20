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




class SoundsController : public CocosDenshion::SimpleAudioEngine,public cocos2d::Node{
public:


	char* getMusicFileName(std::string);

	char* getEffectsFileName(std::string);

	void setMusicVolum(float volum);   //调整所有音乐的音量，包括音乐以及音效
	
	void newStopBackgroundMusic();//关闭背景音乐,音乐从当前音乐大小逐次减小

	void newStopEffect();//关闭音效音乐,音效从当前音乐大小逐次减小

private:
	float m_musicVolum;  //音乐音量的大小
	void setVolumLogic(float t);


};
#endif /* defined(__KateBattle__SoundsController__) */
