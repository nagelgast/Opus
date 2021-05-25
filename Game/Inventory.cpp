#include "Inventory.h"


#include "InventorySlot.h"
#include "Interactable.h"
#include "MouseItem.h"
#include "InventoryItem.h"
#include "Item.h"

#include "../Opus/ShapeRenderer.h"

void Inventory::Initialize(const std::shared_ptr<MouseItem>& mouse_item)
{
	mouse_item_ = mouse_item;
}

void Inventory::Awake()
{
	const auto width = static_cast<float>(kInventorySlotSize * columns_);
	const auto height = static_cast<float>(kInventorySlotSize * rows_);
	auto background = Instantiate(&GetTransform());
	background->AddComponent(ShapeRenderer(Shape::kSquare, {0.2f, 0.2f, 0.2f}, false));

	auto& background_transform = background->GetTransform();
	background_transform.SetSize(width, height);

	// TODO Replace with anchoring system
	const Vector2 offset = {(width - kInventorySlotSize) / 2, (height - kInventorySlotSize) / 2};

	for (auto row = 0; row < rows_; ++row)
	{
		for (auto col = 0; col < columns_; ++col)
		{
			auto index = col + row * columns_;
			const auto slot = Instantiate<InventorySlot>(&GetTransform());
			auto slot_interactable = slot->GetComponent<Interactable>();
			slot_interactable->OnRelease += [this, index] { HandleRelease(index); };
			slot_interactable->OnHoverEnter += [this, index] { HandleSlotHoverEnter(index); };
			slot_interactable->OnHoverExit += [this, index] { HandleSlotHoverExit(index); };

			auto& slot_transform = slot->GetTransform();
			slot_transform.SetSize(kInventorySlotSize, kInventorySlotSize);
			Vector2 slot_pos = {col * kInventorySlotSize, row * kInventorySlotSize};
			slot_transform.SetLocalPosition(slot_pos - offset);

			slots_.push_back(slot);
		}
	}
}

bool Inventory::TryAutoAddItem(const std::shared_ptr<Item>& item)
{
	const auto slot_indices = FindAvailableSlots(item->size);
	const auto has_space = !slot_indices.empty();
	if(has_space)
	{
		Place(item, slot_indices);
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

void Inventory::Place(const std::shared_ptr<Item>& item, std::vector<int> slot_indices)
{
	// Create new inventory item instance
	const auto inventory_item = Instantiate<InventoryItem>(&GetTransform());
	inventory_item->Initialize(item, slot_indices);

	// Position item correctly
	auto& transform = inventory_item->GetTransform();
	const Vector2 offset = {kInventorySlotSize*(item->size.width-1)/2, kInventorySlotSize * (item->size.height - 1) / 2 };
	transform.SetPosition(slots_[slot_indices[0]]->GetTransform().GetPosition() + offset);

	// Mark all of its slots as occupied
	for (auto slot_index : slot_indices)
	{
		slots_[slot_index]->SetItem(inventory_item);
	}

	ResetHighlights();
}

void Inventory::HandleRelease(const int index)
{
	if(hovering_over_multiple_items_) return;

	const auto picked_up_item = Take(pickup_slot_);

	if (mouse_item_->HasItem())
	{
		const auto new_item = mouse_item_->Take();
		Place(new_item, hover_slot_indices_);
	}

	if (picked_up_item)
	{
		mouse_item_->TryAddItem(picked_up_item);
		HandleSlotHoverEnter(index);
	}
}

std::shared_ptr<Item> Inventory::Take(const std::shared_ptr<InventorySlot>& slot)
{
	if(!slot->HasItem()) return nullptr;
	
	auto& inventory_item = slot->GetItem();
	auto item = inventory_item.GetItem();

	auto slot_indices = inventory_item.GetSlotIndices();

	for (auto slot_index : slot_indices)
	{
		slots_[slot_index]->ClearItem();
	}
	
	inventory_item.Destroy();

	return item;
}

void Inventory::HandleSlotHoverEnter(const int index)
{
	pickup_slot_ = slots_[index];
	
	if(mouse_item_->HasItem())
	{
		hover_slot_indices_ = CalculateSlotsToOccupy(mouse_item_->GetItem().size, index);

		auto hovering_over_item = false;
		hovering_over_multiple_items_ = false;
		for (auto slot_index : hover_slot_indices_)
		{
			const auto slot = slots_[slot_index];
			if(slot->HasItem())
			{
				if(!hovering_over_item)
				{
					// Set pickup slot here so that you will pick up that item, even if it's not underneath the hovered slot
					hovering_over_item = true;
					pickup_slot_ = slot;
				}
				else if(&pickup_slot_->GetItem() != &slot->GetItem())
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

	if (pickup_slot_->HasItem())
	{
		const auto pickup_color = mouse_item_->HasItem() ? kPickupSlotColor : kAvailableSlotColor;
		const auto pickup_slot_indices = pickup_slot_->GetItem().GetSlotIndices();
		for (auto pickup_slot_index : pickup_slot_indices)
		{
			slots_[pickup_slot_index]->EnableHighlight(pickup_color);
		}
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
