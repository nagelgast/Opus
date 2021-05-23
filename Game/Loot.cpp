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
	Item item {"TestWand", sprite, 1, 3};
	Item item2 { "TestBelt", sprite, 2, 2 };
	Item item3 {"TestOrb", sprite, 1, 1};
	
	auto pos = entity_->GetTransform().GetPosition();
	
	const auto world_item = entity_->Instantiate<WorldItem>(pos);
	world_item->item_ = std::make_shared<Item>(item);
	const auto world_item2 = entity_->Instantiate<WorldItem>(pos);
	world_item2->item_ = std::make_shared<Item>(item2);
	const auto world_item3 = entity_->Instantiate<WorldItem>(pos);
	world_item3->item_ = std::make_shared<Item>(item3);
}
