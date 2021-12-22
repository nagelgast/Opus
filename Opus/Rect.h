#pragma once

class Transform;
struct Vector2;

struct Rect
{
	Rect() : Rect(0,0,0,0)
	{
	}
	
	Rect(const float left, const float top, const float width, const float height) :
		left(left), top(top), width(width), height(height), right(left+width), bottom(top + height)
	{
	}
	
	Rect(const int left, const int top, const int width, const int height) : Rect(
		static_cast<float>(left), static_cast<float>(top),
		static_cast<float>(width), static_cast<float>(height))
	{
	}

	const float left;
	const float top;
	const float width;
	const float height;

	const float right;
	const float bottom;

	bool Contains(Vector2 point) const;

	Rect ConvertToGlobalSpace(Transform& transform) const;
};
