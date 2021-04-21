#pragma once
#include <memory>
#include <vector>

#include "Collider.h"

class CollisionSystem
{
public:
	void FixedUpdate();

	void AddCollider(const std::shared_ptr<Collider>& collider);
	void RemoveCollider(std::shared_ptr<Collider> collider);
private:
	std::vector<std::shared_ptr<Collider>> colliders_;

	void HandleCollision(Collider& c1, Collider& c2) const;
};

