//
//  JoyStick.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//
#include "cocos2d.h"
#ifndef __KateBattle__JoyStick__
#define __KateBattle__JoyStick__

#include "cocos2d.h"

enum class JoystickEnum
{
    DEFAULT,
    D_UP,
    D_DOWN,
    D_LEFT,
    D_RIGHT,
    D_LEFT_UP,
    D_LEFT_DOWN,
    D_RIGHT_UP,
    D_RIGHT_DOWN
};

class Joystick : public cocos2d::Layer
{
public:
    /** 启动搖杆器 */
    void onRun();
    /** 清除数据 */
    void onDisable();
    /** 设置死亡半径，即超出半径將摇杆器失效 */
    void setDieRadius(float radius);
    /** 设置无效区域半径（如果在无效区域內，將重置） */
    void setFailRadius(float radius);
    /** 是否显示底盘和触点 */
    void setVisibleJoystick(bool visible);
    /** 是否自由变换摇杆器的位置，即在屏幕上每一次按下鼠标时的坐标将是摇杆器的坐标，移动时将不改变摇杆器坐标，直到下次按下鼠标 */
    void setAutoPosition(bool value);
    /** 回调函数指针 */
	std::function<JoystickEnum(JoystickEnum)> onDirection;
    /** 静态创建函数（需要传入底盘和触点图片路径） */
    static Joystick* create(std::string chassisPath,std::string dotPath);
    /** 初始化摇杆器（需要传入底盘和触点图片路径） */
    void initWithJoystick(std::string chassisPath,std::string dotPath);
protected:
    /** 有效区域半径 */
    float _radius;
    /** 失效区域半径 */
    float _failradius;
    /** 是否移出有效区域 */
    bool isMoveOut;
    /** 是否存在有效区域半径 */
    bool isDieRadius;
    /** 是否自由变换摇杆器坐标 */
    bool isAutoPosition;
    /** 方向 */
    JoystickEnum _direction;
    /** 底盘 */
    cocos2d::Sprite* _chassis;
    /** 触点 */
    cocos2d::Sprite* _touchDot;
    cocos2d::EventListenerTouchOneByOne* listener;
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    /**
     1、设置触点，并判断是否在无效区域内（如果在无效区域内，将重置）
     2、发送角度变化（如果不在无效区域内） */
    void setTouchDotPosition(cocos2d::Vec2 vec1, cocos2d::Vec2 vec2);
    /**
     1、计算摇杆器八方向
     2、发送角度变化，回调弧度变化函数 */
    void changeAngle( cocos2d::Vec2 position );
    /** 回调注册的监听函数 */
    void callDirectionFun();
    /** 重置（当弧度不是 DEFAULT时才重置） */
    void resetState();
    
};

#endif /* defined(__KateBattle__JoyStick__) */
