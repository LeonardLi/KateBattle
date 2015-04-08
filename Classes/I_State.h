#ifndef __KataBattle__State__
#define __KataBattle__State__

#include "EnumMsgType.h"
class Monster;



class I_State{
public:
	virtual void execute(Monster* monster,EnumMsgType type) = 0;
};

#endif