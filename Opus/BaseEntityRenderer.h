#pragma once

struct Rect;
struct Color;
struct Sprite;
struct Vector2;
class Entity;
enum class Shape;

class BaseEntityRenderer
{
public:
	virtual ~BaseEntityRenderer() = default;
	
	virtual void SetSprite(const Sprite sprite) = 0;
	virtual void SetTextureRect(const Rect& rect) = 0;
	virtual void SetShape(const Shape& shape) = 0;
	virtual void SetText(const char* text) = 0;

	virtual Rect GetTextureRect() const = 0;
	virtual float GetWidth() = 0;

	virtual void SetColor(const Color& color) = 0;

	virtual void SetMirrored(const bool& value) = 0;

	virtual void Reset() = 0;

	Entity* entity_ = nullptr;

	bool in_world_space_ = true;
};
