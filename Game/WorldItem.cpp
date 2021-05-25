#include "WorldItem.h"

#include "../Opus/ShapeRenderer.h"

#include "Interactable.h"
#include "PlayerInventory.h"

void WorldItem::Awake()
{
	SetName("WorldItem");

	AddComponent(ShapeRenderer(Shape::kSquare, {0.5f, 0.5f, 0.5f}));
	const auto size = 30;
	auto interactable = AddComponent(Interactable());
	interactable->OnInteract += [this] { PickUp(); };

	auto& transform = GetTransform();
	transform.SetScale(size, size);
}

void WorldItem::PickUp()
{
	PlayerInventory::GetInstance().PickUpItem(item_);
	Destroy();
}
