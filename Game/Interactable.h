#pragma once

#include "../Opus/Core.h"
#include "../Opus/Rect.h"

class Interactable final :
    public Component
{
public:
	~Interactable() override;
	
	void Update() override;
	Event OnHoverEnter;
	Event OnHoverExit;
	Event OnClick;
	Event OnInteract;
	Rect bounds_;

	//TODO Replace this with a system
	static Interactable* GetActiveInteractable();
private:
	static Interactable* active_interactable_;
	bool hovering_ = false;
};

