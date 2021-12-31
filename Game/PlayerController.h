#pragma once

#include "../Opus/Core.h"

class SpriteRenderer;
class PlayerSkillHandler;
class Interactable;

class PlayerController final :
    public Component
{
public:
	PlayerController(float walk_speed, float run_speed);
	void Start() override;
	void FixedUpdate() override;

	void SetTarget(Interactable& target);
	void SetTarget(Vector2 position);
	void ClearTarget();

private:
	PlayerSkillHandler* psh_ = nullptr;
	SpriteRenderer* sr_ = nullptr;
	Interactable* target_ = nullptr;
	Vector2 target_pos_ = {0,0};
	float walk_speed_ = 0;
	float run_speed_ = 0;
};
