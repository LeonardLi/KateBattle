#ifndef __KataBattle__MonsterFSM__
#define __KataBattle__MonsterFSM__

#include "cocos2d.h"



class Monster;
class I_State;

class MonsterFSM : public cocos2d::Node{

public:
	~MonsterFSM();
	static MonsterFSM* createWithMonster(Monster* monster);
	bool initWithMonster(Monster* monster);

	void changeState(I_State* state);
	void OnRecvWantToUseSkill(Ref* obj);
	void OnRecvWantToAttack(Ref* obj);
private:

	Monster* monster;
	I_State* mCurState;

};
#endif