//
//  JsonReader.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "JsonReader.h"

JsonReader* JsonReader::m_jsonReader = nullptr;

JsonReader* JsonReader::getInstance(){

	if (m_jsonReader == nullptr)
	{
		m_jsonReader = new JsonReader();
		if (m_jsonReader && m_jsonReader->init()){
		}
		else
		{
			CC_SAFE_DELETE(m_jsonReader);
		}

	}
	return m_jsonReader;
}

bool JsonReader::init(){
	return true;
}