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




class SoundsController : public cocos2d::Node{
public:

	char* getMusicFileName(std::string);

	char* getEffectsFileName(std::string);

	void setMusicVolum(float volum);   //�����������ֵ����������������Լ���Ч
	
	void stopBackgroundMusic();//�رձ�������,���ִӵ�ǰ���ִ�С��μ�С

	void stopEffect();//�ر���Ч����,��Ч�ӵ�ǰ���ִ�С��μ�С
	
	static SoundsController* getInstance();
private:
	float m_BackMusicVolum;  //�������������Ĵ�С
	float m_EffectMusicVolum;  //��Ч�����Ĵ�С
	void _setBackVolumLogic(float dt);
	void _setEffectVolumLogic(float dt);

};
#endif /* defined(__KateBattle__SoundsController__) */
