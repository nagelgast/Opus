#pragma once

class Transform;
struct Vector2;

struct Rect
{
	Rect(const float top, const float left, const float width, const float height) :
		top(top), left(left), width(width), height(height)
	{
	}
	
	Rect(const int top, const int left, const int width, const int height) :
		top(static_cast<float>(top)), left(static_cast<float>(left)),
		width(static_cast<float>(width)), height(static_cast<float>(height))
	{
	}

	float top;
	float left;
	float width;
	float height;

	bool Contains(Vector2 point) const;

	Rect ConvertToGlobalSpace(Transform& transform) const;
};
