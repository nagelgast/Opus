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

    void StartAttack();
    void StopAttack();
    void SetSprite(const std::string& state) const;
private:
    void UpdateSprite() const;

    SpriteRenderer* sr_ = nullptr;
    Animation* anim_ = nullptr;

    Vector2 old_pos_;
    bool moving_ = false;
    bool facing_right_ = true;
    bool facing_down_ = true;
    bool attacking_ = false;
};
