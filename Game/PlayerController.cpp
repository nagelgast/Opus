#include "PlayerController.h"

#include "../Opus/Collision.h"
#include "../Opus/Input.h"

#include <cmath>

#include "Interactable.h"

PlayerController::PlayerController(const float walk_speed,
                                   const float run_speed)
	: walk_speed_(walk_speed),
	  run_speed_(run_speed)
{
}

void PlayerController::Start()
{
	psh_ = entity_->GetComponent<PlayerSkillHandler>();
}

void PlayerController::FixedUpdate()
{
	const auto dt = entity_->GetFixedDeltaTime();
	const auto& input = entity_->GetInput();

	const auto speed = dt * (input.run.held ? run_speed_ : walk_speed_);

	const auto pos = entity_->GetTransform().GetPosition();

	if (psh_->IsCasting())
	{
		return;
	}

	if (target_)
	{
		target_pos_ = target_->entity_->GetTransform().GetPosition();
	}

	Vector2 movement;

	const auto delta = target_pos_ - pos;
	if (abs(delta.x) > 2 || abs(delta.y) > 2)
	{
		movement = delta.GetNormalized();
	}
	else if (target_)
	{
		target_->OnInteract();
		target_ = nullptr;
	}

	movement.x *= speed;
	movement.y *= speed;
	entity_->GetTransform().Move(movement);
}

void PlayerController::SetTarget(const Vector2 position)
{
	target_pos_ = position;
}

void PlayerController::SetTarget(Interactable& target)
{
	target_ = &target;
}

void PlayerController::ClearTarget()
{
	target_ = nullptr;
}