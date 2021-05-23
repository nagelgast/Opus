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
	interactable->bounds_ = { 0, 0, size, size };
	interactable->OnInteract += [this] { PickUp(); };

	auto& transform = GetTransform();
	transform.SetSize(size, size);
}

void WorldItem::PickUp()
{
	// TODO Improve this, geez
	for (const auto& entity : GetEntities())
	{
		auto inventory = entity->GetComponent<PlayerInventory>();
		if (inventory)
		{
			inventory->PickUpItem(item_);
			Destroy();
		}
	}
}
