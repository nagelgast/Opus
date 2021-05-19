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
	const Sprite sprite{ "Sprites/Driftwood_Wand_inventory_icon.png", {0, 0, 78, 234} };
	Item item {"TestItem", sprite, 1, 3};
	
	const auto world_item = entity_->Instantiate<WorldItem>(entity_->GetTransform().GetPosition());
	world_item->item_ = std::make_shared<Item>(item);
}
