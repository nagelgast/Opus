#include "WorldItem.h"

#include <iostream>



#include "InventoryItem.h"
#include "Targetable.h"
#include "TargetingSystem.h"
#include "../Opus/ShapeRenderer.h"

WorldItem::WorldItem(const Item& item) : item_(std::make_shared<Item>(item))
{
}

void WorldItem::Start()
{
	targetable_ = entity_->GetComponent<Targetable>();
	targetable_->SetHandler([this] {PickUp();});
}

void WorldItem::PickUp()
{
	std::cout << "Test";
	entity_->Instantiate(InventoryItem(item_));
	entity_->Destroy();
}
