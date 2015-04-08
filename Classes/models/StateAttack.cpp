#include "StateAttack.h"
#include "StateUseSkill.h"
#include "MonsterFSM.h"
#include "Monster.h"
void StateAttack::execute(Monster* monster, EnumMsgType type){
	switch (type)
	{
	case EnumMsgType::en_Msg_WantToUseSkill:
		monster->getAttack();
		monster->getFSM()->changeState(new StateUseSkill());
		break;

	default:
		break;
	}

}