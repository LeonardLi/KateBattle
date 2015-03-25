//
//  JsonReader.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__JsonReader__
#define __KateBattle__JsonReader__

#include <stdio.h>
#include "cocos2d.h"

class JsonReader : public cocos2d::Node{

public:
	JsonReader* getInstance();
	virtual bool init();


public:
	static JsonReader* m_jsonReader;

};





#endif /* defined(__KateBattle__JsonReader__) */
