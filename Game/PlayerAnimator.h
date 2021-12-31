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
    void Start() override;
    void Update() override;
private:
    SpriteRenderer* sr_ = nullptr;
    Animation* anim_ = nullptr;

    Vector2 old_pos_;
    bool facing_right_ = true;
};
