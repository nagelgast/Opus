#pragma once

#include "../Opus/Entity.h"

class PlayerInventoryScreen;

class ScreenManager : public Entity
{
public:
	void Awake() override;
	void Update() override;
private:
	std::shared_ptr<PlayerInventoryScreen> player_inventory_screen_;
};
