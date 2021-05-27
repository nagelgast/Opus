#include "InventoryItem.h"

#include "Inventory.h"
#include "Interactable.h"
#include "InventorySlot.h"
#include "Item.h"
#include "../Opus/SpriteRenderer.h"

void InventoryItem::Awake()
{
	interactable_ = &AddComponent(Interactable());
	sr_ = &AddComponent(SpriteRenderer());
}

void InventoryItem::Initialize(std::unique_ptr<Item> item, const std::vector<InventorySlot*>& slots)
{
	item_ = std::move(item);
	slots_ = slots;

	for(const auto& slot : slots_)
	{
		slot->SetItem(*this);
	}
	
	const auto width = static_cast<float>(kInventorySlotSize * item_->size.width);
	const auto height = static_cast<float>(kInventorySlotSize * item_->size.height);

	sr_->SetSprite(item_->sprite, false);

	GetTransform().SetScale(width, height);

}

std::unique_ptr<Item> InventoryItem::TakeItem()
{
	for(auto& slot : slots_)
	{
		slot->ClearItem();
	}
	
	Destroy();

	return std::move(item_);
}

Item& InventoryItem::GetItem() const
{
	return *item_;
}

void InventoryItem::SetHighlight(const Color color)
{
	for (const auto& slot : slots_)
	{
		slot->EnableHighlight(color);
	}
}

