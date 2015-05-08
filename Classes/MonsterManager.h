#ifndef __KateBattle__MonsterManager__
#define __KateBattle__MonsterManager__

#include "cocos2d.h"
class Monster;
enum class ScenarioEnum;
enum class SubScenarioEnum;

class MonsterManager:public cocos2d::Node{
public:
	
	cocos2d::Vector<Monster*> getMonsterList();
	cocos2d::Vector<Monster*> getMonsterScreen1List();
	cocos2d::Vector<Monster*> getMonsterScreen2List();
	static MonsterManager* createWithLevel(ScenarioEnum scenario, SubScenarioEnum subscenario);
	bool initWithLevel(ScenarioEnum scenario, SubScenarioEnum subscenario);
	void createMonsters(ScenarioEnum scenario, SubScenarioEnum subscenario);
	int getNotShowMonsterNumber();
	//virtual void update(float delta);


private:
	void __createMonsterLevel11();
	void __createMonsterLevel12();
	void __createMonsterLevel13();
	void __createMonsterLevel21();
	void __createMonsterLevel22();
	void __createMonsterLevel23();
	void __createMonsterLevel31();
	void __createMonsterLevel32();
	void __createMonsterLevel33();

public:
	cocos2d::Vector<Monster*> m_showedMonsterList;

private:
	cocos2d::Vector<Monster*> m_monsterList;
	cocos2d::Vector<Monster*> m_monsterScreen1List;
	cocos2d::Vector<Monster*> m_monsterScreen2List;

};

#endif