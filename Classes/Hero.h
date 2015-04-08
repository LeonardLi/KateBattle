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
class ControllerMoveBase;
enum class JoystickEnum;

class Hero : public Entity{

public:
	void ChangeDirection(JoystickEnum direction);
	
	static Hero* create(cocos2d::Sprite* sprite);
	
	Hero* initFromJson();

	virtual void onDead();
	
	virtual void onHurt();

	void changeControlType(float dt);

	void heroNotControl(float time);

	void attack();
private:
	Hero();

	bool init(cocos2d::Sprite* sprite);
	
	virtual void update(float dt);
	
	

	void changeStun(float dt);

	void herostun(float time);
public:
	bool m_canControl;

private:
	ControllerMoveBase* m_moveController;

	CC_SYNTHESIZE(int, m_hp, Hp);

	JoystickEnum m_direction;

	int m_heroDirection;


};


#endif /* defined(__KateBattle__Hero__) */
