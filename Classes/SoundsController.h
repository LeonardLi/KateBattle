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

	void setMusicVolum(float volum);   //�����������ֵ����������������Լ���Ч
	
	void newStopBackgroundMusic();//�رձ�������,���ִӵ�ǰ���ִ�С��μ�С

	void newStopEffect();//�ر���Ч����,��Ч�ӵ�ǰ���ִ�С��μ�С

private:
	float m_musicVolum;  //���������Ĵ�С
	void setVolumLogic(float t);


};
#endif /* defined(__KateBattle__SoundsController__) */
