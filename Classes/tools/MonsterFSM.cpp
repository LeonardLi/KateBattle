#include "MonsterFSM.h"
#include "I_State.h"
#include "EnumMsgType.h"
USING_NS_CC;
#define NOTIFY NotificationCenter::getInstance()


MonsterFSM::~MonsterFSM(){
	NOTIFY->removeAllObservers(this);
	
};

MonsterFSM* MonsterFSM::createWithMonster(Monster* monster){
	MonsterFSM* fsm = new MonsterFSM();

	if (fsm&&fsm->initWithMonster(monster)){
		fsm->autorelease();
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
	NOTIFY->addObserver(this, callfuncO_selector(MonsterFSM::OnRecvWantToUseSkill),
		StringUtils::toString(EnumMsgType::en_Msg_WantToUseSkill), NULL);
	NOTIFY->addObserver(this, callfuncO_selector(MonsterFSM::OnRecvWantToAttack),
		StringUtils::toString(EnumMsgType::en_Msg_WantToAttack), NULL);
	return true;
}


void MonsterFSM::changeState(I_State* state){
	CC_SAFE_DELETE(mCurState);
	this->mCurState = state;
}

void MonsterFSM::OnRecvWantToUseSkill(Ref* obj){
	this->mCurState->execute(monster,EnumMsgType::en_Msg_WantToUseSkill);

}

void MonsterFSM::OnRecvWantToAttack(Ref* obj){
	this->mCurState->execute(monster, EnumMsgType::en_Msg_WantToAttack);
	
}