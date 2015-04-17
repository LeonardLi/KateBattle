#ifndef __KataBattle__MonsterFSM__
#define __KataBattle__MonsterFSM__

#include "cocos2d.h"



class Monster;
class I_State;

enum class EnumMsgType;
class MonsterFSM : public cocos2d::Node{

public:
	~MonsterFSM();
	static MonsterFSM* createWithMonster(Monster* monster);
	bool initWithMonster(Monster* monster);

	void changeState(I_State* state);

	void OnRecvWantToUseSkill(Ref* obj);
	void OnRecvWantToAttack(Ref* obj);
	void OnRecvBossWantToUseSkill(Ref* obj);
	void OnRecvBossWantToAttack(Ref* obj);

	int getState();

public:
	enum stateNum{
		toUseSkill,
		toAttack,
		BosstoUseSkill,
		BossToAttack,
	};
private:

	Monster* monster;
	I_State* mCurState;
	int state;
	
};
#endif