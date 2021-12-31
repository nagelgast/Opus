#include "ScreenItem.h"

#include "Inventory.h"
#include "Interactable.h"
#include "InventoryScreen.h"
#include "InventorySlot.h"
#include "Item.h"
#include "PlayerItemStorage.h"
#include "../Opus/SpriteRenderer.h"

void ScreenItem::Awake()
{
	interactable_ = &AddComponent(Interactable());
	sr_ = &AddComponent(SpriteRenderer());
}

void ScreenItem::Initialize(Item& item, const std::vector<InventorySlot*>& slots)
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

	// TODO Use a global item scale setting
	GetTransform().SetScale(2, 2);

}

void ScreenItem::Remove()
{
	for(auto& slot : slots_)
	{
		slot->ClearItem();
	}
	
	Destroy();
}

Item& ScreenItem::GetItem() const
{
	return *item_;
}

void ScreenItem::SetHighlight(const Color color)
{
	for (const auto& slot : slots_)
	{
		slot->EnableHighlight(color);
	}
}

