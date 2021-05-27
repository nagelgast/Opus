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
private:
	bool is_open_ = false;
	Entity* background_ = nullptr;
};
