#ifndef __KataBattle__State__
#define __KataBattle__State__


class Monster;
enum class EnumMsgType{

	en_Msg_WantToUseSkill,
	en_Msg_WantToAttack,
	en_Msg_Count
};


class I_State{
public:
	virtual void execute(Monster* monster,EnumMsgType type) = 0;
};

#endif