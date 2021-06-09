#include "PlayerSkillHandler.h"

#include <iostream>


#include "ActiveSkill.h"
#include "../Opus/Input.h"

PlayerSkillHandler::~PlayerSkillHandler()
{
	delete active_skill_;
}

void PlayerSkillHandler::SetActiveSkill(ActiveSkill* active_skill)
{
	delete active_skill_;
	active_skill_ = active_skill;
}

void PlayerSkillHandler::Update()
{
	if(!active_skill_) return;
	
	if (remaining_cast_time_ > 0)
	{
		remaining_cast_time_ -= entity_->GetDeltaTime();
		if (remaining_cast_time_ <= 0)
		{
			std::cout << "Cast\n";
			active_skill_->Cast();
		}
	}
	else
	{
		const auto& input = entity_->GetInput();

		if (input.right_mouse.held)
		{
			if (Vector2::IsInRange(input.mouse_world_pos, entity_->GetTransform().GetPosition(),
			                       active_skill_->GetRange()))
			{
				std::cout << "Casting\n";
				remaining_cast_time_ = active_skill_->GetCastTime();
			}
			else
			{
				// TODO Move towards mouse position
			}
		}
	}
}

bool PlayerSkillHandler::IsCasting() const
{
	return remaining_cast_time_ > 0;
}
