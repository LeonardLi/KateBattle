//
//  Monster.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__Monster__
#define __KateBattle__Monster__

#include "Entity.h"
#include "cocos2d.h"
class MonsterFSM;
class Hero;
class BulletBase;
enum class JoystickEnum;
enum class MonsterType
{
	normalTypeLv1,
	normalAttackFastTypeLv1,
	normalMoveFastTypeLv1,
	normalFatTypeLv1,
	normalIronTypeLv1,
	normalAggressiveTypeLv1,
	shootTypeLv1,
	shootAggressiveTypeLv1,
	shootSlowTypeLv1,
	monsterBossNum1,
	num1ShootType,
	num1BoxType,
	monsterBossNum2,
	monsterBossNum2Assister,
	monsterBossNum3,
	num3CarType,
	num3BoxType,
	block,
};


class Monster : public Entity{
public:
	static Monster* create(cocos2d::Sprite* sprite, MonsterType Type);
	bool init(cocos2d::Sprite* sprite,MonsterType type);

	virtual void update(float delta);
	
	

	void monsterGetHurt(float iValue, float time,bool isCrit);
	MonsterFSM* getFSM();
	void attackSequence();
	void useSkillSequence();
	void skillRush(float dt);
	
	void skillFinish(float dt);

	void skillShot(float dt);
	void skillShotQuickly(float dt);

	void boss2AssistStartSkill();
	void showFire(cocos2d::Vec2 location);

	void choiceDirectionToAction(std::string action);

	void castMessage(std::string message
		);

protected:
	void onDead();
	void onHurt();
	void _loadCSB(std::string csbfile,int tag);
private:

	
	//move
	void __monsterMoveToHero(float dt);
	void __monsterRandomMove();

	//attack
	void __readyForAttack(float dt);
	void __attack();
	
	void __attackWithHand();
	void __attackafterMove();
	void __finishAttack(float dt);

	//skill
	void __readyForUseSkill(float dt);
	void __skill();
	
	void __useSkill(float dt);

	//remote attack
	void __initBullet(int bulletType);
	void __attackWithBullet();
	void __bulletLogicCheck(float dt);
	BulletBase* __getAnyUnUsedBullet();

	//judge state
	
	void __intoAttackSequence(float dt);
	void __intoSkillSequence(float dt);

	//distance judge
	void __isInViewRange(float dt);
	void __moveCloseToHero(cocos2d::Vec2 distance);
	

	//post message
	void __postBossAttackMessage(float dt);
	void __postBossSkillMessage(float dt);

	
	void __judgeAttackHero();

	void __changeStun(float dt);
public:
	cocos2d::Vec2 heroLocation;
	cocos2d::Vector<BulletBase*> m_bulletList;
	cocos2d::Vector<Monster*> dangerousAreaList;
	Hero* targetHero;
	
	Monster* m_boxes;
	MonsterType m_monsterType;
	MonsterFSM* m_FSM;
	bool skillOrAttack;
	bool bossOrNot;

	cocos2d::ProgressTimer* bloodBar;
private:
	CC_SYNTHESIZE(int, m_boxTag, boxTag);
	CC_SYNTHESIZE(double, m_attackRange, attackRange);
	CC_SYNTHESIZE(float, m_AttackValue, AttackValue);
	CC_SYNTHESIZE(float, m_DefenceValue, DefenceValue);
	CC_SYNTHESIZE(float, m_SpeedRate, SpeedRate);
	CC_SYNTHESIZE(float, m_Hp, Hp);
	CC_SYNTHESIZE(float, m_upperHp, upperHp);
	CC_SYNTHESIZE(float, m_attackTime, attackTime);
	CC_SYNTHESIZE(float, m_viewRange, viewRange);
	cocostudio::Armature* m_armature;
	CC_SYNTHESIZE(bool, m_direction, direction);
	CC_SYNTHESIZE(bool, m_canAttack, canAttack);
	CC_SYNTHESIZE(bool, m_isMoving,isMoving);
	CC_SYNTHESIZE(bool,m_isStanding,isStanding);
	CC_SYNTHESIZE(bool, m_isDead, isDead);
	CC_SYNTHESIZE(bool, m_Attacked, Attacked);
	//be attacked just now

};


class MonsterBossNum1 :public Monster{

public:
	static MonsterBossNum1* create(cocos2d::Sprite* sprite, cocos2d::Vector<Monster*> monsterList);
	bool init(cocos2d::Sprite* sprite, cocos2d::Vector<Monster*> monsterList);
	cocos2d::Vector<Monster*> shootMonsterList;
	

	void intoBoss1SkillSequence(float dt);
	void outBoss1SkillSequence(float dt);
private:
	void __skillRushBox(float dt);
	void __skillRush(float dt);
	void __isCollide(float dt);
public:
	Monster* box;
private:

};

class MonsterBossNum2 : public Monster{

public:
	static MonsterBossNum2* create(cocos2d::Sprite* sprite, Monster* monster);
	bool init(cocos2d::Sprite* sprite,  Monster* monster);
	void intoBoss2SkillSequence(float dt);
	void outBoss2SkillSequence(float dt);
private:
	void __dangerousAreaJudge(float dt);
	void __rotateAreaJudge(float dt);
	void __bossRotate();
	void __bossRotateStop(float dt);
	void __bossJump();
	void __bossRushToBox(float dt);
	void __bossRushJudge(float dt);
	void __bossRushMoveEnd(float dt);

public:

	
private:
	Monster* monsterAssist;
	
};


class MonsterBossNum3 :public Monster{

public:
	static MonsterBossNum3* create(cocos2d::Sprite* sprite, cocos2d::Vector<Monster*> monsterList);
	bool init(cocos2d::Sprite* sprite, cocos2d::Vector<Monster*> monsterList);
	cocos2d::Vector<Monster*> carMonsterList;
	void showTheCar(float dt);
	
	void intoBoss3SkillSequence(float dt);
	void outBoss3SkillSequence(float dt);

private:
	void __bossRunOutOfGround(float dt);
	void __runTheCar(float dt);
	void __runNumber1Car(float dt);
	void __runNumber2Car(float dt);
	void __runNumber3Car(float dt);
	void __removeTheCar(float dt);
	void __isCarCollide(float dt); 
	void __skillDropBox(float dt);
	void __dropBoxCollide(float dt);
	void __findAnyVacantPlace(float dt);
	void __dropBoxEnd(float dt);
	void __showTheShadow(int locationNum);
	void __isBoxNeedRemove(float dt);

private:
	int isPlaceVacant[4];
	cocos2d::Vector<Monster*> boxList;
	cocos2d::Vector<Monster*> notFallBoxList;
	cocos2d::Vector<Monster*> fallingBoxList;
	cocos2d::Vector<Monster*> shadowList;
	int lastBoxNumber;
};




#endif /* defined(__KateBattle__Monster__) */
