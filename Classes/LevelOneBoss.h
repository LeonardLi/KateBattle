#ifndef __KataBattle__LevelOneBoss__
#define __KataBattle__LevelOneBoss__

#include "cocos2d.h"
class Monster;

class LevelOneBoss : public Monster{

public:
	void attack();
	void skillSheld();
	void skillLine();

};


#endif