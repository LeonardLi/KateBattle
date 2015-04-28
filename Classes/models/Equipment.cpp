#include "Equipment.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

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

Equipment* Equipment::create(const std::string& normalImage, 
							 const std::string& selectedImage /* = "" */, 
							 const std::string& disableImage /* = "" */, 
							 TextureResType texType /* = TextureResType::LOCAL */)
{
	Equipment* btn = new (std::nothrow) Equipment;
	if (btn && btn->init(normalImage, selectedImage, disableImage,texType))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return btn;
}


