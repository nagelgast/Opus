#include "Inventory.h"


#include "InventorySlot.h"
#include "Interactable.h"
#include "MouseItem.h"
#include "InventoryItem.h"
#include "Item.h"

#include "../Opus/ShapeRenderer.h"
#include "../Opus/SpriteRenderer.h"

const int kInventorySlotSize = 25;

void Inventory::Initialize(const std::shared_ptr<MouseItem>& mouse_item)
{
	mouse_item_ = mouse_item;
}

void Inventory::Awake()
{
	const auto width = static_cast<float>(kInventorySlotSize * columns_);
	const auto height = static_cast<float>(kInventorySlotSize * rows_);
	auto background = Instantiate(&GetTransform());
	background->AddComponent(ShapeRenderer(Shape::kSquare, 0.2f, 0.2f, 0.2f, 1, false));

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

void Inventory::AddItem(const std::shared_ptr<Item>& item)
{
	// TODO Implement automatically finding available space
	AddItem(item, slots_[0]);
}

void Inventory::AddItem(const std::shared_ptr<Item>& item, const std::shared_ptr<InventorySlot>& slot) const
{
	const auto inventory_item = SpawnInventoryItem(item);
	auto& transform = inventory_item->entity_->GetTransform();
	const Vector2 offset = {kInventorySlotSize*(item->width-1)/2, kInventorySlotSize * (item->height - 1) / 2 };
	transform.SetPosition(slot->GetTransform().GetPosition() + offset);

	
	slot->SetItem(inventory_item);
}

void Inventory::HandleRelease(const int index)
{
	std::shared_ptr<Item> old_item = nullptr;

	if(hovering_over_multiple_items_)
	{
		return;
	}
	
	const auto slot_item = pickup_slot_->Take();
	if(slot_item)
	{
		old_item = slot_item->item_;
		slot_item->entity_->Destroy();
	}

	if (mouse_item_->HasItem())
	{
		const auto new_item = mouse_item_->Take();
		AddItem(new_item, slots_[index]);
	}

	// Swap the old item to the mouse after placing the new item to ensure the mouse has space
	if (old_item)
	{
		mouse_item_->TryAddItem(old_item);
	}
}


std::shared_ptr<InventoryItem> Inventory::SpawnInventoryItem(const std::shared_ptr<Item>& item) const
{
	const auto width = static_cast<float>(kInventorySlotSize * item->width);
	const auto height = static_cast<float>(kInventorySlotSize * item->height);

	auto entity = Instantiate(&GetTransform());
	auto interactable = entity->AddComponent(Interactable());
	interactable->bounds_ = {0, 0, width, height};

	auto inventory_item = entity->AddComponent(InventoryItem(item));
	auto sr = entity->AddComponent(SpriteRenderer());
	sr->SetSprite(item->sprite, false);

	entity->GetTransform().SetSize(width, height);

	return inventory_item;
}

void Inventory::HandleSlotHoverEnter(const int index)
{
	pickup_slot_ = slots_[index];
	
	if(mouse_item_->HasItem())
	{
		hover_slot_indices_ = CalculateHoverSlots(mouse_item_->GetItem(), index);

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
				else
				{
					hovering_over_multiple_items_ = true;
				}
			}
		}
		
		EnableHighlights();
	}
}

void Inventory::HandleSlotHoverExit(int index)
{
	ClearHighlights();
}

std::vector<int> Inventory::CalculateHoverSlots(Item& item, const int index) const
{
	// Just return index if small item
	if(item.width == 1 && item.height == 1)
	{
		return {index};
	}
	
	auto top_row = index / columns_;
	auto left_col = index % columns_;
	
	if (item.width > 1)
	{
		// Calculate left-most column
		if (left_col + item.width > columns_)
		{
			// Correct if near right edge
			left_col = columns_ - item.width;
		}
		else
		{
			// Check mid-way position
		}
	}

	if (item.height > 1)
	{
		// Calculate top-most row
		if(top_row + item.height > rows_)
		{
			// Correct if near bottom edge
			top_row = rows_ - item.height;
		}
		else
		{
			// Check mid-way position
		}
	}

	// TODO Initialize this to size
	std::vector<int> result;
	
	for(auto row = 0; row < item.height; ++row)
	{
		for(auto col = 0; col < item.width; ++col)
		{
			auto value = (row+top_row)*columns_ + col + left_col;
			result.push_back(value);
		}
	}

	return result;
}

void Inventory::EnableHighlights()
{
	for (auto highlight_slot : hover_slot_indices_)
	{
		slots_[highlight_slot]->EnableHighlight();
	}
}

void Inventory::ClearHighlights()
{
	for (auto highlighted_slot : hover_slot_indices_)
	{
		slots_[highlighted_slot]->DisableHighlight();
	}
	hover_slot_indices_.clear();
}
