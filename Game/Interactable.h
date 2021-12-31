#pragma once

#include "../Opus/Core.h"
#include "../Opus/Rect.h"

class Interactable final :
    public Component
{
public:
	Rect GetGlobalBounds() const;
	
	Event OnHoverEnter;
	Event OnHoverExit;
	Event OnPress;
	Event OnRelease;
	Event OnInteract;

private:
	Vector2 offset_ = {0,0};
	Vector2 size_ = {1,1};
};

