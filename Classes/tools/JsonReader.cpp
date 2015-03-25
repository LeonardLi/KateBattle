//
//  JsonReader.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "JsonReader.h"

JsonReader* JsonReader::m_jsonReader =NULL;

JsonReader* JsonReader::getInstance(){

	if (m_jsonReader==NULL)
	{
		m_jsonReader = new JsonReader();
		if (m_jsonReader&&m_jsonReader->init()){
			m_jsonReader->autorelease();
			m_jsonReader->retain();
		}
		else
		{
			CC_SAFE_DELETE(m_jsonReader);
			m_jsonReader = NULL;
		}

	}
	return m_jsonReader;
}

bool JsonReader::init(){
	return true;
}