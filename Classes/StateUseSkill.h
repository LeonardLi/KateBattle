#ifndef __KataBattle__StateUseSkill__
#define __KataBattle__StateUseSkill__

#include "I_State.h"
class Monster;
enum class EnumMsgType;
class StateUseSkill: public I_State{
	virtual void execute(Monster* monster, EnumMsgType type);
};

class BossStateUseSkill : public I_State{
	virtual void execute(Monster* monster, EnumMsgType type);
};

#endif