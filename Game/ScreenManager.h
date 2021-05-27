#pragma once

#include "../Opus/Entity.h"

class PlayerInventoryScreen;

class ScreenManager : public Entity
{
public:
	void Awake() override;
	void Update() override;

	bool CheckIsInScreenSpace(Vector2 position) const;

	PlayerInventoryScreen* player_inventory_screen_ = nullptr;
};
