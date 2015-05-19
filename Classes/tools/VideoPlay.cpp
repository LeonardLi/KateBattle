#include "VideoPlay.h"
#include "MenuScene.h"
USING_NS_CC;

Scene* VideoPlay::createScene()
{
	auto scene = Scene::create();
	auto layer = VideoPlay::create();
	scene->addChild(layer);
	return scene;
}
bool VideoPlay::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}

void VideoPlay::onEnter(){
	Layer::onEnter();
	showVideo();
}

void VideoPlay::showVideo(){
	Size size = Director::getInstance()->getVisibleSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	auto videoPlayer = cocos2d::experimental::ui::VideoPlayer::create();
	videoPlayer->setPosition(Point(size.width / 2, size.height / 2));
	videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	videoPlayer->setContentSize(Size(size.width, size.height));
	this->addChild(videoPlayer);
	if (videoPlayer)
	{
		videoPlayer->setFileName("caty.mp4");
		videoPlayer->play();
	}
	videoPlayer->addEventListener(CC_CALLBACK_2(VideoPlay::videoEventCallback, this));
#endif
}

/**
* ��Ƶ������ɵĻص�����
*/
void VideoPlay::videoPlayOverCallback()
{
	auto scene = MenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
/**
*  ��Ƶ���ŵ�״̬
*  ע������Ĵ��룬�˴�����ֻ����androidƽ̨��Iosƽ̨��Ч
*/
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
void VideoPlay::videoEventCallback(Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType){
	switch (eventType) {
	case cocos2d::experimental::ui::VideoPlayer::EventType::PLAYING:
		break;
	case cocos2d::experimental::ui::VideoPlayer::EventType::PAUSED:
		break;
	case cocos2d::experimental::ui::VideoPlayer::EventType::STOPPED:
		break;
	case cocos2d::experimental::ui::VideoPlayer::EventType::COMPLETED:
		videoPlayOverCallback();
		break;
	default:
		break;
	}
}
#endif