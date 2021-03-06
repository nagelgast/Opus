#include "pch.h"
#include "CollisionSystem.h"

#include "Collision.h"
#include "Physics.h"
#include "Transform.h"

#include <algorithm>

#include "Entity.h"

void CollisionSystem::FixedUpdate()
{
	// TODO Replace with iterators
	// TODO Optimize to only check colliders with matching layers
	for (size_t i = 0; i < colliders_.size(); ++i)
	{
		auto* const collider = colliders_[i];
		for(auto j = i+1; j < colliders_.size(); ++j)
		{
			auto* const other = colliders_[j];
			HandleCollision(*collider, *other);
		}
	}
}

void CollisionSystem::HandleCollision(Collider& c1, Collider& c2) const
{
	if (!CheckLayerCollision(c1, c2)) return;
	
	const auto collision = Physics::HandleCollision(c1, c2);
	if (!collision.hit) return;

	if(!c1.IsTrigger() && !c2.IsTrigger())
	{
		if (c2.IsFixed())
		{
			c1.entity_->GetTransform().Move(collision.displacement);
		}
		else if (c1.IsFixed())
		{
			c2.entity_->GetTransform().Move(-collision.displacement);
		}
		else
		{
			c1.entity_->GetTransform().Move(collision.displacement / 2.f);
			c2.entity_->GetTransform().Move(-collision.displacement / 2.f);
		}
	}
	
	c1.Collide(c2);
	c2.Collide(c1);
}

bool CollisionSystem::CheckLayerCollision(const Collider& c1, const Collider& c2) const
{
	auto colliding_layers = collision_matrix_.at(c1.GetLayer());
	return std::find(colliding_layers.begin(), colliding_layers.end(), c2.GetLayer()) != colliding_layers.end();
}

void CollisionSystem::AddCollider(Collider* collider)
{
	colliders_.push_back(collider);
	colliders_by_layer_[collider->GetLayer()].push_back(collider);
}

void CollisionSystem::RemoveCollider(Collider* collider)
{
	const auto iter = remove(colliders_.begin(), colliders_.end(), collider);
	colliders_.erase(iter, colliders_.end());
	auto& layer = colliders_by_layer_[collider->GetLayer()];
	const auto layer_iter = remove(layer.begin(), layer.end(), collider);
	layer.erase(layer_iter, layer.end());
}

void CollisionSystem::SetCollisionMatrix(const std::map<int, std::vector<int>>& collision_matrix)
{
	collision_matrix_ = collision_matrix;
}

std::vector<Collider*> CollisionSystem::GetLayerColliders(int layer)
{
	return colliders_by_layer_[layer];
}
