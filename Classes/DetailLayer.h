/************************************************************************/
/*
Name: DetailLayer
Author: xiaoDe
Function: show detail information for the entity that clicked
Date: 2015/4/27
*/
/************************************************************************/
#pragma once
#include "PopupLayer.h"
#include "cocos2d.h"
class Equipment;
enum class InventoryEnum;
class DetailLayer : public PopupLayer{
public:
	DetailLayer();
	~DetailLayer();
	static DetailLayer* create(Equipment*);
	static DetailLayer* create(InventoryEnum);
	CREATE_FUNC(DetailLayer);
	void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);
private:
	void __loadPicFromCSB(Equipment*);
	void __loadPicFromCSB(InventoryEnum type);
	virtual bool init();

	bool init(Equipment*);
	bool init(InventoryEnum);

	virtual void onEnter();
	//touchÊ±¼àÌý£¬ÆÁ±ÎÏòÏÂ´¥Ãþ
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


	void onUseButtonClicked(cocos2d::Ref*);
	void onEquipBuntonClicked(cocos2d::Ref*);
	void onBackupButtonClicked(cocos2d::Ref*);

	cocos2d::Ref* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;
	Equipment* m_equipment;
	InventoryEnum m_type;
};
