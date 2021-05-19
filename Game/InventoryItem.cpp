#include "InventoryItem.h"

#include <utility>

#include "Interactable.h"
#include "PlayerInventory.h"

InventoryItem::InventoryItem(std::shared_ptr<Item> item) : item_(std::move(item))
{
}

void InventoryItem::Start()
{
	auto interactable = entity_->GetComponent<Interactable>();
	interactable->OnClick += [this] {PickUp(); };
}

void InventoryItem::PickUp()
{
	// TODO Improve this, geez
	for (auto entity : entity_->GetEntities())
	{
		auto inventory = entity->GetComponent<PlayerInventory>();
		if (inventory)
		{
			inventory->PickUpItem(item_);
			entity_->Destroy();
		}
	}
}
