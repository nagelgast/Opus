#pragma once

#include "../Opus/Core.h"

class PlayerInventoryScreen;

class ScreenManager : public Component
{
public:
	void Awake() override;
	void Update() override;

	bool CheckIsInScreenSpace(Vector2 position) const;

	PlayerInventoryScreen* player_inventory_screen_ = nullptr;
};
