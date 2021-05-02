#include "PlayerSkillHandler.h"

#include "FireballSkill.h"

#include "../Opus/Input.h"

PlayerSkillHandler::PlayerSkillHandler(FireballSkill& active_skill)
	: remaining_cast_time_(),
	  active_skill_(active_skill)
{
}

void PlayerSkillHandler::Update()
{
	if (remaining_cast_time_ > 0)
	{
		remaining_cast_time_ -= entity_->GetDeltaTime();
		if(remaining_cast_time_ <= 0)
		{
			active_skill_.Trigger(*this);
		}
	}

	if (remaining_cast_time_ <= 0 && entity_->GetInput().right_mouse.pressed)
	{
		remaining_cast_time_ = active_skill_.GetCastTime();
	}
}

bool PlayerSkillHandler::IsCasting() const
{
	return remaining_cast_time_ > 0;
}
