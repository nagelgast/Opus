#pragma once

struct Sprite;
struct Vector2;
class Entity;
enum class Shape;

class BaseEntityRenderer
{
public:
	virtual ~BaseEntityRenderer() = default;
	virtual void SetSize(float width, float height) = 0;

	virtual void SetSprite(Sprite sprite) = 0;
	virtual void SetShape(const Shape shape, float r, float g, float b, float a) = 0;

	virtual void Reset() = 0;

	Entity* entity_ = nullptr;

	bool in_world_space_ = true;
};
