#include "Inventory.h"


#include "Interactable.h"
#include "InventoryItem.h"
#include "InventorySlot.h"
#include "MouseItem.h"
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
	const auto offset_x = (width - kInventorySlotSize )/2;
	const auto offset_y = (height - kInventorySlotSize )/2;
	
	for (auto row = 0; row < rows_; ++row)
	{
		for (auto col = 0; col < columns_; ++col)
		{
			const auto slot = Instantiate<InventorySlot>(&GetTransform());
			auto& slot_transform = slot->GetTransform();
			slot_transform.SetSize(kInventorySlotSize, kInventorySlotSize);
			slot_transform.SetLocalPosition({col * kInventorySlotSize - offset_x, row * kInventorySlotSize - offset_y});
		}
	}

	auto interactable = AddComponent(Interactable());
	interactable->bounds_ = {0, 0, width, height};
	interactable->OnPress += [this] { HandlePress(); };
}

void Inventory::AddItem(const std::shared_ptr<Item>& item)
{
	auto entity = Instantiate(&GetTransform());
	auto interactable = entity->AddComponent(Interactable());
	interactable->bounds_ = {0, 0, 40, 120};

	const auto inventory_item = entity->AddComponent(InventoryItem(item));
	auto sr = entity->AddComponent(SpriteRenderer());
	sr->SetSprite(item->GetSprite(), false);

	auto& transform = entity->GetTransform();
	transform.SetSize(40, 120);

	items_[0] = inventory_item;
}

void Inventory::HandlePress()
{
	std::shared_ptr<Item> old_item = nullptr;

	if (items_[0])
	{
		old_item = items_[0]->item_;
	}

	if (mouse_item_->HasItem())
	{
		mouse_item_->Place(*this);
	}

	if (old_item)
	{
		mouse_item_->TryAddItem(old_item);
		items_[0]->entity_->Destroy();
		items_[0] = nullptr;
	}
}
