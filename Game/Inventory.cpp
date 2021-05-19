#include "Inventory.h"


#include "Interactable.h"
#include "InventoryItem.h"
#include "../Opus/SpriteRenderer.h"

void Inventory::AddItem(const std::shared_ptr<Item>& item)
{
	auto entity = entity_->Instantiate();
	auto interactable = entity->AddComponent(Interactable());
	interactable->bounds_ = {0,0, 40, 120};
	
	auto inventory_item = entity->AddComponent(InventoryItem(item));
	auto sr = entity->AddComponent(SpriteRenderer());
	sr->SetSprite(item->GetSprite(), false);
	
	auto& transform = entity->GetTransform();
	transform.SetSize(40, 120);
	transform.SetParent(&entity_->GetTransform());
	transform.SetLocalPosition({0, 0});
	
	items_[0] = inventory_item;
}
