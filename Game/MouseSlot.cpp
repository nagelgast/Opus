#include "MouseSlot.h"

#include "Item.h"
#include "WorldItem.h"
#include "../Opus/Input.h"
#include "../Opus/SpriteRenderer.h"

void MouseSlot::Awake()
{
	renderer_ = AddComponent(SpriteRenderer());
}

bool MouseSlot::SetItem(const std::shared_ptr<Item>& item)
{
	item_ = item;
	renderer_->SetSprite(item_->sprite, false);

	GetTransform().SetScale(item_->sprite.rect.width, item_->sprite.rect.height);
	
	return true;
}

bool MouseSlot::TryDrop(const Vector2 position)
{
	if(HasItem())
	{
		if(can_drop_items_)
		{
			Drop(position);
		}
		else
		{
			// PromptDestroyItem();
		}

		return true;
	}

	return false;
}

std::shared_ptr<Item> MouseSlot::Take()
{
	auto item = item_;
	Clear();
	return item;
}

Item& MouseSlot::GetItem()
{
	return *item_;
}

bool MouseSlot::HasItem() const
{
	return item_ != nullptr;
}

void MouseSlot::Update()
{
	GetTransform().SetPosition(GetInput().mouse_screen_pos);
}

void MouseSlot::Drop(const Vector2 position)
{
	const auto world_item = Instantiate<WorldItem>(position);
	world_item->item_ = item_;

	Clear();
}

void MouseSlot::Clear()
{
	item_ = nullptr;
	renderer_->ResetSprite();
	GetTransform().SetScale(1,1);
}
