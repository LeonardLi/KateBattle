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
enum class ScenarioEnum;



class SoundsController : public cocos2d::Node,public CocosDenshion::SimpleAudioEngine{
public:

	char* getMusicFileName(std::string);

	char* getEffectsFileName(std::string);

	void setMusicVolum(float volum);   //调整所有音乐的音量，包括音乐以及音效
	
	void pauseBackgroundMusic();//关闭背景音乐,音乐从当前音乐大小逐次减小

	void stopBackgroundMusic(ScenarioEnum scen);//场景切换时，背景音乐的播放

	void pauseEffect();//关闭音效音乐,音效从当前音乐大小逐次减小
	
	static SoundsController* getInstance();
private:
	ScenarioEnum scenario;
	float m_BackMusicVolum;  //背景音乐音量的大小
	float m_EffectMusicVolum;  //音效音量的大小
	void _setBackVolumLogic(float dt);
	void _setEffectVolumLogic(float dt);
	void _setBackSceneVolumLogic(float dt);
		
};
#endif /* defined(__KateBattle__SoundsController__) */
