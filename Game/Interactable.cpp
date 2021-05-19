#include "Interactable.h"

#include "../Opus/Input.h"
#include "PlayerController.h"

Rect Interactable::GetGlobalBounds()
{
	const auto pos = entity_->GetTransform().GetPosition();
	const auto offset = entity_->GetTransform().GetOrigin();

	auto global_bounds = bounds_;
	global_bounds.left = pos.x - offset.x;
	global_bounds.top = pos.y - offset.y;
	
	return global_bounds;
}
