#pragma once

#include <string>

class Vector2;
class Entity;
enum class Shape;

class BaseEntityRenderer
{
public:
	virtual void SetSize(float width, float height) = 0;

	virtual void SetSprite(const std::string& path, int left, int top, int width, int height) = 0;
	virtual void SetShape(const Shape shape, float r, float g, float b, float a) = 0;

	Entity* entity_ = nullptr;
};
