#include "MonsterManager.h"
#include "Monster.h"
USING_NS_CC;

MonsterManager* MonsterManager::createWithLevel(int iCurlevel){
	MonsterManager* monsterMgr = new MonsterManager();

	if (monsterMgr && monsterMgr->initWithLevel(iCurlevel))
	{
		monsterMgr->autorelease();
	}
	else
		CC_SAFE_DELETE(monsterMgr);

	return monsterMgr;
}

bool MonsterManager::initWithLevel(int iCurlevel){
	createMonsters(iCurlevel);
	return true;
}


Vector<Monster*> MonsterManager::getMonsterList(){
	return m_monsterList;
}

void MonsterManager::createMonsters(int iCurlevel){
	
	Monster* monster1 = Monster::create(Sprite::create("wolf.png"));
	monster1->setPosition(400, 400);
	m_monsterList.pushBack(monster1);
	this->addChild(monster1);
	//based on level to read json
	//m_monsterList.pushBack();

}