//
//  JsonUtility.cpp
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//
#include "cocos2d.h"
#include "JsonUtility.h"
#include "Equipment.h"
#include "Inventory.h"
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

void JsonUtility::_write()    //写是数组类型的元素，只写json数组的大小
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
	rapidjson::Value& logNum = val["LogNumber"];
	logNum.SetInt(user.LogNumber);
	rapidjson::Value& health = val["UserHealth"];
	health.SetDouble(user.UserHealth);
	rapidjson::Value& attack = val["UserAttack"];
	attack.SetDouble(user.UserAttack);
	rapidjson::Value& defense = val["UserDefense"];
	defense.SetDouble(user.UserDefense);
	rapidjson::Value& Intelligence = val["UserIntelligence"];
	Intelligence.SetDouble(user.UserIntelligence);
	rapidjson::Value& AttackRate = val["UserAttackRate"];
	AttackRate.SetDouble(user.UserAttackRate);
	rapidjson::Value& MoveRate = val["UserMoveRate"];
	MoveRate.SetDouble(user.UserMoveRate);
	rapidjson::Value& EquiNumber = val["EquipmentNumber"];
	EquiNumber.SetInt(user.EquipmentNumber);
	rapidjson::Value& skill = val["SkillID"];
	if (skill.IsArray())
	{
		for (int i = 0; i < skill.Capacity(); i++)
		{
			
			rapidjson::Value&first = skill[i];
			first.SetInt(user.SkillID[i]);
		}
	}
	rapidjson::Value& tool = val["ToolID"];
	if (tool.IsArray())
	{
		for (int i = 0; i < tool.Capacity(); i++)
		{
			rapidjson::Value&first = tool[i];
			first.SetInt(user.ToolID[i]);
		}
	}
	rapidjson::Value& equip = val["EquipID"];           //need to modify
	if (equip.IsArray())
	{
		int length = user.EquipmentNumber;
		for (int i = 0; i < length; i++)
		{
			rapidjson::Value&first = equip[i];
			rapidjson::Value&scenod = first["ID"];
			scenod.SetInt(user.Equip[i].ID);
			rapidjson::Value&scenod1 = first["Style"];
			scenod1.SetInt(static_cast<int>(user.Equip[i].Style));               //类型的转换
			rapidjson::Value&scenod2 = first["Used"];
			scenod2.SetBool(user.Equip[i].Used);
			rapidjson::Value&scenod3 = first["Defense"];
			scenod3.SetDouble(user.Equip[i].Defense);
			rapidjson::Value&scenod4 = first["Blood"];
			scenod4.SetDouble(user.Equip[i].Blood);
			rapidjson::Value&scenod5 = first["Attack"];
			scenod5.SetDouble(user.Equip[i].Attack);
			rapidjson::Value&scenod6 = first["Intelligence"];
			scenod6.SetDouble(user.Equip[i].Intelligence);
			rapidjson::Value&scenod7 = first["AttackRate"];
			scenod7.SetDouble(user.Equip[i].AttackRate);
			rapidjson::Value&scenod8 = first["MoveRate"];
			scenod8.SetDouble(user.Equip[i].MoveRate);
		}
	}
	rapidjson::Value& clear = val["Clear_BlockID"];
	for (int i = 0; i < 3; i++)
	{
		rapidjson::Value&first = clear[i];
		for (int j = 0; j < 3; j++)
		{
			rapidjson::Value&secons = first[j];
			secons.SetInt(user.Clear_BlockID[i][j]);
		}
	}
	//clear.SetInt(user.Clear_BlockID);
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
	rapidjson::Value& logNum = val["LogNumber"];
	user.LogNumber = logNum.GetInt();
	rapidjson::Value& health = val["UserHealth"];
	user.UserHealth = user.UserCulHealth  = health.GetDouble();
	rapidjson::Value& attack = val["UserAttack"];
	user.UserAttack = attack.GetDouble();
	rapidjson::Value& defense = val["UserDefense"];
	user.UserDefense = defense.GetDouble();
	rapidjson::Value& Intelligence = val["UserIntelligence"];
	user.UserIntelligence = Intelligence.GetDouble();
	rapidjson::Value& AttackRate = val["UserAttackRate"];
	user.UserAttackRate = AttackRate.GetDouble();
	rapidjson::Value& MoveRate = val["UserMoveRate"];
	user.UserMoveRate = MoveRate.GetDouble();
	rapidjson::Value& EquipmentNum = val["EquipmentNumber"];
	user.EquipmentNumber = EquipmentNum.GetInt();
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
			user.ToolID[i] = first.GetInt();
		}
	}
	rapidjson::Value& equip = val["EquipID"];                      //need to modify
	if (equip.IsArray())
	{
		int length = user.EquipmentNumber;
		for (i = 0; i < length; i++)
		{
			rapidjson::Value&first = equip[i];
			rapidjson::Value&scenod = first["ID"];
			user.Equip[i].ID = scenod.GetInt();
			rapidjson::Value&scenod1 = first["Style"];
			user.Equip[i].Style = static_cast<EquipmentType>(scenod1.GetInt());
			rapidjson::Value&scenod2 = first["Used"];
			user.Equip[i].Used = scenod2.GetBool();
			rapidjson::Value&scenod3 = first["Defense"];
			user.Equip[i].Defense = scenod3.GetDouble();
			rapidjson::Value&scenod4 = first["Blood"];
			user.Equip[i].Blood = scenod4.GetDouble();
			rapidjson::Value&scenod5 = first["Attack"];
			user.Equip[i].Attack = scenod5.GetDouble();
			rapidjson::Value&scenod6 = first["Intelligence"];
			user.Equip[i].Intelligence = scenod6.GetDouble();
			rapidjson::Value&scenod7 = first["AttackRate"];
			user.Equip[i].AttackRate = scenod7.GetDouble();
			rapidjson::Value&scenod8 = first["MoveRate"];
			user.Equip[i].MoveRate = scenod8.GetDouble();
		}
	}
	rapidjson::Value& clear = val["Clear_BlockID"];
	for (i = 0; i < 3; i++)
	{
		rapidjson::Value&first = clear[i];
		for (int j = 0; j < 3; j++)
		{
			rapidjson::Value&secons = first[j];
			user.Clear_BlockID[i][j] = secons.GetInt();
		}
	}
	return user;
}

