#include "StateAttack.h"
#include "StateUseSkill.h"
#include "MonsterFSM.h"
#include "Monster.h"
void StateAttack::execute(Monster* monster, EnumMsgType type){
	switch (type)
	{
	case EnumMsgType::en_Msg_WantToUseSkill:
		monster->getFSM()->changeState(new StateUseSkill());
		monster->useSkillSequence();		
		break;

	default:
		break;
	}
}

void BossStateAttack::execute(Monster* monster, EnumMsgType type){
	switch (type)
	{
	case EnumMsgType::en_Msg_BossWantToUseSkill:
		monster->getFSM()->changeState(new BossStateUseSkill());
		monster->useSkillSequence();		
		break;

	default:
		break;
	}
}