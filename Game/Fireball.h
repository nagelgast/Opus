#pragma once

#include "../Opus/Core.h"

class Fireball final : public Entity
{
public:
	explicit Fireball(const Vector2& start_pos, const Vector2& target_pos);
};

