#include "SFMLCamera.h"

const Vector2& SFMLCamera::GetPosition()
{
	return position_;
}

void SFMLCamera::SetPosition(const Vector2 position)
{
	position_ = position;
}
