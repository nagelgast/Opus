#pragma once

#include "Component.h"
#include "Vector2.h"

class Camera : public Component
{
public:
	void Update() override;
	void SetTarget(Entity& target);
private:
	Vector2 offset_;
	Entity* target_;
};

