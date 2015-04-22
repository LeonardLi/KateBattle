//
//  Hero.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__Hero__
#define __KateBattle__Hero__
#include "Entity.h"
#include "cocos2d.h"
#include "Monster.h"
class ControllerMoveBase;
enum class JoystickEnum;

enum class Direction{
	right,
	left
};
class Hero : public Entity{

public:
	void ChangeDirection(JoystickEnum direction);
	
	static Hero* create();
	
	Hero* initFromJson();

	void onDead();
	
	void onHurt();

	void changeControlType(float dt);

	void heroNotControl(float time);

	void attack();

	void getHurt(float ivalue,float stunTime,float slowValue,float slowTime);

	//Animation play
	void playAnimaitonStand(Direction);
	void playAnimaitonWalk(Direction);
	void playAnimaitonAttack(Direction);
	void playAnimaitonHurt(Direction);
	void playAnimaitonDead(Direction);
protected:
	virtual void _loadCSB(std::string);
	

private:
	Hero();

	virtual bool init();
	
	virtual void update(float dt);
	
	void changeStun(float dt);

	void herostun(float time);

	void changeSpeed(float slowValue, float slowTime);

	void recoverSpeed(float dt);


	


public:
	bool m_canControl;
	cocos2d::Vector <Monster*> m_blockArea;
private:

	CC_SYNTHESIZE(int, m_hp, Hp);
	CC_SYNTHESIZE(float, m_defaultSpeed, DefaultSpeed);
	CC_SYNTHESIZE(ControllerMoveBase*, m_moveController, MoveController);
	JoystickEnum m_direction;
	cocostudio::Armature* m_armature;

};


#endif /* defined(__KateBattle__Hero__) */
