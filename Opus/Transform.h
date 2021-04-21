#pragma once
#include "Component.h"
#include "Vector2.h"

class Transform final : public Component
{
public:
	OPUS_API void SetSize(float width, float height);
	OPUS_API Vector2 GetPosition() const;
	OPUS_API void SetPosition(float x, float y);
	OPUS_API void SetPosition(Vector2 position);
	OPUS_API void Move(Vector2 offset);
	OPUS_API Vector2 GetOrigin() const;
	OPUS_API Vector2 GetScale() const;
private:
	Vector2 position_;
	Vector2 rotation_;
	Vector2 scale_;

	Vector2 origin_;
};
