#include "Equipment.h"


Equipment::Equipment() :
m_id(0),
m_style(EquipmentType::Default),
m_defense(0.0f),
m_blood(0.0f),
m_attack(0.0f),
m_intelligence(0.0f),
m_attackRate(0.0f),
m_moveRate(0.0f),
m_isUsed(false)
{
}

Equipment::~Equipment(){

}

Equipment* Equipment::create(const std::string& filename){
	Equipment* instance = new Equipment();
	if (instance && instance->initWithFile(filename))
	{
		instance->autorelease();
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return instance;
}

