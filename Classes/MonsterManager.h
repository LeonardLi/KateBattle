#ifndef __KateBattle__MonsterManager__
#define __KateBattle__MonsterManager__

#include "cocos2d.h"
class Monster;

class MonsterManager:public cocos2d::Node{
public:
	
	cocos2d::Vector<Monster*> getMonsterList();
	cocos2d::Vector<Monster*> getMonsterScreen1List();
	cocos2d::Vector<Monster*> getMonsterScreen2List();
	static MonsterManager* createWithLevel(int iCurlevel);
	bool initWithLevel(int iCurlevel);
	void createMonsters(int iCurlevel);
	int getNotShowMonsterNumber();
	//virtual void update(float delta);



public:
	cocos2d::Vector<Monster*> m_showedMonsterList;

private:
	cocos2d::Vector<Monster*> m_monsterList;
	cocos2d::Vector<Monster*> m_monsterScreen1List;
	cocos2d::Vector<Monster*> m_monsterScreen2List;

};

#endif