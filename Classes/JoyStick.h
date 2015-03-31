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
    /** �����u���� */
    void onRun();
    /** ������� */
    void onDisable();
    /** ���������뾶���������뾶��ҡ����ʧЧ */
    void setDieRadius(float radius);
    /** ������Ч����뾶���������Ч����ȣ������ã� */
    void setFailRadius(float radius);
    /** �Ƿ���ʾ���̺ʹ��� */
    void setVisibleJoystick(bool visible);
    /** �Ƿ����ɱ任ҡ������λ�ã�������Ļ��ÿһ�ΰ������ʱ�����꽫��ҡ���������꣬�ƶ�ʱ�����ı�ҡ�������ֱ꣬���´ΰ������ */
    void setAutoPosition(bool value);
    /** �ص�����ָ�� */
	std::function<JoystickEnum(JoystickEnum)> onDirection;
    /** ��̬������������Ҫ������̺ʹ���ͼƬ·���� */
    static Joystick* create(std::string chassisPath,std::string dotPath);
    /** ��ʼ��ҡ��������Ҫ������̺ʹ���ͼƬ·���� */
    void initWithJoystick(std::string chassisPath,std::string dotPath);
protected:
    /** ��Ч����뾶 */
    float _radius;
    /** ʧЧ����뾶 */
    float _failradius;
    /** �Ƿ��Ƴ���Ч���� */
    bool isMoveOut;
    /** �Ƿ������Ч����뾶 */
    bool isDieRadius;
    /** �Ƿ����ɱ任ҡ�������� */
    bool isAutoPosition;
    /** ���� */
    JoystickEnum _direction;
    /** ���� */
    cocos2d::Sprite* _chassis;
    /** ���� */
    cocos2d::Sprite* _touchDot;
    cocos2d::EventListenerTouchOneByOne* listener;
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    /**
     1�����ô��㣬���ж��Ƿ�����Ч�����ڣ��������Ч�����ڣ������ã�
     2�����ͽǶȱ仯�����������Ч�����ڣ� */
    void setTouchDotPosition(cocos2d::Vec2 vec1, cocos2d::Vec2 vec2);
    /**
     1������ҡ�����˷���
     2�����ͽǶȱ仯���ص����ȱ仯���� */
    void changeAngle( cocos2d::Vec2 position );
    /** �ص�ע��ļ������� */
    void callDirectionFun();
    /** ���ã������Ȳ��� DEFAULTʱ�����ã� */
    void resetState();
    
};

#endif /* defined(__KateBattle__JoyStick__) */
