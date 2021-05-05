#include "MouseItem.h"


#include "Item.h"
#include "../Opus/Input.h"
#include "../Opus/SpriteRenderer.h"

MouseItem::MouseItem()
{
	renderer_ = AddComponent(SpriteRenderer());
}

bool MouseItem::TrySetItem(std::shared_ptr<Item> item)
{
	if(item_) return false;

	item_ = std::move(item);
	renderer_->SetSprite(item_->GetSprite());

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
