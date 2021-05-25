#include "InventoryItem.h"

#include "Inventory.h"
#include "Interactable.h"
#include "InventorySlot.h"
#include "Item.h"
#include "../Opus/SpriteRenderer.h"

void InventoryItem::Awake()
{
	interactable_ = AddComponent(Interactable());
	sr_ = AddComponent(SpriteRenderer());
}

void InventoryItem::Initialize(const std::shared_ptr<InventoryItem>& self, const std::shared_ptr<Item>& item,
	const std::vector<std::shared_ptr<InventorySlot>>& slots)
{
	self_ = self;
	item_ = item;
	slots_ = slots;

	for(const auto& slot : slots_)
	{
		slot->SetItem(self);
	}
	
	const auto width = static_cast<float>(kInventorySlotSize * item->size.width);
	const auto height = static_cast<float>(kInventorySlotSize * item->size.height);

	sr_->SetSprite(item->sprite, false);

	GetTransform().SetScale(width, height);

}

std::shared_ptr<Item> InventoryItem::Take()
{
	for(auto& slot : slots_)
	{
		slot->ClearItem();
	}
	
	Destroy();

	return item_;
}

std::shared_ptr<Item> InventoryItem::GetItem() const
{
	return item_;
}

void InventoryItem::SetHighlight(const Color color)
{
	for (const auto& slot : slots_)
	{
		slot->EnableHighlight(color);
	}
}

