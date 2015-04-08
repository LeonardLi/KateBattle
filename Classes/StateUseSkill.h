#ifndef __KataBattle__StateUseSkill__
#define __KataBattle__StateUseSkill__

#include "I_State.h";
class Monster;
class StateUseSkill: public I_State{
	virtual void execute(Monster* monster, EnumMsgType type);
};

#endif