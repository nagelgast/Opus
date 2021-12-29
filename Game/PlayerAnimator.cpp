#include "PlayerAnimator.h"

#include "../Opus/Sprite.h"
#include "../Opus/SpriteRenderer.h"
#include "../Opus/Animation.h"


void PlayerAnimator::Awake()
{
    const Sprite sprite{ "Sprites/chars/gabe/gabe-idle-run.png", {0, 0, 24, 24} };
    const auto sr = entity_->AddComponent(SpriteRenderer());
    sr.SetSprite(sprite);

    entity_->AddComponent(Animation(7, 0.1));
}
