#include "PlayerController.h"

#include <cmath>

#include "../Opus/Collision.h"
#include "../Opus/Entity.h"
#include "../Opus/Input.h"
#include "../Opus/Transform.h"

PlayerController::PlayerController(const float walk_speed, const float run_speed)
:	walk_speed_(walk_speed),
	run_speed_(run_speed)
{
}

void PlayerController::Update()
{
	const auto dt = entity_->GetDeltaTime();
	const auto& input = entity_->GetInput();

	const auto speed = dt * (input.run.held ? run_speed_ : walk_speed_);
	
	const auto pos = entity_->GetTransform().GetPosition();

	Vector2 movement;

	if(input.move.held)
	{
		target_pos_ = input.mouse_world_pos;
		direct_control_ = false;
	}

	if(!direct_control_)
	{
		const auto delta = target_pos_ - pos;
		if(abs(delta.x) > 2 || abs(delta.y) > 2)
		{
			movement = delta.GetNormalized();
		}
	}
	
	if (input.right.held)
	{
		movement.x++;
		direct_control_ = true;
	}
	if (input.left.held)
	{
		movement.x--;
		direct_control_ = true;
	}
	if (input.up.held)
	{
		movement.y--;
		direct_control_ = true;
	}
	if (input.down.held)
	{
		movement.y++;
		direct_control_ = true;
	}

	movement.x *= speed;
	movement.y *= speed;
	entity_->GetTransform().Move(movement);
}
