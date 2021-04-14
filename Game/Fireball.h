#pragma once

#include "../Opus/Entity.h"

class Fireball final : public Entity
{
public:
	explicit Fireball(const Vector2& start_pos, const Vector2& target_pos);
};

