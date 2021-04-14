#pragma once

#include "Component.h"

class __declspec(dllexport) ColliderComponent : public Component
{
public:
	bool CheckCollision(const ColliderComponent& collider) const;
};

