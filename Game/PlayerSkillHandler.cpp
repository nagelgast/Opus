#include "PlayerSkillHandler.h"

#include "Entity.h"
#include "FireballSkill.h"
#include "Input.h"

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
