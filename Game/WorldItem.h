#pragma once

#include "Item.h"
#include "../Opus/Core.h"

class PlayerInventory;
class Interactable;

class WorldItem :
    public Entity
{
public:
	void Awake() override;
	void Initialize(std::unique_ptr<Item> item);
	void PickUp();
private:
	std::unique_ptr<Item> item_;
};
