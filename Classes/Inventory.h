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
	InventoryAmount
};

class Inventory :public cocos2d::ui::Button{
public:
	Inventory();
	~Inventory();

private:
	CC_SYNTHESIZE(InventoryEnum, m_type, InventoryType );
	CC_SYNTHESIZE(int, m_amount, Amount);
	std::string m_IntroMsg;
};

