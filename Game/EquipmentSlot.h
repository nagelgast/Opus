#pragma once
#include "InventorySlot.h"

class EquipmentSlot :
	public InventorySlot
{
public:
	void SpawnItem(Item& item);
	
	void SetRequiredTag(const ItemTag& tag);
	ItemTag GetRequiredTag() const;
	bool CanHold(Item& item) const;
private:
	void Awake() override;

	void HandleRelease();
	void SetEquippableHighlight() const;

	ItemTag required_tag_ = ItemTag::kNoTag;
};
