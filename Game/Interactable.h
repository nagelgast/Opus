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
	Rect bounds_ {0,0,1,1};
};

