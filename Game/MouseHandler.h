#pragma once
#include "Interactable.h"
#include "../Opus/Core.h"

class ScreenManager;
class MouseItem;
class PlayerController;

class MouseHandler : public Component
{
public:
	MouseHandler(std::shared_ptr<ScreenManager> screen_manager, std::shared_ptr<PlayerController> player_controller, std::shared_ptr<MouseItem> mouse_item);
	void Update() override;

private:
	void FindTarget();
	
	void HandleWorldPress();
	void HandleWorldHold();
	void HandleWorldRelease();
	void HandleWorldHover();

	void HandleScreenPress();
	void HandleScreenHold();
	void HandleScreenRelease();
	void HandleScreenHover();
	
	void HandleHover();

	void SetPlayerTargetPosition();
	void SetPlayerTargetInteractable();

	std::shared_ptr<ScreenManager> screen_manager_;
	std::shared_ptr<PlayerController> player_controller_;
	std::shared_ptr<MouseItem> mouse_item_;
	
	std::shared_ptr<Interactable> target_;
	std::shared_ptr<Interactable> previous_target_;

	Vector2 mouse_position_;

	bool is_world_space_hold_ = false;
	bool in_world_space_ = false;
	bool holding_item_ = false;

	// TODO Update when implementing towns/hideouts
	const bool can_drop_items_ = true;
};

