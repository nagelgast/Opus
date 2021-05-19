#include "Inventory.h"


#include "Interactable.h"
#include "InventoryItem.h"
#include "MouseItem.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/SpriteRenderer.h"

void Inventory::Initialize(const std::shared_ptr<MouseItem>& mouse_item)
{
	mouse_item_ = mouse_item;
}

void Inventory::Awake()
{
	auto background = Instantiate();
	background->AddComponent(ShapeRenderer(Shape::kSquare, 0.4f, 0.4f, 0.4f, 1, false));

	auto& transform = background->GetTransform();
	transform.SetParent(&GetTransform());
	transform.SetSize(300, 150);

	auto interactable = AddComponent(Interactable());
	interactable->bounds_ = {0, 0, 300, 150};
	interactable->OnPress += [this] { HandlePress(); };
}

void Inventory::AddItem(const std::shared_ptr<Item>& item)
{
	auto entity = Instantiate();
	auto interactable = entity->AddComponent(Interactable());
	interactable->bounds_ = {0, 0, 40, 120};

	const auto inventory_item = entity->AddComponent(InventoryItem(item));
	auto sr = entity->AddComponent(SpriteRenderer());
	sr->SetSprite(item->GetSprite(), false);

	auto& transform = entity->GetTransform();
	transform.SetSize(40, 120);
	transform.SetParent(&GetTransform());
	transform.SetLocalPosition({0, 0});

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
