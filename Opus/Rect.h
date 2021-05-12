#pragma once

struct Vector2;

struct Rect
{
	float top;
	float left;
	float width;
	float height;

	bool Contains(Vector2 point) const;
};

