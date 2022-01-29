#pragma once

#include "Component.h"
#include "Sprite.h"

class SpriteRenderer : public Component
{
public:
	void Awake() override;
	void SetSprite(const Sprite& sprite) const;
	void ResetSprite() const;
	void SetMirrored(bool value) const;
private:
	BaseEntityRenderer* renderer_ = nullptr;
};
