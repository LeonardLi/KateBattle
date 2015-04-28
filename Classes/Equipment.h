//
//  Equipment.h
//  KateBattle
//
//  Created by Lmc on 15/3/31.
//
//

#pragma once
#include "Entity.h"
enum class EquipmentType{
	Hat,
	Aniversary,
	Cloth,
	Shoes,
	Default
};
class Equipment :public BackupEntity{
public:
    CREATE_FUNC(Equipment);
    static Equipment* create(const std::string&);
	Equipment();
	~Equipment();
	
private:
	CC_SYNTHESIZE(int, m_id, EquipmentID);
	CC_SYNTHESIZE(EquipmentType, m_style, EquipmentStyle);
	CC_SYNTHESIZE(double, m_defense, Denfense);
	CC_SYNTHESIZE(double, m_blood, Blood);
	CC_SYNTHESIZE(double, m_attack, Attack);
	CC_SYNTHESIZE(double, m_intelligence, Intelligence);
	CC_SYNTHESIZE(double, m_attackRate, AttackRate);
	CC_SYNTHESIZE(double, m_moveRate, MoveRate);
	CC_SYNTHESIZE(bool, m_isUsed, Used);
};
