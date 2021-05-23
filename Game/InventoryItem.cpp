#include "InventoryItem.h"

#include "Inventory.h"
#include "Interactable.h"
#include "Item.h"
#include "../Opus/SpriteRenderer.h"

void InventoryItem::Awake()
{
	interactable_ = AddComponent(Interactable());
	sr_ = AddComponent(SpriteRenderer());

}

void InventoryItem::Initialize(const std::shared_ptr<Item>& item, const std::vector<int>& slot_indices)
{
	item_ = item;
	slot_indices_ = slot_indices;

	const auto width = static_cast<float>(kInventorySlotSize * item->width);
	const auto height = static_cast<float>(kInventorySlotSize * item->height);
	
	interactable_->bounds_ = { 0, 0, width, height };
	sr_->SetSprite(item->sprite, false);

	GetTransform().SetSize(width, height);
}

std::shared_ptr<Item> InventoryItem::GetItem() const
{
	return item_;
}

std::vector<int> InventoryItem::GetSlotIndices() const
{
	return slot_indices_;
}
