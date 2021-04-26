#include "pch.h"
#include "CollisionSystem.h"

#include "Collision.h"
#include "Physics.h"
#include "Transform.h"

#include <algorithm>

void CollisionSystem::FixedUpdate()
{
	// TODO Replace with iterators
	for (auto i = 0; i < colliders_.size(); ++i)
	{
		auto collider = colliders_[i];
		for(auto j = i+1; j < colliders_.size(); ++j)
		{
			auto other = colliders_[j];
			HandleCollision(*collider, *other);
		}
	}
}

void CollisionSystem::HandleCollision(Collider& c1, Collider& c2) const
{
	if (c1.GetLayer() != c2.GetLayer()) return;
	
	const auto collision = Physics::HandleCollision(c1, c2);
	if (!collision.hit) return;

	if(!c1.IsTrigger() && !c2.IsTrigger())
	{
		if (c2.IsFixed())
		{
			c1.entity_->GetTransform().Move(-collision.displacement);
		}
		else if (c1.IsFixed())
		{
			c2.entity_->GetTransform().Move(collision.displacement);
		}
		else
		{
			c1.entity_->GetTransform().Move(-collision.displacement / 2.f);
			c2.entity_->GetTransform().Move(collision.displacement / 2.f);
		}
	}
	
	c1.Collide(c2);
	c2.Collide(c1);
}

void CollisionSystem::AddCollider(const std::shared_ptr<Collider>& collider)
{
	colliders_.push_back(collider);
}

void CollisionSystem::RemoveCollider(std::shared_ptr<Collider> collider)
{
	const auto iter = remove(colliders_.begin(), colliders_.end(), collider);
	colliders_.erase(iter, colliders_.end());
}
