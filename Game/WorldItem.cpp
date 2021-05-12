#include "WorldItem.h"

#include <utility>

#include "../Opus/ShapeRenderer.h"

#include "Inventory.h"
#include "Interactable.h"

WorldItem::WorldItem(std::shared_ptr<Interactable> interactable, const Item& item) :
	item_(std::make_shared<Item>(item)), interactable_(std::move(interactable))
{
}

void WorldItem::Start()
{
	interactable_->OnInteract += [this] { PickUp(); };
}

void WorldItem::PickUp()
{
	// TODO Improve this, geez
	for (auto entity : entity_->GetEntities())
	{
		auto inventory = entity->GetComponent<Inventory>();
		if (inventory)
		{
			inventory->AddItem(item_);
			entity_->Destroy();
		}
	}
}
