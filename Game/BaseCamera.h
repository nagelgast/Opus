#pragma once

#include "Vector2.h"

class BaseCamera
{
public:
	virtual const Vector2& GetPosition() = 0;
	virtual void SetPosition(const Vector2 position) = 0;
};