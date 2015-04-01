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

private:
	Hero();
	virtual bool init(cocos2d::Sprite* sprite);
	ControllerMoveBase* m_moveController;
	virtual void update(float dt);

	CC_SYNTHESIZE(int, m_hp, Hp);
	JoystickEnum m_direction;
};


#endif /* defined(__KateBattle__Hero__) */