void JsonUtility::setUser()		//设置用户信息
{
	_write();
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

EquipmentInfo JsonUtility::getEquipment(int ID)	//获取第i个装备
{
	EquipmentInfo equip = {};
	rapidjson::Value& val = m_doc["Data"];
	rapidjson::Value& equi = val["Equipment"];
	if (ID >= equi.Capacity())
	{
		CCAssert(false, "wrong :exceed the limit of equipment");
	}
	rapidjson::Value& equi_info = equi[ID];
	equip.EquipInfo = equi_info["EquipInfo"].GetString();
	equip.EquipName = equi_info["EquipName"].GetString();
	equip.EquipPrice = equi_info["EquipPrice"].GetInt();
	equip.Attack = equi_info["Attack"].GetDouble();
	equip.AttackRate = equi_info["AttackRate"].GetDouble();
	equip.Blood = equi_info["Blood"].GetDouble();
	equip.Defense = equi_info["Defense"].GetDouble();
	equip.EquipAddress = equi_info["EquipAddress"].GetString();
	equip.EquipType = static_cast<EquipmentType>(equi_info["EquipType"].GetInt());
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
	info.ToolAddress = tool_info["ToolAddress"].GetString();
	info.ToolInfo = tool_info["ToolInfo"].GetString();
	info.ToolEffect = tool_info["ToolEffect"].GetString();
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
	user = getUser();
	return true;
}
