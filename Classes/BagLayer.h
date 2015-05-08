/************************************************************************/
/*
Name: BagLayer
Author: xiaoDe
Function: show bag
Date: 2015/4/14
*/
/************************************************************************/
#pragma once
#include "cocos2d.h"
#include "PopupLayer.h"
#include "JsonUtility.h"
class Equipment;
enum class InventoryEnum;
class BagLayer : public PopupLayer{
public:
	static cocos2d::Scene* createScene(cocos2d::RenderTexture* sqr);
	static BagLayer* create();
	BagLayer();
	~BagLayer();

	void setCallbackFunc(cocos2d::Ref* target, cocos2d::SEL_CallFuncN callFun);

private:
	void __loadPicFromCSB();
	bool init();

	void __handleEquipmentDetailLayer(cocos2d::Node*);
	void __handleInventoryDetailLayer(cocos2d::Node*);
	virtual void onEnter();

	//touchÊ±¼àÌý£¬ÆÁ±ÎÏòÏÂ´¥Ãþ
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);


	void onInventoryClickedListener(cocos2d::Ref*);
	void onEquipmentClickedListener(cocos2d::Ref*);
	void onBackButtonClickListener(cocos2d::Ref*);
	void onAdvancedButtonClickListener(cocos2d::Ref*);

	bool __initFromFile();
	void __playAnimation(InventoryEnum);
	void __replaceEquipment(Equipment*);
    void __flushInventory();
	void __flushEquipment();
	void __flushHeroStatus();
	void __updateHeroData(Equipment* , bool);
	void __updateHeroData(Equipment* newEqu, Equipment* oldEqu);
	void __updateHeroData(InventoryEnum);

	cocos2d::Ref* m_callbackListener;
	cocos2d::SEL_CallFuncN m_callback;
	cocos2d::Vector<Equipment*> m_equipmentVec;
	cocos2d::EventListenerTouchOneByOne* m_listener;
	cocos2d::EventDispatcher* m_dispatcher;
	cocos2d::Node* m_baglayer;
};
