#include "Loot.h"

#include "Item.h"
#include "../Opus/ShapeRenderer.h"

void Loot::OnDestroy()
{
	SpawnItem();
}

void Loot::SpawnItem()
{
	Entity item {};
	item.SetName("Item");
	item.AddComponent(ShapeRenderer(Shape::kSquare, 0.5f, 0.5f, 0.5f, 1));
	item.AddComponent(Item());
	auto& transform = item.GetTransform();
	transform.SetPosition(entity_->GetTransform().GetPosition());
	transform.SetSize(10, 10);

	entity_->Instantiate(std::move(item));
}
