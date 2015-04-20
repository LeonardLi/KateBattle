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

void JsonUtility::_read()
{
	std::string filePath = FileUtils::getInstance()->fullPathForFilename("groot.json");
	std::string contentStr = FileUtils::getInstance()->getStringFromFile(filePath);
	m_doc.Parse<rapidjson::ParseFlag::kParseDefaultFlags>(contentStr.c_str());
	if (m_doc.HasParseError())
	{
		CCAssert(false,"GetParseError");
		CCLOG("GetParseError %s\n", m_doc.GetParseError());
	}
	if (!m_doc.IsObject())
	{
		CCAssert(false, "no object!");
	}
	if (!m_doc.HasMember("User"))
	{
		CCAssert(false, "No User!");
	}
	if (!m_doc.HasMember("Data"))
	{
		CCAssert(false, "No Data!");
	}
}

void JsonUtility::_write(User user)    //写是数组类型的元素，只写json数组的大小
{
	if (!m_doc.IsObject())
	{
		CCAssert(false, "NO OBJECT IN WRITING!");
	}
	rapidjson::Value& val = m_doc["User"];
	rapidjson::Value& tem = val["UserName"];
	tem.SetString(user.UserName.c_str());

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
			if (user.ToolID[i][0] == -1)
				break;
			rapidjson::Value&first = tool[i];
			for (int j = 0; j < 2; j++)
			{
				rapidjson::Value&secons = first[j];
				secons.SetInt(user.ToolID[i][j]);
			}
		}
		for (; i < tool.Capacity(); i++)
		{
			rapidjson::Value&first = tool[i];
			for (int j = 0; j < 2; j++)
			{
				rapidjson::Value&secons = first[j];
				secons.SetInt(-1);
			}
		}
	}
	rapidjson::Value& equip = val["EquipID"];
	if (equip.IsArray())
	{
		for (i = 0; i < equip.Capacity(); i++)
		{
			if (user.EquipID[i][0] == -1)
				break;
			rapidjson::Value&first = equip[i];
			for (int j = 0; j < 2; j++)
			{
				rapidjson::Value&secons = first[j];
				secons.SetInt(user.EquipID[i][j]);
			}
		}
		for (; i < equip.Capacity(); i++)
		{
			rapidjson::Value&first = equip[i];
			for (int j = 0; j < 2; j++)
			{
				rapidjson::Value&secons = first[j];
				secons.SetInt(-1);
			}
		}
	}
	rapidjson::Value& clear = val["Clear_BlockID"];
	clear.SetInt(user.Clear_BlockID);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer< rapidjson::StringBuffer > writer(buffer);
	m_doc.Accept(writer);
	const char * lin = buffer.GetString();
	log("GROOT1:%s", lin);
	FILE* file = fopen("groot.json", "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	
	_read();
}    

User JsonUtility::getUser()					//获取用户信息
{
	User user = {};
	rapidjson::Value& val = m_doc["User"];
	rapidjson::Value& tem = val["UserName"];
	user.UserName = tem.GetString();
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
	int i;
	if (tool.IsArray())
	{
		for (i = 0; i < tool.Capacity(); i++)
		{
			rapidjson::Value&first = tool[i];
			for (int j = 0; j < 2; j++)
			{
				rapidjson::Value&secons = first[j];
				user.ToolID[i][j] = secons.GetInt();
			}
		}
	}
	rapidjson::Value& equip = val["EquipID"];
	if (equip.IsArray())
	{
		for (i = 0; i < equip.Capacity(); i++)
		{
			rapidjson::Value&first = equip[i];
			for (int j = 0; j < 2; j++)
			{
				rapidjson::Value&secons = first[j];
				user.EquipID[i][j] = secons.GetInt();
			}
		}
	}
	rapidjson::Value& clear = val["Clear_BlockID"];
	if (clear.IsInt())
		user.Clear_BlockID = clear.GetInt();
	return user;
}

void JsonUtility::setUser(User user)		//设置用户信息
{
	_write(user);
}

