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


		// TODO Refactor this
		if(input.right_mouse.released)
		{
			moving_to_target_ = true;
		}

		if(moving_to_target_ && input.left_mouse.pressed)
		{
			moving_to_target_ = false;
		}

		if (input.right_mouse.held)
		{
			target_position_ = input.mouse_world_pos;
		}
		
		if (input.right_mouse.held || moving_to_target_)
		{
			if (Vector2::IsInRange(target_position_, entity_->GetTransform().GetPosition(),
			                       active_skill_->GetRange()))
			{
				std::cout << "Casting\n";
				remaining_cast_time_ = active_skill_->GetCastTime();
				moving_to_target_ = false;
			}
		}
	}
}

bool PlayerSkillHandler::IsCasting() const
{
	return remaining_cast_time_ > 0;
}

Vector2 PlayerSkillHandler::GetTargetPosition() const
{
	return target_position_;
}
