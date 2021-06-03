#pragma once

#include "Component.h"

class TextRenderer : public Component
{
public:
	void Awake() override;
	void SetText(const std::string& text) const;
private:
	BaseEntityRenderer* renderer_ = nullptr;
};
