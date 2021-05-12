#include "Interactable.h"

#include <iostream>


#include "../Opus/Input.h"
#include "PlayerController.h"

Interactable::~Interactable()
{
	if(active_interactable_ == this)
	{
		active_interactable_ = nullptr;
	}
}

void Interactable::Update()
{
	const auto& input = entity_->GetInput();

	const auto pos = entity_->GetTransform().GetPosition();
	const auto offset = entity_->GetTransform().GetOrigin();
	if (bounds_.Contains(input.mouse_screen_pos - pos + offset))
	{
		if (!hovering_)
		{
			hovering_ = true;
			active_interactable_ = this;
			std::cout << "HoverEnter";
			OnHoverEnter();
		}

		if(input.left_mouse.pressed)
		{
			OnClick();
			std::cout << "Click";
		}
	}
	else if (hovering_)
	{
		hovering_ = false;
		if(active_interactable_ == this)
		{
			active_interactable_ = nullptr;
		}
		std::cout << "HoverExit";
		OnHoverExit();
	}
}

Interactable* Interactable::GetActiveInteractable()
{
	return active_interactable_;
}

Interactable* Interactable::active_interactable_;
