#include "AppDelegate.h"
#include "GameScene.h"
#include "Kernal.h"
#include "SimpleAudioEngine.h"
#include "JsonUtility.h"
#include "SoundsController.h"
#include "SoundsDef.h"

USING_NS_CC;
using namespace CocosDenshion;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("katty battle");
        director->setOpenGLView(glview);
    }
	glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::EXACT_FIT);
	preLoadMusic();
	Kernal* GameKernal = Kernal::create();

	GameKernal->startGame();
	
    return true;
}



// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::preLoadMusic(){
	SoundsController::getInstance()->preloadBackgroundMusic(MUSIC_1.c_str());
	SoundsController::getInstance()->preloadBackgroundMusic(MUSIC_2.c_str());
	SoundsController::getInstance()->preloadBackgroundMusic(MUSIC_3.c_str());
	SoundsController::getInstance()->preloadBackgroundMusic(MUSIC_4.c_str());
}