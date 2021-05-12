#pragma once

#include "Item.h"
#include "../Opus/Core.h"

class Interactable;

class WorldItem :
    public Component
{
public:
	explicit WorldItem(std::shared_ptr<Interactable> interactable, const Item& item);
	void Start() override;
	void PickUp();
	std::shared_ptr<Item> item_;
private:
	std::shared_ptr<Interactable> interactable_;
};
