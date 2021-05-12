#include "WorldItem.h"

#include <iostream>



#include "Inventory.h"
#include "MouseItem.h"
#include "Targetable.h"
#include "TargetingSystem.h"
#include "../Opus/ShapeRenderer.h"

WorldItem::WorldItem(const Item& item) : item_(std::make_shared<Item>(item))
{
}

void WorldItem::Start()
{
	targetable_ = entity_->GetComponent<Targetable>();
	targetable_->OnInteract += [this] {PickUp(); };
}

void WorldItem::PickUp()
{
	std::cout << "Test";

	// TODO Improve this, geez
	for (auto entity : entity_->GetEntities())
	{
		auto inventory = entity->GetComponent<Inventory>();
		if(inventory)
		{
			inventory->AddItem(item_);
			entity_->Destroy();
		}
	}
}
