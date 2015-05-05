//
//  Iventory.h
//  KateBattle
//
//  Created by Lmc on 15/3/31.
//
//
#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Entity.h"

enum class InventoryEnum{
	sBlood,
	bBlood,
	jifengyaoshui,
	fengkuangyaoshui,
	mianyiyaoshui,
	xianlingyaoshui,
	Default
};

class Inventory :public cocos2d::Node{
public:
	Inventory();
	~Inventory();
    CREATE_FUNC(Inventory);

private:
	CC_SYNTHESIZE(InventoryEnum, m_type, InventoryType );
	CC_SYNTHESIZE(int, m_amount, Amount);
    CC_SYNTHESIZE(cocos2d::ui::Button*, m_button, InventoryButton)
	std::string m_IntroMsg;
};

