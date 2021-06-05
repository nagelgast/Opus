#include "Inventory.h"


#include "InventorySlot.h"
#include "Interactable.h"
#include "MouseSlot.h"
#include "InventoryItem.h"
#include "Item.h"
#include "ItemInfoPopup.h"
#include "PlayerInventory.h"

#include "../Opus/ShapeRenderer.h"

void Inventory::Initialize(MouseSlot& mouse_item)
{
	mouse_item_ = &mouse_item;
}

void Inventory::Awake()
{
	const auto width = static_cast<float>(kInventorySlotSize * columns_);
	const auto height = static_cast<float>(kInventorySlotSize * rows_);
	auto& background = Instantiate(GetTransform());
	background.AddComponent(ShapeRenderer(Shape::kSquare, {0.2f, 0.2f, 0.2f}, false));

	auto& background_transform = background.GetTransform();
	background_transform.SetScale(width, height);

	for (auto row = 0; row < rows_; ++row)
	{
		for (auto col = 0; col < columns_; ++col)
		{
			auto index = col + row * columns_;
			auto& slot = Instantiate<InventorySlot>(GetTransform());
			auto& slot_interactable = *slot.GetComponent<Interactable>();
			slot_interactable.OnRelease += [this, index] { HandleRelease(index); };
			slot_interactable.OnHoverEnter += [this, index] { HandleSlotHoverEnter(index); };
			slot_interactable.OnHoverExit += [this, index] { HandleSlotHoverExit(index); };

			auto& slot_transform = slot.GetTransform();
			slot_transform.SetScale(kInventorySlotSize, kInventorySlotSize);
			const Vector2 slot_pos = {col * kInventorySlotSize, row * kInventorySlotSize};
			slot_transform.SetLocalPosition(slot_pos);

			slots_.push_back(&slot);
		}
	}
}

bool Inventory::TryAutoAddItem(std::unique_ptr<Item> item)
{
	const auto slot_indices = FindAvailableSlots(item->GetSize());
	const auto has_space = !slot_indices.empty();
	if(has_space)
	{
		Place(std::move(item), slot_indices);
	}

	return has_space;
}

std::vector<int> Inventory::FindAvailableSlots(const ItemSize item_size)
{
	for(auto col = 0; col < columns_; ++col)
	{
		for(auto row = 0; row < rows_; ++row)
		{
			const auto index = col+row*columns_;
			auto slot_indices = CalculateSlotsToOccupy(item_size, index);
			auto is_available = true;
			for (auto slot_index : slot_indices)
			{
				if(slots_[slot_index]->HasItem())
				{
					is_available = false;
					break;
				}
			}
			if(is_available)
			{
				return slot_indices;
			}
		}
	}
	
	return {};
}

void Inventory::Place(std::unique_ptr<Item> item, const std::vector<int>& slot_indices)
{
	std::vector<InventorySlot*> item_slots;
	for(auto index : slot_indices)
	{
		item_slots.push_back(slots_[index]);
	}
	
	// Create new inventory item instance
	auto& inventory_item = Instantiate<InventoryItem>(GetTransform());

	// Position item correctly
	auto& transform = inventory_item.GetTransform();
	const Vector2 offset = { kInventorySlotSize * (item->GetSize().width - 1) / 2, kInventorySlotSize * (item->GetSize().height - 1) / 2 };
	transform.SetPosition(item_slots[0]->GetTransform().GetPosition());
	
	inventory_item.Initialize(std::move(item), item_slots);


	ResetHighlights();
}

void Inventory::HandleRelease(const int index)
{
	if(hovering_over_multiple_items_) return;

	std::unique_ptr<Item> picked_up_item = nullptr;

	if(pickup_item_)
	{
		picked_up_item = pickup_item_->TakeItem();
	}
	
	if (mouse_item_->HasItem())
	{
		Place(mouse_item_->Take(), hover_slot_indices_);
	}

	if (picked_up_item)
	{
		PlayerInventory::GetInstance().PickUpItem(std::move(picked_up_item));
		HandleSlotHoverEnter(index);
	}
}

void Inventory::HandleSlotHoverEnter(const int index)
{
	pickup_item_ = &slots_[index]->GetItem();

	if(pickup_item_)
	{
		// TODO Dynamic positioning
		auto pos = pickup_item_->GetTransform().GetPosition();
		pos.x -= 40;
		pos.y -= 210;
		popup_ = &Instantiate<ItemInfoPopup>(pos);
		popup_->SetItem(pickup_item_->GetItem());
	}
	
	if(mouse_item_->HasItem())
	{
		hover_slot_indices_ = CalculateSlotsToOccupy(mouse_item_->GetItem().GetSize(), index);

		auto hovering_over_item = false;
		hovering_over_multiple_items_ = false;
		for (auto slot_index : hover_slot_indices_)
		{
			auto* const slot = slots_[slot_index];
			if(slot->HasItem())
			{
				if(!hovering_over_item)
				{
					// Set pickup slot here so that you will pick up that item, even if it's not underneath the hovered slot
					hovering_over_item = true;
					pickup_item_ = &slot->GetItem();
				}
				else if(pickup_item_ != &slot->GetItem())
				{
					hovering_over_multiple_items_ = true;
				}
			}
		}
	}

	SetHighlights();
}

void Inventory::HandleSlotHoverExit(int index)
{
	if(popup_)
	{
		popup_->Destroy();
		popup_ = nullptr;
	}
	ResetHighlights();
	hover_slot_indices_.clear();
}

std::vector<int> Inventory::CalculateSlotsToOccupy(const ItemSize item_size, const int index) const
{
	// Just return index if small item
	if(item_size.width == 1 && item_size.height == 1)
	{
		return {index};
	}
	
	auto top_row = index / columns_;
	auto left_col = index % columns_;
	
	if (item_size.width > 1)
	{
		// Calculate left-most column
		if (left_col + item_size.width > columns_)
		{
			// Correct if near right edge
			left_col = columns_ - item_size.width;
		}
		else
		{
			// TODO Check mid-slot mouse position
		}
	}

	if (item_size.height > 1)
	{
		// Calculate top-most row
		if(top_row + item_size.height > rows_)
		{
			// Correct if near bottom edge
			top_row = rows_ - item_size.height;
		}
		else
		{
			// TODO Check mid-slot mouse position
		}
	}

	// TODO Initialize this to size
	std::vector<int> result;
	
	for(auto row = 0; row < item_size.height; ++row)
	{
		for(auto col = 0; col < item_size.width; ++col)
		{
			auto value = (row+top_row)*columns_ + col + left_col;
			result.push_back(value);
		}
	}

	return result;
}

void Inventory::SetHighlights()
{
	// TODO Implement overlap slot coloring
	
	if(mouse_item_->HasItem())
	{
		const auto hover_color = hovering_over_multiple_items_ ? kUnavailableSlotColor : kAvailableSlotColor;

		for (auto highlight_slot : hover_slot_indices_)
		{
			slots_[highlight_slot]->EnableHighlight(hover_color);
		}
	}

	if (pickup_item_)
	{
		const auto pickup_color = mouse_item_->HasItem() ? kPickupSlotColor : kAvailableSlotColor;
		pickup_item_->SetHighlight(pickup_color);
	}
}

void Inventory::ResetHighlights()
{
	for (const auto& slot : slots_)
	{
		if(slot->HasItem())
		{
			slot->EnableHighlight(kItemSlotColor);
		}
		else
		{
			slot->DisableHighlight();
		}
	}
}
