#pragma once

#include "../Opus/Core.h"

class PlayerInventory;
class Item;
class Interactable;

class WorldItem :
    public Entity
{
public:
	void Awake() override;
	void PickUp();
	std::shared_ptr<Item> item_;
private:
	std::shared_ptr<Interactable> interactable_;
	std::shared_ptr<PlayerInventory> inventory_;
};
