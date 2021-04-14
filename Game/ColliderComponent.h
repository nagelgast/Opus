#pragma once

#include "Component.h"

class ColliderComponent : public Component
{
public:
	bool CheckCollision(const ColliderComponent& collider) const;
};

