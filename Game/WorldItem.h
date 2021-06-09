#pragma once

#include "Item.h"
#include "../Opus/Core.h"

class PlayerItemStorage;
class Interactable;

class WorldItem :
    public Entity
{
public:
	void Awake() override;
	void Initialize(std::unique_ptr<Item> item);
	void PickUp();
private:
	PlayerItemStorage* player_inventory_ = nullptr;
	
	std::unique_ptr<Item> item_;
};
