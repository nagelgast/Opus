#include "PlayerSkillHandler.h"

#include "../Opus/Entity.h"
#include "FireballSkill.h"
#include "../Opus/Input.h"

PlayerSkillHandler::PlayerSkillHandler(FireballSkill& active_skill) : active_skill_(active_skill)
{
}

void PlayerSkillHandler::Update()
{
	if (entity_->GetInput().action.pressed)
	{
		active_skill_.Trigger(*this);
	}
}
