#pragma once

#include "Component.h"
#include "Sprite.h"

class SpriteRenderer : public Component
{
public:
	void Start() override;
	void SetSprite(const Sprite& sprite);
private:
	BaseEntityRenderer* renderer_ = nullptr;
	Sprite sprite_;
};
