#include "EquipmentSlot.h"

#include "Interactable.h"
#include "PlayerItemStorage.h"
#include "ScreenItem.h"

void EquipmentSlot::Awake()
{
	InventorySlot::Awake();
	
	interactable_->OnHoverEnter += [this] { SetEquippableHighlight(); };
	interactable_->OnHoverExit += [this] { DisableHighlight(); };
	interactable_->OnRelease += [this] { HandleRelease(); };
}

void EquipmentSlot::SpawnItem(Item& item)
{
	item_ = &Instantiate<ScreenItem>(GetTransform());
	item_->Initialize(item, { this });
}

bool EquipmentSlot::CanHold(Item& item) const
{
	if (required_tag_ == ItemTag::kNoTag) return true;

	return item.HasTag(required_tag_);
}

void EquipmentSlot::SetRequiredTag(const ItemTag& tag)
{
	required_tag_ = tag;
}

ItemTag EquipmentSlot::GetRequiredTag() const
{
	return required_tag_;
}

void EquipmentSlot::HandleRelease()
{
	storage_->HandleEquipmentRelease(*this);
}

void EquipmentSlot::SetEquippableHighlight() const
{
	if (storage_->IsHoldingItem() && !storage_->CanEquipHeldItem(*this))
	{
		EnableHighlight(kUnavailableSlotColor);
	}
	else
	{
		EnableHighlight(kAvailableSlotColor);
	}
}

