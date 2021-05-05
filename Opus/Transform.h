#pragma once
#include "Component.h"
#include "Vector2.h"

class Transform final : public Component
{
public:
	void SetSize(float width, float height);
	Vector2 GetPosition() const;
	void SetPosition(float x, float y);
	void SetPosition(Vector2 position);
	void Move(Vector2 offset);
	Vector2 GetOrigin() const;
	Vector2 GetScale() const;
private:
	Vector2 position_;
	Vector2 rotation_;
	Vector2 scale_;

	Vector2 origin_;
};
