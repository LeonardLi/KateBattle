//
//  Monster.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__Monster__
#define __KateBattle__Monster__

#include <stdio.h>
#include "Entity.h"

class Monster : public Entity{
public:
	virtual void onDead();
	virtual void onHurt();
private:
};

#endif /* defined(__KateBattle__Monster__) */
