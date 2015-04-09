//
//  JsonReader.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#include "JsonReader.h"
#include "cocostudio/CocoStudio.h"
#include "CCFileUtils.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "json/document.h"
#include <fstream>

USING_NS_CC;

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
std::string JsonReader::readJson(std::string jsonPath){
	rapidjson::Document doc;
	SSIZE_T size;

	unsigned char* ch = nullptr;
	ch = FileUtils::getInstance()->getFileData(jsonPath, "r", &size);
	if (ch != nullptr)
	{
		std::string contentStr = std::string((const char*)ch, size);
		doc.Parse<rapidjson::kParseDefaultFlags>(contentStr.c_str());
		log("%s\n", contentStr.c_str());
		//rapidjson::Value &valMonster = doc["string"];
		//const char* ch1 = valMonster.GetString();
		return contentStr;
	}
	else
	{
		log("not found json!");
		return "";
	}
	/*
	rapidjson::Document _doc;
	bool bRet = false;
	ssize_t size = 0;
	unsigned char *pBytes = NULL;*/
	//do {
	//	pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData("ball.json", "r", &size);
	//	CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
	//	std::string load_str((const char*)pBytes, size);
	//	CC_SAFE_DELETE_ARRAY(pBytes);
	//	_doc.Parse<0>(load_str.c_str());
	//	CC_BREAK_IF(_doc.HasParseError());
	//	//生成json文档对像  

	//	if (!_doc.IsObject())
	//		return;

	//	//是否有此成员  
	//	if (!_doc.HasMember("entities"))
	//		return;

	//	// 通过[]取成员值,再根据需要转为array,int,double,string  
	//	const rapidjson::Value &pArray = _doc["entities"];

	//	//是否是数组  
	//	if (!pArray.IsArray())
	//		return;

	//	for (rapidjson::SizeType i = 0; i < pArray.Size(); i++)
	//	{
	//		const rapidjson::Value &p = pArray[i];
	//		if (p.HasMember("entity"))
	//		{
	//			const rapidjson::Value &valueEnt = p["entity"];
	//			if (valueEnt.HasMember("TapOpposite") && valueEnt.HasMember("Interval") && valueEnt.HasMember("BallNum"))
	//			{
	//				const rapidjson::Value &tapOpposite = valueEnt["TapOpposite"];
	//				int tapOp = tapOpposite.GetInt();      //得到int值  

	//				const rapidjson::Value &interval = valueEnt["Interval"];
	//				float inter = interval.GetDouble();  //得到float,double值  

	//				const rapidjson::Value &ballNum = valueEnt["BallNum"];
	//				int ball = ballNum.GetInt();      //得到int值  

	//				ballParam param;
	//				param.tapOp = tapOp;
	//				param.inter = inter;
	//				param.ballIndex = ball;
	//				m_ballParamVec.push_back(param);
	//			}
	//		}
	//		else
	//		{
	//			return;
	//		}

	//	}
	//	bRet = true;

	//} while (0);

}

void JsonReader::writeJson(){
	rapidjson::Document document;
	document.SetObject();

	//make json
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	rapidjson::Value object(rapidjson::kObjectType);
	object.AddMember("int", 1, allocator);
	object.AddMember("double", 1.0, allocator);
	object.AddMember("bool", true, allocator);
	object.AddMember("hello", "wwwww", allocator);
	array.PushBack(object, allocator);
	document.AddMember("json", "json string", allocator);
	document.AddMember("array", array, allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);


	//output json
	std::string strJson(buffer.GetString(), buffer.Size());
	CCLOG("BioEvolve::CElemDataMgr:%s", strJson.c_str());
	std::string filepath = ("0000000.json");
	std::ofstream outfile;
	outfile.open(filepath.c_str());
	if (outfile.fail())
	{
		return;
	}
	outfile << strJson;
	outfile.close();
	CCLOG("%s", buffer.GetString());
}