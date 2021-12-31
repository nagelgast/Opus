#pragma once
#include <vector>

#include "Component.h"
#include "Rect.h"
#include "Vector2.h"

class Transform final : public Component
{
public:
	~Transform() override;

	Transform* GetParent();
	void SetParent(Transform& transform);
	
	Vector2 GetPosition() const;
	void SetPosition(Vector2 position);
	void SetLocalPosition(Vector2 position);
	void Move(Vector2 offset);
	
	void SetScale(float width, float height);
	Vector2 GetScale() const;

	Rect GetBounds(Vector2 offset, Vector2 scale_multiplier) const;

	std::vector<Transform*> GetChildren();
private:
	void RecalculateLocalPosition();
	void RecalculateChildrenPosition();
	void RecalculateChildPosition();

	void RecalculateLocalScale();
	void RecalculateChildrenScale();
	void RecalculateChildScale();


	Transform* parent_ = nullptr;
	Vector2 position_;
	Vector2 local_position_;
	Vector2 scale_ {1,1};
	Vector2 local_scale_;

	std::vector<Transform*> children_;

	friend class Entity;
};
