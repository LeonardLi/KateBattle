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

class Hero : public Entity{

public:
	void ChangeDirection(JoystickEnum direction);
	
	static Hero* create(cocos2d::Sprite* sprite);
	
	Hero* initFromJson();

	void onDead();
	
	void onHurt();

	void changeControlType(float dt);

	void heroNotControl(float time);

	void attack();

	void getHurt(float ivalue,float stunTime,float slowValue,float slowTime);

protected:
	virtual void _loadCSB(std::string);
	

private:
	Hero();

	bool init(cocos2d::Sprite* sprite);
	
	virtual void update(float dt);
	
	void changeStun(float dt);

	void herostun(float time);

	void changeSpeed(float slowValue, float slowTime);

	void recoverSpeed(float dt);

public:
	bool m_canControl;
	cocos2d::Vector <Monster*> m_blockArea;
private:
	ControllerMoveBase* m_moveController;

	CC_SYNTHESIZE(int, m_hp, Hp);
	CC_SYNTHESIZE(float, m_defaultSpeed, DefaultSpeed);

	JoystickEnum m_direction;

	int m_heroDirection;


};


#endif /* defined(__KateBattle__Hero__) */
