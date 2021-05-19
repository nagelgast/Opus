#pragma once

#include "Item.h"
#include "../Opus/Core.h"

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
};
