#include "MonsterFSM.h"
#include "I_State.h"
#include "StateAttack.h"
#include "StateUseSkill.h"
USING_NS_CC;
#define NOTIFY NotificationCenter::getInstance()


MonsterFSM::~MonsterFSM(){
	NOTIFY->removeAllObservers(this);
	
};

MonsterFSM* MonsterFSM::createWithMonster(Monster* monster){
	MonsterFSM* fsm = new MonsterFSM();

	if (fsm&&fsm->initWithMonster(monster)){
	
	}
	else{
		CC_SAFE_DELETE(fsm);
		fsm = nullptr;
	}
	return fsm;
}

bool MonsterFSM::initWithMonster(Monster* monster){
	this->mCurState = NULL;
	this->monster = monster;
	this->state = toUseSkill;
	NOTIFY->addObserver(this, callfuncO_selector(MonsterFSM::OnRecvWantToUseSkill),
		StringUtils::toString(static_cast<int>(EnumMsgType::en_Msg_WantToUseSkill)), NULL);
	NOTIFY->addObserver(this, callfuncO_selector(MonsterFSM::OnRecvWantToAttack),
		StringUtils::toString(static_cast<int>(EnumMsgType::en_Msg_WantToAttack)), NULL);
	NOTIFY->addObserver(this, callfuncO_selector(MonsterFSM::OnRecvBossWantToUseSkill),
		StringUtils::toString(static_cast<int>(EnumMsgType::en_Msg_BossWantToUseSkill)), NULL);
	NOTIFY->addObserver(this, callfuncO_selector(MonsterFSM::OnRecvBossWantToAttack),
		StringUtils::toString(static_cast<int>(EnumMsgType::en_Msg_BossWantToAttack)), NULL);


	return true;
}


void MonsterFSM::changeState(I_State* state){
	CC_SAFE_DELETE(mCurState);
	this->mCurState = state;
}

void MonsterFSM::OnRecvWantToUseSkill(Ref* obj){
	this->state = toUseSkill;
	this->mCurState->execute(monster,EnumMsgType::en_Msg_WantToUseSkill);

}

void MonsterFSM::OnRecvWantToAttack(Ref* obj){
	this->state = toAttack;
	this->mCurState->execute(monster, EnumMsgType::en_Msg_WantToAttack);
	
}
void MonsterFSM::OnRecvBossWantToUseSkill(Ref* obj){
	this->state = BosstoUseSkill;
	this->mCurState->execute(monster, EnumMsgType::en_Msg_BossWantToUseSkill);

}

void MonsterFSM::OnRecvBossWantToAttack(Ref* obj){
	this->state = BossToAttack;
	this->mCurState->execute(monster, EnumMsgType::en_Msg_BossWantToAttack);

}

int MonsterFSM::getState(){
	return this->state;
}