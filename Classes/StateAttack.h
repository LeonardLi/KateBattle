#ifndef __KataBattle__StateAttack__
#define __KataBattle__StateAttack__

#include "I_State.h"

enum class EnumMsgType;

class Monster;
class StateAttack : public I_State{
public:
	virtual void execute(Monster* monster, EnumMsgType type);
};


class BossStateAttack :public I_State{
public:
	virtual void execute(Monster* monster, EnumMsgType type);
};

#endif