#pragma once

#include "../Opus/Core.h"
#include "../Opus/Rect.h"

class Interactable final :
    public Component
{
public:
	Rect GetGlobalBounds();
	
	Event OnHoverEnter;
	Event OnHoverExit;
	Event OnPress;
	Event OnRelease;
	Event OnInteract;
	Rect bounds_;
};

