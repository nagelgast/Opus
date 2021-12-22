#include "PlayerController.h"

#include "../Opus/Collision.h"
#include "../Opus/Input.h"
#include "../Opus/Animation.h"
#include "../Opus/SpriteRenderer.h"

#include <cmath>

#include "Interactable.h"
#include "PlayerSkillHandler.h"

PlayerController::PlayerController(const float walk_speed,
                                   const float run_speed)
	: walk_speed_(walk_speed),
	  run_speed_(run_speed)
{
}

void PlayerController::Start()
{
	psh_ = entity_->GetComponent<PlayerSkillHandler>();
	anim_ = entity_->GetComponent<Animation>();
	sr_ = entity_->GetComponent<SpriteRenderer>();
}

void PlayerController::FixedUpdate()
{
	const auto dt = entity_->GetFixedDeltaTime();
	const auto& input = Game::GetInput();

	const auto speed = dt * (input.run.held ? run_speed_ : walk_speed_);

	const auto pos = entity_->GetTransform().GetPosition();

	if (psh_->IsCasting())
	{
		return;
	}

	Vector2 movement;

	const auto delta = target_pos_ - pos;
	if (abs(delta.x) > 2 || abs(delta.y) > 2)
	{
		movement = delta.GetNormalized();
	}
	else
	{
		// Reached target position
		// TODO Keep track of when player is moving so we don't call this every frame
		anim_->Reset();

		if (target_)
		{
			target_->OnInteract();
			ClearTarget();
		}
	}

	movement.x *= speed;
	movement.y *= speed;
	entity_->GetTransform().Move(movement);
}

void PlayerController::SetTarget(const Vector2 position)
{
	target_pos_ = position;
	StartMoving();
}

void PlayerController::SetTarget(Interactable& target)
{
	target_ = &target;
	target_pos_ = target_->entity_->GetTransform().GetPosition();
	StartMoving();
}

void PlayerController::ClearTarget()
{
	target_ = nullptr;
}

void PlayerController::StartMoving()
{
	anim_->Play();
	auto x = entity_->GetTransform().GetPosition().x;
	// Mirror if we're moving into our opposite direction
	if (target_pos_.x < x != sr_->IsMirrored())
	{
		sr_->Mirror();
	}
}