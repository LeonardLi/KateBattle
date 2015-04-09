//
//  JsonReader.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__JsonReader__
#define __KateBattle__JsonReader__

#include "cocos2d.h"

class JsonReader{

public:
	static JsonReader* getInstance();
	virtual bool init();

	/*read Json from files*/
	std::string readJson(std::string jsonPath);

	void writeJson();
public:
	static JsonReader* m_jsonReader;

};





#endif /* defined(__KateBattle__JsonReader__) */
