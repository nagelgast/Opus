#include "WorldItem.h"

#include "../Opus/ShapeRenderer.h"

#include "Interactable.h"
#include "PlayerInventory.h"

void WorldItem::Awake()
{
	SetName("WorldItem");

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
	PlayerInventory::GetInstance().PickUpItem(std::move(item_));
	Destroy();
}