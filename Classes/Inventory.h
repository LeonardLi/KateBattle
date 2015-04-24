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

class Inventory :public BackupEntity{

public:
	Inventory();
	~Inventory();
	static Inventory* create(InventoryEnum, int amount);
	void useInventory();

private:
	bool init(InventoryEnum, int amount);
	CC_SYNTHESIZE(InventoryEnum, m_type, InventoryType );
	CC_SYNTHESIZE(int, m_amount, Amount);
	CC_SYNTHESIZE(cocos2d::ui::Button*, m_button, InventoryButton);
	std::string m_IntroMsg;


};

