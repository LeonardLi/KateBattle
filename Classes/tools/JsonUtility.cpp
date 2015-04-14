//
//  JsonUnity.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//
#include "cocos2d.h"
#include "JsonUtility.h"

USING_NS_CC;
JsonUnity* JsonUnity::m_JsonUnity = nullptr;

void JsonUnity::read()
{
	std::string filePath = FileUtils::getInstance()->fullPathForFilename("groot.json");
	std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
	m_doc.Parse<0>(contentStr.c_str());
	if (m_doc.HasParseError())
	{
		CCLOG("GetParseError %s\n", m_doc.GetParseError());
		return;
	}
	if (!m_doc.IsObject())
	{
		CCLOG("no object!");
		return;
	}
	if (!m_doc.HasMember("User"))
	{
		CCLOG("no member!");
		return;
	}
	if (!m_doc.HasMember("User"))
	{
		CCLOG("No User!");
		return;
	}
	if (!m_doc.HasMember("Data"))
	{
		CCLOG("No Data!");
		return;
	}
	rapidjson::StringBuffer buffer;
	rapidjson::Writer< rapidjson::StringBuffer > writer(buffer);
	m_doc.Accept(writer);
	const char * lin = buffer.GetString();
	CCLOG("GROOT:%s", lin);
}
void JsonUnity::write(User user)    //写是数组类型的元素，只写json数组的大小
{
	if (!m_doc.IsObject())
	{
		CCLOG("NO OBJECT IN WRITING!");
		return;
	}
	rapidjson::Value& val = m_doc["User"];
	rapidjson::Value& tem = val["UserName"];
	if (tem.IsString())
	{
		CCLOG("UserName:%s", tem.GetString());
		tem.SetString(user.UserName);
		CCLOG("UserName:%s", val["UserName"].GetString());
	}
	rapidjson::Value& bon = val["UserBonesNumber"];
	if (bon.IsInt())
	{
		CCLOG("UserBonesNumber:%i", bon.GetInt());
		bon.SetInt(user.UserBonesNumber);
		CCLOG("UserBonesNumber:%i", bon.GetInt());
	}
	rapidjson::Value& gold = val["UserGoldsNumber"];
	if (gold.IsInt())
	{
		CCLOG("UserGoldsNumber:%i", gold.GetInt());
		gold.SetInt(user.UserGoldsNumber);
		CCLOG("UserGoldsNumber:%i", gold.GetInt());
	}
	rapidjson::Value& health = val["UserHealth"];

	CCLOG("UserHealth:%lf", health.GetDouble());
	health.SetDouble(user.UserHealth);
	CCLOG("health :%lf", health.GetDouble());

	rapidjson::Value& attack = val["UserAttack"];

	CCLOG("UserAttack:%lf", attack.GetDouble());
	attack.SetDouble(user.UserAttack);
	CCLOG("UserAttack :%lf", attack.GetDouble());

	rapidjson::Value& defense = val["UserDefense"];
	CCLOG("UserDefense:%lf", defense.GetDouble());
	defense.SetDouble(user.UserDefense);
	CCLOG("UserDefense :%lf", defense.GetDouble());

	rapidjson::Value& speed = val["UserSpeed"];

	CCLOG("UserSpeed:%lf", speed.GetDouble());
	speed.SetDouble(user.UserSpeed);
	CCLOG("UserSpeed :%lf", speed.GetDouble());

	rapidjson::Value& strength = val["UserStrength"];

	CCLOG("UserStrength:%lf", strength.GetDouble());
	strength.SetDouble(user.UserStrength);
	CCLOG("UserStrength :%lf", strength.GetDouble());

	rapidjson::Value& skill = val["SkillID"];
	int i;
	if (skill.IsArray())
	{
		for (i = 0; i < skill.Capacity(); i++)
		{
			if (user.SkillID[i] == -1)
				break;
			rapidjson::Value&first = skill[i];
			CCLOG("skill[%i]:%i", i, first.GetInt());
			first.SetInt(user.SkillID[i]);
			CCLOG("skill[%i]:%i", i, first.GetInt());
		}
		for (; i < skill.Capacity(); i++)
		{
			rapidjson::Value&first = skill[i];
			first.SetInt(-1);
		}
	}
	rapidjson::Value& tool = val["ToolID"];
	if (tool.IsArray())
	{
		for (i = 0; i < tool.Capacity(); i++)
		{
			if (user.ToolID[i] == -1)
				break;
			rapidjson::Value&first = tool[i];
			CCLOG("tool[%i]:%i", i, first.GetInt());
			first.SetInt(user.ToolID[i]);
			CCLOG("tool[%i]:%i", i, first.GetInt());
		}
		for (; i < tool.Capacity(); i++)
		{
			rapidjson::Value&first = tool[i];
			first.SetInt(-1);
		}
	}
	rapidjson::Value& equip = val["EquipID"];
	if (equip.IsArray())
	{
		for (i = 0; i < equip.Capacity(); i++)
		{
			if (user.EquipID[i] == -1)
				break;
			rapidjson::Value&first = equip[i];
			CCLOG("equip[%i]:%i", i, first.GetInt());
			first.SetInt(user.EquipID[i]);
			CCLOG("equip[%i]:%i", i, first.GetInt());
		}
		for (; i < equip.Capacity(); i++)
		{
			rapidjson::Value&first = equip[i];
			first.SetInt(-1);
		}
	}
	rapidjson::Value& clear = val["Clear_BlockID"];
	if (clear.IsInt())
	{
		CCLOG("Clear_BlockID:%i", clear.GetInt());
		clear.SetInt(user.Clear_BlockID);
		CCLOG("Clear_BlockID:%i", clear.GetInt());
	}
	rapidjson::StringBuffer buffer;
	rapidjson::Writer< rapidjson::StringBuffer > writer(buffer);
	m_doc.Accept(writer);
	const char * lin = buffer.GetString();
	CCLOG("GROOT1:%s", lin);
	FILE* file = fopen("groot.json", "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
}    //


User JsonUnity::getUser()					//获取用户信息
{
	User user;
	rapidjson::Value& val = m_doc["User"];
	rapidjson::Value& tem = val["UserName"];
	CCLOG("UserName:%s", tem.GetString());
	strcpy_s(user.UserName, tem.GetString());
	rapidjson::Value& bon = val["UserBonesNumber"];
	CCLOG("UserBonesNumber:%i", bon.GetInt());
	user.UserBonesNumber = bon.GetInt();
	rapidjson::Value& gold = val["UserGoldsNumber"];
	CCLOG("UserGoldsNumber:%i", gold.GetInt());
	user.UserGoldsNumber = gold.GetInt();
	rapidjson::Value& health = val["UserHealth"];

	CCLOG("UserHealth:%lf", health.GetDouble());
	user.UserHealth = health.GetDouble();

	rapidjson::Value& attack = val["UserAttack"];

	CCLOG("UserAttack:%lf", attack.GetDouble());
	user.UserAttack = attack.GetDouble();

	rapidjson::Value& defense = val["UserDefense"];
	CCLOG("UserDefense:%lf", defense.GetDouble());
	user.UserDefense = defense.GetDouble();

	rapidjson::Value& speed = val["UserSpeed"];

	CCLOG("UserSpeed:%lf", speed.GetDouble());
	user.UserSpeed = speed.GetDouble();

	rapidjson::Value& strength = val["UserStrength"];

	CCLOG("UserStrength:%lf", strength.GetDouble());
	user.UserStrength = strength.GetDouble();

	rapidjson::Value& skill = val["SkillID"];
	if (skill.IsArray())
	{
		for (int i = 0; i < skill.Capacity(); i++)
		{
			rapidjson::Value&first = skill[i];
			CCLOG("skill[%i]:%i", i, first.GetInt());
			user.SkillID[i] = first.GetInt();
		}
	}
	rapidjson::Value& tool = val["ToolID"];
	if (tool.IsArray())
	{
		for (int i = 0; i < tool.Capacity(); i++)
		{
			rapidjson::Value&first = tool[i];
			CCLOG("tool[%i]:%i", i, first.GetInt());
			user.ToolID[i] = first.GetInt();
		}
	}
	rapidjson::Value& equip = val["EquipID"];
	if (equip.IsArray())
	{
		for (int i = 0; i < equip.Capacity(); i++)
		{
			rapidjson::Value&first = equip[i];
			CCLOG("equip[%i]:%i", i, first.GetInt());
			user.EquipID[i] = first.GetInt();
		}
	}
	rapidjson::Value& clear = val["Clear_BlockID"];
	if (clear.IsInt())
	{
		CCLOG("Clear_BlockID:%i", clear.GetInt());
		user.Clear_BlockID = clear.GetInt();
	}


	return user;
}
void JsonUnity::setUser(User user)		//设置用户信息
{
	write(user);
}
//Block JsonUnity::getBlock(int ID)			//获取第i关卡信息
//{
//
//}
//Monster_info JsonUnity::getMonster(int ID)		// 获取第i个怪物
//{
//
//}
//Skill JsonUnity::getSkill(int ID)			//获取第i个技能
//{
//
//}
//Equipment JsonUnity::getEquipment(int ID)	//获取第i个装备
//{
//
//}
//Tool JsonUnity::getTool(int ID)			//获取第i个工具
//{
//
//}
rapidjson::Document JsonUnity::getDocument()			// 获取m_doc
{
	return m_doc;
}

JsonUnity* JsonUnity::getInstance(){

	if (m_JsonUnity == nullptr)
	{
		m_JsonUnity = new JsonUnity();
		if (m_JsonUnity && m_JsonUnity->init()){
		}
		else
		{
			CC_SAFE_DELETE(m_JsonUnity);
		}

	}
	return m_JsonUnity;
}

bool JsonUnity::init()
{
	read();
	return true;
}
