#pragma once

#include "Component.h"
#include "Sprite.h"

class SpriteRenderer : public Component
{
public:
	void Start() override;
	void SetSprite(const Sprite& sprite, bool world_space = true);
	void ResetSprite();
private:
	BaseEntityRenderer* renderer_ = nullptr;
	Sprite sprite_;

	bool world_space_;
};
