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

	bool IsOpen() const;

	std::shared_ptr<Inventory> player_inventory_;
private:
	bool is_open_;
	std::shared_ptr<Entity> background_;
};

