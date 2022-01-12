#pragma once
#include "Interactable.h"
#include "../Opus/Core.h"

class ScreenManager;
class MouseSlot;
class PlayerController;

class MouseHandler : public Component
{
public:
	MouseHandler(ScreenManager& screen_manager, PlayerController& player_controller, MouseSlot& mouse_item);
	void Update() override;

private:
	void FindTarget();
	
	void HandleWorldPress();
	void HandleWorldHold() const;
	void HandleWorldRelease();
	void HandleWorldHover();

	void HandleScreenPress() const;
	void HandleScreenHold();
	void HandleScreenRelease() const;
	void HandleScreenHover();
	
	void HandleHover();

	void SetPlayerTargetPosition() const;
	void SetPlayerTargetInteractable() const;

	ScreenManager* screen_manager_ = nullptr;
	PlayerController* player_controller_ = nullptr;
	MouseSlot* mouse_item_ = nullptr;
	
	Interactable* target_ = nullptr;
	Interactable* previous_target_ = nullptr;

	Vector2 mouse_position_;

	bool is_world_space_hold_ = false;
	bool in_world_space_ = false;
	bool holding_item_ = false;
};

