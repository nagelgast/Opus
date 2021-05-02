#include "PlayerController.h"

#include "../Opus/Collision.h"
#include "../Opus/Input.h"

#include <cmath>
#include <utility>

#include "TargetingSystem.h"


PlayerController::PlayerController(std::shared_ptr<TargetingSystem> targeting_system, const float walk_speed,
                                   const float run_speed)
	: targeting_system_(std::move(targeting_system)),
	  walk_speed_(walk_speed),
	  run_speed_(run_speed)
{
}

void PlayerController::FixedUpdate()
{
	const auto dt = entity_->GetFixedDeltaTime();
	const auto& input = entity_->GetInput();

	const auto speed = dt * (input.run.held ? run_speed_ : walk_speed_);

	const auto pos = entity_->GetTransform().GetPosition();

	if (input.left_mouse.pressed)
	{
		target_ = targeting_system_->GetTarget();
		if (target_)
		{
			target_pos_ = target_->entity_->GetTransform().GetPosition();
		}
	}
	else if (input.left_mouse.held && !target_)
	{
		target_pos_ = input.mouse_world_pos;
		direct_control_ = false;
	}

	if (psh_->IsCasting())
	{
		return;
	}

	Vector2 movement;

	if (!direct_control_)
	{
		const auto delta = target_pos_ - pos;
		if (abs(delta.x) > 2 || abs(delta.y) > 2)
		{
			movement = delta.GetNormalized();
		}
		else if (target_)
		{
			target_->Interact();
			target_ = nullptr;
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
