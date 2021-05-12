#include "Loot.h"


#include "Interactable.h"
#include "Item.h"
#include "WorldItem.h"
#include "../Opus/ShapeRenderer.h"

void Loot::OnDestroy()
{
	SpawnItem();
}

void Loot::SpawnItem() const
{
	Item item {};
	item.SetName("TestItem");
	item.SetSprite(Sprite{ "Sprites/Driftwood_Wand_inventory_icon.png", {0, 0, 78, 234} });

	auto world_item = entity_->Instantiate();
	world_item->SetName("WorldItem");
	
	world_item->AddComponent(ShapeRenderer(Shape::kSquare, 0.5f, 0.5f, 0.5f, 1));
	const auto interactable = world_item->AddComponent(Interactable());

	const auto size = 30;
	interactable->bounds_ = {0, 0, size, size};

	auto& transform = world_item->GetTransform();
	transform.SetPosition(entity_->GetTransform().GetPosition());
	transform.SetSize(size, size);
	world_item->AddComponent(WorldItem(interactable, item));
}
