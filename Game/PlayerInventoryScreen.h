#pragma once

#include "..\Opus\Entity.h"
class PlayerInventoryScreen :
    public Entity
{
public:
	void Awake() override;
	void Open();
	void Close();
private:
	std::shared_ptr<Entity> background_;
};

