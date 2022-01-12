#pragma once
#include "Vector2.h"

struct Particle
{
	Vector2 position;
	Vector2 velocity;
	float lifetime = 0;
};
