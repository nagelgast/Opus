#include "Interactable.h"

#include "../Opus/Input.h"
#include "PlayerController.h"

Rect Interactable::GetGlobalBounds()
{
	const auto transform = entity_->GetTransform();
	const auto pos = transform.GetPosition();
	const auto offset = transform.GetOrigin();
	const auto scale = transform.GetScale();
	
	auto global_bounds = bounds_;
	global_bounds.left = pos.x - offset.x;
	global_bounds.top = pos.y - offset.y;
	global_bounds.width *= scale.x;
	global_bounds.height *= scale.y;
	
	return global_bounds;
}
