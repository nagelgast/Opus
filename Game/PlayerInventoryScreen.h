#pragma once

#include "..\Opus\Entity.h"
class Inventory;

class PlayerInventoryScreen :
    public Entity
{
public:
	void Awake() override;
	void Open();
	void Close();
private:
	bool is_open_;
	std::shared_ptr<Entity> background_;
	std::shared_ptr<Inventory> player_inventory_;
};

