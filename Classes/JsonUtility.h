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
struct User								//����û���Ϣ
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
	int ToolID[6];               //�޸�
	EquipID Equip[24];			//�޸�
	int Clear_BlockID[3][3];
};
struct Monster_location{				//ÿ�ع�����Ϣ
	int monsterID;
	double x;
	double y;
};

struct Store              //ÿ���̵���Ϣ
{
	double X;
	double Y;
	int ToolID[10];
	int EquipID[10];
};

struct Block							//ÿ�ؿ���Ϣ
{
	Monster_location monster[9];
	std::string info;
	std::string BlockName;
	Store store;
};

struct EquipmentInfo{						//װ����Ϣ
	std::string EquipName;
	std::string EquipInfo;
	double Defense;								//�����˰˸�Ԫ��
	double Blood;
	double Attack;
	double Intelligence;
	double AttackRate;
	double MoveRate;
	std::string EquipAddress;
	int EquipPrice;
	EquipmentType EquipType;
};

struct Tool								//������Ϣ
{
	std::string ToolName;
	std::string ToolAddress;
	std::string ToolInfo;
	std::string ToolEffect;
	int ToolPrice;
};

struct Skill							//������Ϣ
{
	std::string SkillName;
	std::string SkillType;
	double SkillDamage;
	std::string SkillInfo;
	double SkillColdTime;
};

struct Monster_info						   //������Ϣ
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

	void setUser();		//�����û���Ϣ
	Block getBlock(int ID);			//��ȡ��i�ؿ���Ϣ
	Monster_info getMonster(int ID);		// ��ȡ��i������
	Skill getSkill(int ID);			//��ȡ��i������
	EquipmentInfo getEquipment(int ID);	//��ȡ��i��װ��
	Tool getTool(int ID);			//��ȡ��i������
	Store getStore(int ID);			//��ȡ��i�ص��̵����Ϣ
	rapidjson::Document getDocument();			// ��ȡm_doc
	virtual bool init();
	static JsonUtility* getInstance();
public:
	User user;
private:
    User getUser();					//��ȡ�û���Ϣ 
	void _read();                   //��ʼ��ʱ��ȡjson�ļ�
	void _write();		   //���޸ĵ�����д��json�ļ�
	

private:
	static JsonUtility* m_JsonUtility;
	rapidjson::Document m_doc;
};





#endif /* defined(__KateBattle__JsonUtility__) */
