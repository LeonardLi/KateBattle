#pragma once
#include "cocos2d.h"
#include "ui/UIVideoPlayer.h"
#include "ui/CocosGUI.h"

class VideoPlay : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onEnter();

	void videoPlayOverCallback();

	void showVideo();
	/**
	* ��Ƶ����״̬��ֻ����android��iosƽ̨��Ч
	*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	void videoEventCallback(Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType);
#endif

	CREATE_FUNC(VideoPlay);
};
