#include "PlayerAnimator.h"

#include "../Opus/Sprite.h"
#include "../Opus/SpriteRenderer.h"
#include "../Opus/Animation.h"

void PlayerAnimator::Awake()
{
	anim_ = &entity_->AddComponent(Animation(8, 1.f / 8));

	sr_ = &entity_->AddComponent(SpriteRenderer());
	UpdateSprite();
}

void PlayerAnimator::Update()
{
	// TODO Implement FSM instead of using bools

	if(attacking_)
	{
		return;
	}

	const auto new_pos = entity_->GetTransform().GetPosition();
	const auto delta_pos = new_pos - old_pos_;

	const auto moving_right = delta_pos.x > 0;
	const auto moving_hor = moving_right || delta_pos.x < 0;
	if(moving_hor && facing_right_ != moving_right)
	{
		facing_right_ = moving_right;
		UpdateSprite();
	}

	const auto moving_down = delta_pos.y > 0;
	const auto moving_ver = moving_down or delta_pos.y < 0;
	if(moving_ver && facing_down_ != moving_down)
	{
		facing_down_ = moving_down;
		UpdateSprite();
	}

	if((moving_hor || moving_ver) != moving_)
	{
		moving_ = !moving_;
		UpdateSprite();
	}
	old_pos_ = new_pos;
}

void PlayerAnimator::StartAttack()
{
	attacking_ = true;
	SetSprite("attack_02");
	anim_->Reset();
	anim_->Play();
}

void PlayerAnimator::StopAttack()
{
	attacking_ = false;
	UpdateSprite();
}

void PlayerAnimator::UpdateSprite() const
{
	sr_->SetMirrored(facing_right_ != facing_down_);

	// TODO Implement way to pre-load all the textures and sprites
	const std::string state = moving_ ? "run" : "idle";
	SetSprite(state + "_whit_sword");
}

void PlayerAnimator::SetSprite(const std::string& state) const
{
	const auto facing = facing_down_ ? "front" : "back";
	const Sprite sprite{ "Sprites/characters/" + state + "_" + facing + ".png", {0, 0, 48, 32}};
	sr_->SetSprite(sprite);
}
