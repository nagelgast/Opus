#include "MouseHandler.h"

#include "MouseSlot.h"
#include "PlayerController.h"
#include "ScreenManager.h"
#include "../Opus/Input.h"

MouseHandler::MouseHandler(ScreenManager& screen_manager, PlayerController& player_controller, MouseSlot& mouse_item) :
	screen_manager_(&screen_manager), player_controller_(&player_controller), mouse_item_(&mouse_item)
{
}

void MouseHandler::Update()
{
	in_world_space_ = !screen_manager_->CheckIsInScreenSpace(mouse_position_);
	holding_item_ = mouse_item_->HasItem();

	const auto& input = Game::GetInput();
	const auto pressed = input.left_mouse.pressed;
	const auto held = input.left_mouse.held;
	const auto released = input.left_mouse.released;
	mouse_position_ = input.mouse_screen_pos;

	if (in_world_space_)
	{
		// TODO Handle decently for all skill keys
		if (pressed || input.right_mouse.pressed)
		{
			HandleWorldPress();
		}
		else if (held || input.right_mouse.held)
		{
			if (is_world_space_hold_)
			{
				HandleWorldHold();
			}
		}
		else if (released || input.right_mouse.released)
		{
			HandleWorldRelease();
		}
		else
		{
			HandleHover();
		}
	}
	else
	{
		if (pressed)
		{
			HandleScreenPress();
		}
		else if (held)
		{
			if (!is_world_space_hold_)
			{
				HandleScreenHold();
			}
		}
		else if (released)
		{
			HandleScreenRelease();
		}
		else
		{
			HandleHover();
		}
	}
}

void MouseHandler::FindTarget()
{
	previous_target_ = target_;

	// TODO Optimize this
	auto entities = Game::GetWorldSpace().GetEntities();
	std::vector<Interactable*> interactables;
	for (const auto& entity : entities)
	{
		auto* interactable = entity->GetComponent<Interactable>();
		if (interactable)
		{
			interactables.push_back(interactable);
		}
	}

	std::vector<Interactable*> targets;

	for (const auto& interactable : interactables)
	{
		auto bounds = interactable->GetGlobalBounds();
		if (bounds.Contains(mouse_position_))
		{
			targets.push_back(interactable);
		}
	}

	if (!targets.empty())
	{
		// TODO Pick front-most target
		target_ = targets[0];
	}
	else
	{
		target_ = nullptr;
	}
}

void MouseHandler::HandleWorldPress()
{
	// TODO Handle skills bound to lmb
	// TODO Handle enemy targeting dependent on skill

	// Check if we're holding an item we can drop
	const auto dropped_item = mouse_item_->TryDrop(player_controller_->entity_->GetTransform().GetPosition());

	// If we dropped an item, treat this as a screen click
	is_world_space_hold_ = !dropped_item;

	// If we did not drop an item, update player target
	if (!dropped_item)
	{
		if (target_)
		{
			SetPlayerTargetInteractable();
		}
		else
		{
			player_controller_->ClearTarget();
			SetPlayerTargetPosition();
		}
	}
}

void MouseHandler::HandleWorldHold() const
{
	SetPlayerTargetPosition();
}

void MouseHandler::HandleWorldRelease()
{
	is_world_space_hold_ = false;
}

void MouseHandler::HandleWorldHover()
{
	if (holding_item_) return;

	HandleHover();
}

void MouseHandler::HandleScreenPress() const
{
	if (target_)
	{
		target_->OnPress();
	}
}

void MouseHandler::HandleScreenHold()
{
	HandleHover();
}

void MouseHandler::HandleScreenRelease() const
{
	if (target_)
	{
		target_->OnRelease();
	}
}

void MouseHandler::HandleScreenHover()
{
	HandleHover();
}


void MouseHandler::HandleHover()
{
	FindTarget();

	if (target_ != previous_target_)
	{
		if (previous_target_)
		{
			previous_target_->OnHoverExit();
		}
		if (target_)
		{
			target_->OnHoverEnter();
		}
	}
}

void MouseHandler::SetPlayerTargetPosition() const
{
	player_controller_->SetTarget(mouse_position_);
}

void MouseHandler::SetPlayerTargetInteractable() const
{
	player_controller_->SetTarget(*target_);
}
