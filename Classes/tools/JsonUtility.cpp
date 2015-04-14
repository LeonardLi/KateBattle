//
//  JsonUtility.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//
#include "cocos2d.h"
#include "JsonUtility.h"

USING_NS_CC;
JsonUtility* JsonUtility::m_JsonUtility = nullptr;

void JsonUtility::read()
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
}

void JsonUtility::write(User user)    //写是数组类型的元素，只写json数组的大小
{
	if (!m_doc.IsObject())
	{
		CCLOG("NO OBJECT IN WRITING!");
		return;
	}
	rapidjson::Value& val = m_doc["User"];
	rapidjson::Value& tem = val["UserName"];
	tem.SetString(user.UserName);
	rapidjson::Value& bon = val["UserBonesNumber"];
	bon.SetInt(user.UserBonesNumber);
	rapidjson::Value& gold = val["UserGoldsNumber"];
	gold.SetInt(user.UserGoldsNumber);
	rapidjson::Value& health = val["UserHealth"];
	health.SetDouble(user.UserHealth);
	rapidjson::Value& attack = val["UserAttack"];
	attack.SetDouble(user.UserAttack);
	rapidjson::Value& defense = val["UserDefense"];
	defense.SetDouble(user.UserDefense);
	rapidjson::Value& speed = val["UserSpeed"];
	speed.SetDouble(user.UserSpeed);
	rapidjson::Value& strength = val["UserStrength"];
	strength.SetDouble(user.UserStrength);
	rapidjson::Value& skill = val["SkillID"];
	int i;
	if (skill.IsArray())
	{
		for (i = 0; i < skill.Capacity(); i++)
		{
			if (user.SkillID[i] == -1)
				break;
			rapidjson::Value&first = skill[i];
			first.SetInt(user.SkillID[i]);
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
			first.SetInt(user.ToolID[i]);
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
			first.SetInt(user.EquipID[i]);
		}
		for (; i < equip.Capacity(); i++)
		{
			rapidjson::Value&first = equip[i];
			first.SetInt(-1);
		}
	}
	rapidjson::Value& clear = val["Clear_BlockID"];
	clear.SetInt(user.Clear_BlockID);
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
	read();
}    

