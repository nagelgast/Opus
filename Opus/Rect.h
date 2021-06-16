#pragma once

class Transform;
struct Vector2;

struct Rect
{
	Rect(const float top, const float left, const float width, const float height) :
		top(top), left(left), width(width), height(height), bottom(top+height), right(left+width)
	{
	}
	
	Rect(const int top, const int left, const int width, const int height) : Rect(
		static_cast<float>(top), static_cast<float>(left),
		static_cast<float>(width), static_cast<float>(height))
	{
	}

	const float top;
	const float left;
	const float width;
	const float height;

	const float bottom;
	const float right;

	bool Contains(Vector2 point) const;

	Rect ConvertToGlobalSpace(Transform& transform) const;
};
