#pragma once

#include "Component.h"
#include "Vector2.h"
#include "Opus.h"

class Camera : public Component
{
public:
	OPUS_API void Update() override;
	OPUS_API void SetTarget(const std::shared_ptr<Entity>& target);
private:
	Vector2 offset_;
	std::weak_ptr<Entity> target_;
};

