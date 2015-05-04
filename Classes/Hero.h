//
//  Hero.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//
#pragma once
#include "Entity.h"
#include "cocos2d.h"
#include "Monster.h"
class ControllerMoveBase;
class Monster;
enum class JoystickEnum;
enum class InventoryEnum;

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

	void seInventory(InventoryEnum);

	void changeControlType(float dt);

	void heroNotControl(float time);

	void attack();

	void blink();

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
	cocos2d::Vector <Monster*> m_heroMonsterList;
private:
	CC_SYNTHESIZE(float, m_attackSpeed, attackSpeed);
	CC_SYNTHESIZE(float, m_attackValue, attackValue);
	CC_SYNTHESIZE(float, m_attackRange, attackRange);
	CC_SYNTHESIZE(float, m_curHp, curHp);
	CC_SYNTHESIZE(float, m_finnalHp, finnalHp);

	CC_SYNTHESIZE(float, m_defaultSpeed, DefaultSpeed);
	CC_SYNTHESIZE(float, m_defaultAttackValue, defaultAttackValue);
	CC_SYNTHESIZE(float, m_defaultHp, defaultHp);
	CC_SYNTHESIZE(bool, m_isDead, isDead);
	CC_SYNTHESIZE(ControllerMoveBase*, m_moveController, MoveController);
	JoystickEnum m_direction;
	cocostudio::Armature* m_armature;

};