Block JsonUtility::getBlock(int ID)			//获取第i关卡信息
{
	Block block = {};
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& blo = val["Block"];
	if (ID >= blo.Capacity())
	{
		CCAssert(false, "wrong :exceed the limit of monster ");	
	}
	rapidjson::Value& info = blo[ID];
	rapidjson::Value& mon_info = info["Monster"];
	if (mon_info.IsArray())
	{
		for (int i = 0; i < mon_info.Capacity(); i++)
		{
			rapidjson::Value& inf = mon_info[i];
			block.monster[i].monsterID = inf["MonsterID"].GetInt();
			block.monster[i].x = inf["X"].GetDouble();
			block.monster[i].y = inf["Y"].GetDouble();
		}
	}
	rapidjson::Value& block_info = info["BlockInfo"];
	block.info = block_info.GetString();
	rapidjson::Value& block_name = info["BlockName"];
	block.BlockName = block_name.GetString();
	block.store = getStore(ID);
	return block;
}

Monster_info JsonUtility::getMonster(int ID)		// 获取第i个怪物
{
	Monster_info info = {};
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& mon = val["Monster"];
	if (ID >= mon.Capacity())
	{
		CCAssert(false, "wrong :exceed the limit of monster ");
	}
	rapidjson::Value& mon_info = mon[ID];
	info.MonsterAttack = mon_info["MonsterAttack"].GetDouble();
	info.MonsterDefense = mon_info["MonsterDefense"].GetDouble();
	info.MonsterHealth = mon_info["MonsterHealth"].GetInt();
	info.MonsterInfo = mon_info["MonsterInfo"].GetString();
	info.MonsterSpeed = mon_info["MonsterSpeed"].GetDouble();
	info.MonsterType = mon_info["MonsterType"].GetString();
	return info;
}

Skill JsonUtility::getSkill(int ID)			//获取第i个技能
{
	Skill info = {};
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& skill = val["Skill"];
	if (ID >= skill.Capacity())
	{
		CCAssert(false, "wrong :exceed the limit of skill");
	}
	rapidjson::Value& skill_info = skill[ID];
	info.SkillColdTime = skill_info["SkillColdTime"].GetDouble();
	info.SkillDamage = skill_info["SkillDamage"].GetDouble();
	info.SkillInfo = skill_info["SkillInfo"].GetString();
	info.SkillName = skill_info["SkillName"].GetString();
	info.SkillType = skill_info["SkillType"].GetString();
	return info;
}

Equipment JsonUtility::getEquipment(int ID)	//获取第i个装备
{
	Equipment equip = {};
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& equi = val["Equipment"];
	if (ID >= equi.Capacity())
	{
		CCAssert(false, "wrong :exceed the limit of equipment");
	}
	rapidjson::Value& equi_info = equi[ID];
	equip.EquipAttribute = equi_info["EquipAttribute"].GetString();
	equip.EquipAttributeValue = equi_info["EquipAttributeValue"].GetDouble();
	equip.EquipInfo = equi_info["EquipInfo"].GetString();
	equip.EquipName = equi_info["EquipName"].GetString();
	equip.EquipPrice = equi_info["EquipPrice"].GetInt();
	return equip;
}

Tool JsonUtility::getTool(int ID)			//获取第i个工具
{
	Tool info = {};
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& tool = val["Tool"];
	if (ID >= tool.Capacity())
	{
		CCAssert(false, "wrong :exceed the limit of tool");
	}
	rapidjson::Value& tool_info = tool[ID];
	info.ToolAttribute = tool_info["ToolAttribute"].GetString();
	info.ToolAttruibuteValue = tool_info["ToolAttruibuteValue"].GetDouble();
	info.ToolInfo = tool_info["ToolInfo"].GetString();
	info.ToolName = tool_info["ToolName"].GetString();
	info.ToolPrice = tool_info["ToolPrice"].GetInt();
	return info;
}

Store JsonUtility::getStore(int ID)		//获取第i关的商店的信息
{
	Store store = {};
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& stor = val["Store"];
	rapidjson::Value& store_info = stor[ID];
	rapidjson::Value& store_Tool = store_info["ToolID"];
	for (int i = 0; i < store_Tool.Capacity();i++)
	{
		store.ToolID[i] = store_Tool[i].GetInt();
	}
	rapidjson::Value& store_Equip = store_info["EquipID"];
	for (int i = 0; i < store_Equip.Capacity(); i++)
	{
		store.EquipID[i] = store_Equip[i].GetInt();
	}
	rapidjson::Value& store_X = store_info["X"];
	store.X = store_X.GetDouble();
	rapidjson::Value& store_Y = store_info["Y"];
	store.Y = store_Y.GetDouble();
	return store;
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
	_read();
	return true;
}
