#include "InventorySlot.h"

#include "Interactable.h"
#include "ScreenItem.h"
#include "PlayerItemStorage.h"
#include "../Opus/ShapeRenderer.h"
#include "../Opus/SpriteRenderer.h"

void InventorySlot::Awake()
{
	storage_ = Game::GetService<PlayerItemStorage>();
	
	highlight_ = &CreateChild();
	shape_renderer_ = &highlight_->AddComponent(ShapeRenderer(Shape::kSquare, {0, 0, 0, 0.5f}, false));
	highlight_->SetVisible(false);

	interactable_ = &AddComponent(Interactable());
}

void InventorySlot::SetItem(ScreenItem& item)
{
	item_ = &item;
}

ScreenItem& InventorySlot::GetItem() const
{
	return *item_;
}

void InventorySlot::ClearItem()
{
	item_ = nullptr;
}

void InventorySlot::RemoveItem() const
{
	if(item_)
	{
		item_->Remove();
	}
}

bool InventorySlot::HasItem() const
{
	return item_ != nullptr;
}

void InventorySlot::EnableHighlight(const Color color) const
{
	highlight_->SetVisible(true);
	shape_renderer_->SetColor(color);
}

void InventorySlot::DisableHighlight() const
{
	highlight_->SetVisible(false);
}
