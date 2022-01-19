#include "WorldItem.h"

#include "../Opus/ShapeRenderer.h"

#include "Interactable.h"
#include "PlayerItemStorage.h"

void WorldItem::Awake()
{
	player_inventory_ = Game::GetService<PlayerItemStorage>();
	entity_->SetName("WorldItem");

	AddComponent(ShapeRenderer(Shape::kSquare, {0.5f, 0.5f, 0.5f}));
	const auto size = 30;
	auto& interactable = AddComponent(Interactable());
	interactable.OnInteract += [this] { PickUp(); };

	auto& transform = GetTransform();
	transform.SetScale(size, size);
}

void WorldItem::Initialize(std::unique_ptr<Item> item)
{
	item_ = std::move(item);
}

// TODO Should return the item
void WorldItem::PickUp()
{
	player_inventory_->PickUpItem(std::move(item_));
	entity_->Destroy();
}