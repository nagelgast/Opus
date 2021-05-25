#pragma once
#include "Component.h"
#include "Vector2.h"

class Transform final : public Component
{
public:
	~Transform();
	
	void SetParent(Transform* transform);
	
	void SetSize(float width, float height);
	Vector2 GetPosition() const;
	void SetPosition(Vector2 position);
	void SetLocalPosition(Vector2 position);
	void Move(Vector2 offset);
	void SetOrigin(Vector2 origin);
	Vector2 GetOrigin() const;
	Vector2 GetScale() const;
private:
	void RecalculateLocalPosition();
	void RecalculateChildrenPosition();
	void RecalculateChildPosition();
	
	Transform* parent_ = nullptr;
	Vector2 position_;
	Vector2 local_position_;
	Vector2 rotation_;
	Vector2 scale_ {1,1};

	Vector2 origin_;

	std::vector<Transform*> children_;

	friend class Entity;
};
