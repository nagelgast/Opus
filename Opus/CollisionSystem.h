#pragma once
#include <memory>
#include <vector>
#include <map>

#include "Collider.h"

class CollisionSystem
{
public:
	void FixedUpdate();

	void AddCollider(const std::shared_ptr<Collider>& collider);
	void RemoveCollider(std::shared_ptr<Collider> collider);
	void SetCollisionMatrix(const std::map<int, std::vector<int>>& collision_matrix);
private:
	void HandleCollision(Collider& c1, Collider& c2) const;
	bool CheckLayerCollision(const Collider& c1, const Collider& c2) const;

	std::map<int, std::vector<int>> collision_matrix_;
	std::vector<std::shared_ptr<Collider>> colliders_;

};

