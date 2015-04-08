#include "GameScene.h"
#include "JoyStick.h"
#include "Hero.h"
#include "cocos2d.h"
#include "ControllerMoveBase.h"
#include "JsonReader.h"
#include "Monster.h"
#include "MonsterManager.h"
USING_NS_CC;

#define COLLIDEMARGIN 30

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	m_hero = Hero::create(Sprite::create("wolf.png"));
	m_hero->setPosition(200, 200);
	this->addChild(m_hero, 1);


    m_stick = Joystick::create("directioncontrol1.png", "directioncontrol2.png");
    this->addChild(m_stick);
    m_stick->setPosition(Vec2(200,200));
	m_stick->setDieRadius(120);
	m_stick->setFailRadius(0);	
	m_stick->onDirection = CC_CALLBACK_1(GameScene::onDirectionChange, this);
    m_stick->onRun();

	m_monsterMgr = MonsterManager::createWithLevel(11);
	this->addChild(m_monsterMgr);

	this->scheduleUpdate();

	//读取json文件
	//根据传入的不同的关卡值
	//载入背景(关卡数值对应图片)
	//载入游戏UI
	//载入背景动画
	//载入英雄（英雄各种属性、装备、物品、技能）
	//载入不同怪物
	//auto monsterMgr = MonsterManager::createWithLevel(level,=====!!!Map!!!====);

	//游戏逻辑update();


	//关卡结束后
	//写JSON文件
	//弹出界面(下一关、重新玩、主菜单)
	//删除之前界面元素（数组中）
    return true;
}


void  GameScene::onDirectionChange(JoystickEnum direction){
	m_hero->ChangeDirection(direction);
}

void GameScene::attackBtnOnClick(Ref* Sender, ui::Widget::TouchEventType type){

	m_hero->attack();
	//check
	//monsterMgr 
		
}

void GameScene::skillBtn1OnClick(Ref* Sender, ui::Widget::TouchEventType type){

}

void GameScene::skillBtn2OnClick(Ref* Sender, ui::Widget::TouchEventType type){

}

void GameScene::skillBtn3OnClick(Ref* Sender, ui::Widget::TouchEventType type){

}

void GameScene::update(float dt){
	for (auto monster : m_monsterMgr->getMonsterList())
	{




		/*Rect monsterRect = monster->getBoundingBox();
		Rect monsterCollideRect = Rect(monsterRect.origin.x + COLLIDEMARGIN, monsterRect.origin.y + COLLIDEMARGIN,
			monsterRect.size.width - 2 * COLLIDEMARGIN, monsterRect.size.height - 2 * COLLIDEMARGIN);
		
		Rect heroRect = m_hero->getBoundingBox();
		if (monsterCollideRect.intersectsRect(heroRect)&&m_hero->m_canControl==true)
		{
			m_hero->heroNotControl(0.5f);
			
			m_hero->runAction(MoveBy::create(0.5, Vec2((m_hero->getPositionX()-monster->getPositionX())/2, (m_hero->getPositionY()-monster->getPositionY())/2)));

			log("collide");
		}*/

	}
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


