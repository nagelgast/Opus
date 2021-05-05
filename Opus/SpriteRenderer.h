#pragma once

#include "Component.h"
#include "Sprite.h"

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(Sprite sprite);
	void Start() override;
private:
	Sprite sprite_;
};