User JsonUtility::getUser()					//获取用户信息
{
	User user;
	rapidjson::Value& val = m_doc["User"];
	rapidjson::Value& tem = val["UserName"];
	strcpy_s(user.UserName, tem.GetString());
	rapidjson::Value& bon = val["UserBonesNumber"];
	user.UserBonesNumber = bon.GetInt();
	rapidjson::Value& gold = val["UserGoldsNumber"];
	user.UserGoldsNumber = gold.GetInt();
	rapidjson::Value& health = val["UserHealth"];
	user.UserHealth = health.GetDouble();
	rapidjson::Value& attack = val["UserAttack"];
	user.UserAttack = attack.GetDouble();
	rapidjson::Value& defense = val["UserDefense"];
	user.UserDefense = defense.GetDouble();
	rapidjson::Value& speed = val["UserSpeed"];
	user.UserSpeed = speed.GetDouble();
	rapidjson::Value& strength = val["UserStrength"];
	user.UserStrength = strength.GetDouble();
	rapidjson::Value& skill = val["SkillID"];
	if (skill.IsArray())
	{
		for (int i = 0; i < skill.Capacity(); i++)
		{
			rapidjson::Value&first = skill[i];
			user.SkillID[i] = first.GetInt();
		}
	}
	rapidjson::Value& tool = val["ToolID"];
	if (tool.IsArray())
	{
		for (int i = 0; i < tool.Capacity(); i++)
		{
			rapidjson::Value&first = tool[i];
			user.ToolID[i] = first.GetInt();
		}
	}
	rapidjson::Value& equip = val["EquipID"];
	if (equip.IsArray())
	{
		for (int i = 0; i < equip.Capacity(); i++)
		{
			rapidjson::Value&first = equip[i];
			user.EquipID[i] = first.GetInt();
		}
	}
	rapidjson::Value& clear = val["Clear_BlockID"];
	if (clear.IsInt())
		user.Clear_BlockID = clear.GetInt();
	return user;
}
void JsonUtility::setUser(User user)		//设置用户信息
{
	write(user);
}
Block JsonUtility::getBlock(int ID)			//获取第i关卡信息
{
	Block block;
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& blo = val["Block"];
	if (ID >= blo.Capacity())
	{
		CCLOG("wrong :exceed the limit of monster ");
		return block;
	}
	rapidjson::Value& info = blo[ID];
	rapidjson::Value& mon_info = info["Monster"];
	if (mon_info.IsArray())
	{
		for (int i = 0; i < mon_info.Capacity(); i++)
		{
			rapidjson::Value& inf = mon_info[i];
			block.monster[i].monsterID = inf["MonsterID"].GetInt();
			block.monster[i].x = inf["X"].GetInt();
			block.monster[i].y = inf["Y"].GetInt();
		}
	}
	rapidjson::Value& block_info = info["BlockInfo"];
	strcpy_s(block.info, block_info.GetString());
	return block;
}
Monster_info JsonUtility::getMonster(int ID)		// 获取第i个怪物
{
	Monster_info info;
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& mon = val["Monster"];
	if (ID >= mon.Capacity())
	{
		CCLOG("wrong :exceed the limit of monster ");
		return info;
	}
	rapidjson::Value& mon_info = mon[ID];
	info.MonsterAttack = mon_info["MonsterAttack"].GetDouble();
	info.MonsterDefense = mon_info["MonsterDefense"].GetDouble();
	info.MonsterHealth = mon_info["MonsterHealth"].GetInt();
	strcpy_s(info.MonsterInfo, mon_info["MonsterInfo"].GetString());
	info.MonsterSpeed = mon_info["MonsterSpeed"].GetDouble();
	strcpy_s(info.MonsterType, mon_info["MonsterType"].GetString());
	return info;
}
Skill JsonUtility::getSkill(int ID)			//获取第i个技能
{
	Skill info;
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& skill = val["Skill"];
	if (ID >= skill.Capacity())
	{
		CCLOG("wrong :exceed the limit of skill ");
		return info;
	}
	rapidjson::Value& skill_info = skill[ID];
	info.SkillColdTime = skill_info["SkillColdTime"].GetDouble();
	info.SkillDamage = skill_info["SkillDamage"].GetDouble();
	strcpy_s(info.SkillInfo, skill_info["SkillInfo"].GetString());
	strcpy_s(info.SkillName, skill_info["SkillName"].GetString());
	strcpy_s(info.SkillType, skill_info["SkillType"].GetString());
	return info;
}
Equipment JsonUtility::getEquipment(int ID)	//获取第i个装备
{
	Equipment equip;
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& equi = val["Equipment"];
	if (ID >= equi.Capacity())
	{
		CCLOG("wrong :exceed the limit of equipment ");
		return equip;
	}
	rapidjson::Value& equi_info = equi[ID];
	strcpy_s(equip.EquipAttribute, equi_info["EquipAttribute"].GetString());
	equip.EquipAttributeValue = equi_info["EquipAttributeValue"].GetDouble();
	strcpy_s(equip.EquipInfo, equi_info["EquipInfo"].GetString());
	strcpy_s(equip.EquipName, equi_info["EquipName"].GetString());
	equip.EquipPrice = equi_info["EquipPrice"].GetInt();
	return equip;
}
Tool JsonUtility::getTool(int ID)			//获取第i个工具
{
	Tool info;
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& tool = val["Tool"];
	if (ID >= tool.Capacity())
	{
		CCLOG("wrong :exceed the limit of tool ");
		return info;
	}
	rapidjson::Value& tool_info = tool[ID];
	strcpy_s(info.ToolAttribute, tool_info["ToolAttribute"].GetString());
	info.ToolAttruibuteValue = tool_info["ToolAttruibuteValue"].GetDouble();
	strcpy_s(info.ToolInfo, tool_info["ToolInfo"].GetString());
	strcpy_s(info.ToolName, tool_info["ToolName"].GetString());
	info.ToolPrice = tool_info["ToolPrice"].GetInt();
	return info;
}
rapidjson::Document JsonUtility::getDocument()			// 获取m_doc
{
	return m_doc;
}

JsonUtility* JsonUtility::getInstance(){

	if (m_JsonUtility == nullptr)
	{
		m_JsonUtility = new JsonUtility();
		if (m_JsonUtility && m_JsonUtility->init()){
		}
		else
		{
			CC_SAFE_DELETE(m_JsonUtility);
		}

	}
	return m_JsonUtility;
}

bool JsonUtility::init()
{
	read();
	return true;
}
