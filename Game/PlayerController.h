#pragma once

#include "../Opus/Core.h"

class SpriteRenderer;
class PlayerSkillHandler;
class Animation;
class Interactable;

class PlayerController final :
    public Component
{
public:
	PlayerController(float walk_speed, float run_speed);
	void Start() override;
	void FixedUpdate() override;

	void SetTarget(Vector2 position);
	void SetTarget(Interactable& target);
	void ClearTarget();

private:
	void StartMoving();

	PlayerSkillHandler* psh_ = nullptr;
	Animation* anim_ = nullptr;
	SpriteRenderer* sr_ = nullptr;
	Interactable* target_ = nullptr;
	Vector2 target_pos_ = {0,0};
	float walk_speed_ = 0;
	float run_speed_ = 0;

	bool direct_control_ = false;
};
