#pragma once

#include "Component.h"
#include "Vector2.h"

class Camera : public Component
{
public:
	void Update() override;
	void SetTarget(const std::shared_ptr<Entity>& target);
private:
	Vector2 offset_;
	std::weak_ptr<Entity> target_;
};

