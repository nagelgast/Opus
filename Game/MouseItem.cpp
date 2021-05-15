#include "MouseItem.h"


#include "Item.h"
#include "../Opus/Input.h"
#include "../Opus/SpriteRenderer.h"

void MouseItem::Awake()
{
	renderer_ = AddComponent(SpriteRenderer());
}

bool MouseItem::TryAddItem(std::shared_ptr<Item> item)
{
	if(item_) return false;

	item_ = std::move(item);
	renderer_->SetSprite(item_->GetSprite(), false);

	return true;
}

bool MouseItem::HasItem() const
{
	return item_ != nullptr;
}

void MouseItem::Update()
{
	GetTransform().SetPosition(GetInput().mouse_screen_pos);
}
