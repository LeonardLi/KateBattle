//
//  JsonUtility.h
//  KateBattle
//
//  Created by Leonard on 15/3/20.
//
//

#ifndef __KateBattle__JsonUtility__
#define __KateBattle__JsonUtility__
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "cocos2d.h"
#pragma execution_character_set("utf-8") 
class Equipment;
enum class EquipmentType;
struct EquipID
{
	int ID;
	EquipmentType Style;
	double Defense;
	double Blood;
	double Attack;
	double Intelligence;
	double AttackRate;
	double MoveRate;
	bool Used;
};
struct User								//玩家用户信息
{
	std::string UserName;
	int UserBonesNumber;
	int UserGoldsNumber;
	int EquipmentNumber;      //change 
	double UserHealth;
	double UserCulHealth;
	double UserAttack;
	double UserDefense;
	double UserIntelligence;
	double UserAttackRate;
	double UserMoveRate;
	int SkillID[3];
	int ToolID[6];               //修改
	EquipID Equip[24];			//修改
	int Clear_BlockID[3][3];
};
struct Monster_location{				//每关怪兽信息
	int monsterID;
	double x;
	double y;
};

struct Store              //每关商店信息
{
	double X;
	double Y;
	int ToolID[10];
	int EquipID[10];
};

struct Block							//每关卡信息
{
	Monster_location monster[9];
	std::string info;
	std::string BlockName;
	Store store;
};

struct EquipmentInfo{						//装备信息
	std::string EquipName;
	std::string EquipInfo;
	double Defense;								//增加了八个元素
	double Blood;
	double Attack;
	double Intelligence;
	double AttackRate;
	double MoveRate;
	std::string EquipAddress;
	int EquipPrice;
	EquipmentType EquipType;
};

struct Tool								//工具信息
{
	std::string ToolName;
	std::string ToolAddress;
	std::string ToolInfo;
	std::string ToolEffect;
	int ToolPrice;
};

struct Skill							//技能信息
{
	std::string SkillName;
	std::string SkillType;
	double SkillDamage;
	std::string SkillInfo;
	double SkillColdTime;
};

struct Monster_info						   //怪物信息
{
	std::string MonsterType;
	int MonsterHealth;
	double MonsterSpeed;
	double MonsterDefense;
	double MonsterAttack;
	std::string MonsterInfo;
};

class JsonUtility{
public:

	void setUser();		//设置用户信息
	Block getBlock(int ID);			//获取第i关卡信息
	Monster_info getMonster(int ID);		// 获取第i个怪物
	Skill getSkill(int ID);			//获取第i个技能
	EquipmentInfo getEquipment(int ID);	//获取第i个装备
	Tool getTool(int ID);			//获取第i个工具
	Store getStore(int ID);			//获取第i关的商店的信息
	rapidjson::Document getDocument();			// 获取m_doc
	virtual bool init();
	static JsonUtility* getInstance();
public:
	User user;
private:
    User getUser();					//获取用户信息 
	void _read();                   //初始化时读取json文件
	void _write();		   //将修改的内容写入json文件
	

private:
	static JsonUtility* m_JsonUtility;
	rapidjson::Document m_doc;
};





#endif /* defined(__KateBattle__JsonUtility__) */
