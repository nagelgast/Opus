#include "InventoryItem.h"

#include "Inventory.h"
#include "Interactable.h"
#include "InventoryScreen.h"
#include "InventorySlot.h"
#include "Item.h"
#include "../Opus/SpriteRenderer.h"

void InventoryItem::Awake()
{
	interactable_ = &AddComponent(Interactable());
	sr_ = &AddComponent(SpriteRenderer());
}

void InventoryItem::Initialize(Item& item, const std::vector<InventorySlot*>& slots)
{
	item_ = &item;
	slots_ = slots;

	for(const auto& slot : slots_)
	{
		slot->SetItem(*this);
	}
	
	const auto width = static_cast<float>(kInventorySlotSize * item_->GetSize().width);
	const auto height = static_cast<float>(kInventorySlotSize * item_->GetSize().height);

	sr_->SetSprite(item_->GetSprite(), false);

	GetTransform().SetScale(width, height);

}

void InventoryItem::Remove()
{
	for(auto& slot : slots_)
	{
		slot->ClearItem();
	}
	
	Destroy();
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

