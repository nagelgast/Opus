#pragma once

#include "../Opus/Core.h"

class Clickable :
    public Component
{
public:
	void Update() override;
	void OnClick();
};
