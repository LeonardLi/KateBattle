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
#pragma execution_character_set("utf-8") 

struct User								//玩家用户信息
{
	char UserName[50];
	int UserBonesNumber;
	int UserGoldsNumber;
	double UserHealth;
	double UserAttack;
	double UserDefense;
	double UserSpeed;
	double UserStrength;
	int SkillID[10];
	int ToolID[10];
	int EquipID[10];
	int Clear_BlockID;
};

struct Monster_location{				//每关怪兽信息
	int monsterID;
	int x;
	int y;
};

struct Block							//每关卡信息
{
	Monster_location monster[9];
	char info[40];
};

struct Equipment{						//装备信息
	char EquipName[20];
	char EquipInfo[50];
	char EquipAttribute[20];
	double EquipAttributeValue;
	int EquipPrice;
};

struct Tool								//工具信息
{
	char ToolName[20];
	char ToolInfo[50];
	char ToolAttribute[20];
	double ToolAttruibuteValue;
	int ToolPrice;
};

struct Skill							//技能信息
{
	char SkillName[20];
	char SkillType[20];
	double SkillDamage;
	char SkillInfo[50];
	double SkillColdTime;
};

struct Monster_info						   //怪物信息
{
	char MonsterType[20];
	int MonsterHealth;
	double MonsterSpeed;
	double MonsterDefense;
	double MonsterAttack;
	char MonsterInfo[50];
};

class JsonUtility{
public:
	User getUser();					//获取用户信息
	void setUser(User user);		//设置用户信息
	Block getBlock(int ID);			//获取第i关卡信息
	Monster_info getMonster(int ID);		// 获取第i个怪物
	Skill getSkill(int ID);			//获取第i个技能
	Equipment getEquipment(int ID);	//获取第i个装备
	Tool getTool(int ID);			//获取第i个工具
	rapidjson::Document getDocument();			// 获取m_doc
	virtual bool init();
	static JsonUtility* getInstance();
	
	
private:
	void read();                   //初始化时读取json文件
	void write(User user);		   //将修改的内容写入json文件

private:
	static JsonUtility* m_JsonUtility;
	rapidjson::Document m_doc;
};





#endif /* defined(__KateBattle__JsonUtility__) */
