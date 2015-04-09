#include "StateAttack.h"
#include "StateUseSkill.h"
#include "MonsterFSM.h"
#include "Monster.h"
void StateAttack::execute(Monster* monster, EnumMsgType type){
	switch (type)
	{
	case EnumMsgType::en_Msg_WantToUseSkill:
		monster->useSkillSequence();
		monster->getFSM()->changeState(new StateUseSkill());
		break;

	default:
		break;
	}
}

void BossStateAttack::execute(Monster* monster, EnumMsgType type){
	switch (type)
	{
	case EnumMsgType::en_Msg_BossWantToUseSkill:
		monster->useSkillSequence();
		monster->getFSM()->changeState(new BossStateUseSkill());
		break;

	default:
		break;
	}
}