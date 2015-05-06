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

	void setMusicVolum(float volum);   //�����������ֵ����������������Լ���Ч
	
	void pauseBackgroundMusic();//�رձ�������,���ִӵ�ǰ���ִ�С��μ�С

	void stopBackgroundMusic(ScenarioEnum scen);//�����л�ʱ���������ֵĲ���

	void pauseEffect();//�ر���Ч����,��Ч�ӵ�ǰ���ִ�С��μ�С
	
	static SoundsController* getInstance();
private:
	ScenarioEnum scenario;
	float m_BackMusicVolum;  //�������������Ĵ�С
	float m_EffectMusicVolum;  //��Ч�����Ĵ�С
	void _setBackVolumLogic(float dt);
	void _setEffectVolumLogic(float dt);
	void _setBackSceneVolumLogic(float dt);
		
};
#endif /* defined(__KateBattle__SoundsController__) */
