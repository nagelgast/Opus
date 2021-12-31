#include "PlayerAnimator.h"

#include "../Opus/Sprite.h"
#include "../Opus/SpriteRenderer.h"
#include "../Opus/Animation.h"

void PlayerAnimator::Awake()
{
    // TODO Implement way to pre-load all the textures and sprites
    const Sprite sprite{ "Sprites/characters/idle_whit_sword_front.png", {0, 0, 48, 32} };
    const auto sr = entity_->AddComponent(SpriteRenderer());
    sr.SetSprite(sprite);

    anim_ = &entity_->AddComponent(Animation(8, 0.1f));
}

void PlayerAnimator::Start()
{
	sr_ = entity_->GetComponent<SpriteRenderer>();
}


void PlayerAnimator::Update()
{
	const auto new_pos = entity_->GetTransform().GetPosition();
	const auto delta_pos = new_pos - old_pos_;
	const auto moving_right = delta_pos.x > 0;
	const auto moving = moving_right || delta_pos.x < 0;

	if(moving && facing_right_ != moving_right)
	{
		facing_right_ = moving_right;
		sr_->SetMirrored(!moving_right);
	}

	old_pos_ = new_pos;
}
//
// void PlayerAnimator::StartMoving()
// {
// 	anim_->Play();
// 	auto x = entity_->GetTransform().GetPosition().x;
// 	// Mirror if we're moving into our opposite direction
// 	if (target_pos_.x < x != sr_->IsMirrored())
// 	{
// 		sr_->Mirror();
// 	}
// }
