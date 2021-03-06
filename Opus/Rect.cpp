#include "pch.h"
#include "Rect.h"

#include "Transform.h"
#include "Vector2.h"

bool Rect::Contains(const Vector2 point) const
{
	if (point.x < left) return false;
	if (point.x > left + width) return false;
	if (point.y < top) return false;
	if (point.y > top + height) return false;

	return true;
}
