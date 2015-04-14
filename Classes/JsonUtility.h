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

struct User								//����û���Ϣ
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

struct Monster_location{				//ÿ�ع�����Ϣ
	int monsterID;
	int x;
	int y;
};

struct Block							//ÿ�ؿ���Ϣ
{
	Monster_location monster[9];
	char info[40];
};

struct Equipment{						//װ����Ϣ
	char EquipName[20];
	char EquipInfo[50];
	char EquipAttribute[20];
	double EquipAttributeValue;
	int EquipPrice;
};

struct Tool								//������Ϣ
{
	char ToolName[20];
	char ToolInfo[50];
	char ToolAttribute[20];
	double ToolAttruibuteValue;
	int ToolPrice;
};

struct Skill							//������Ϣ
{
	char SkillName[20];
	char SkillType[20];
	double SkillDamage;
	char SkillInfo[50];
	double SkillColdTime;
};

struct Monster_info						   //������Ϣ
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
	User getUser();					//��ȡ�û���Ϣ
	void setUser(User user);		//�����û���Ϣ
	Block getBlock(int ID);			//��ȡ��i�ؿ���Ϣ
	Monster_info getMonster(int ID);		// ��ȡ��i������
	Skill getSkill(int ID);			//��ȡ��i������
	Equipment getEquipment(int ID);	//��ȡ��i��װ��
	Tool getTool(int ID);			//��ȡ��i������
	rapidjson::Document getDocument();			// ��ȡm_doc
	virtual bool init();
	static JsonUtility* getInstance();
	
	
private:
	void read();                   //��ʼ��ʱ��ȡjson�ļ�
	void write(User user);		   //���޸ĵ�����д��json�ļ�

private:
	static JsonUtility* m_JsonUtility;
	rapidjson::Document m_doc;
};





#endif /* defined(__KateBattle__JsonUtility__) */
