#pragma once

#include "../Opus/Core.h"

class SpriteRenderer;
class PlayerController;
class Animation;

class PlayerAnimator :
    public Component
{
public:
    void Awake() override;
    void Update() override;
private:
    void UpdateSprite() const;

    SpriteRenderer* sr_ = nullptr;
    Animation* anim_ = nullptr;

    Vector2 old_pos_;
    bool facing_right_ = true;
    bool facing_down_ = true;

    std::string state_;
};
