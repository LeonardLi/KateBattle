#include "StateUseSkill.h"
#include "StateAttack.h"
#include "MonsterFSM.h"
#include "Monster.h"
void StateUseSkill::execute(Monster* monster, EnumMsgType type){
	switch (type)
	{
	case EnumMsgType::en_Msg_WantToAttack:
		monster->attackSequence();
		monster->getFSM()->changeState(new StateAttack());
		break;

	default:
		break;
	}
}

void BossStateUseSkill::execute(Monster* monster, EnumMsgType type){
	switch (type)
	{
	case EnumMsgType::en_Msg_BossWantToAttack:
		monster->attackSequence();
		monster->getFSM()->changeState(new BossStateAttack());
		break;

	default:
		break;
	}
}