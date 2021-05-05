#include "Loot.h"

#include "Item.h"
#include "TargetingSystem.h"
#include "WorldItem.h"
#include "../Opus/ShapeRenderer.h"

void Loot::OnDestroy()
{
	SpawnItem();
}

void Loot::SpawnItem()
{
	Item item {};
	item.SetName("TestItem");
	item.SetSprite(Sprite{ "Sprites/mobs/slime-blue.png", {0, 8, 16, 16} });

	auto world_item = entity_->Instantiate();
	world_item->SetName("WorldItem");
	
	world_item->AddComponent(ShapeRenderer(Shape::kSquare, 0.5f, 0.5f, 0.5f, 1));
	auto targetable = world_item->AddComponent(Targetable());

	auto& transform = world_item->GetTransform();
	transform.SetPosition(entity_->GetTransform().GetPosition());
	transform.SetSize(10, 10);
	world_item->AddComponent(WorldItem(item));
}
