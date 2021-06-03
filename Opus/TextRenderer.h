#pragma once

#include "Component.h"

class TextRenderer : public Component
{
public:
	void Awake() override;
	void SetText(const std::string& text) const;
	float GetWidth() const;
private:
	BaseEntityRenderer* renderer_ = nullptr;
};
