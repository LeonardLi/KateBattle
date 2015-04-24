#include "Inventory.h"

Inventory::Inventory(){

}

Inventory::~Inventory(){

}

Inventory* Inventory::create(InventoryEnum inventoryType, int amount){
	Inventory* inventory = new Inventory();
	if (inventory && inventory->init(inventoryType, amount))
	{
		inventory->autorelease();
	}
	else{
		CC_SAFE_DELETE(inventory);
	}
	return inventory;
}

bool Inventory::init(InventoryEnum type, int amount){
	if (!Node::init())
	{
		return false;
	}

	setInventoryType(type);
	setAmount(amount);
	
	return true;
		
}