#pragma once
#include "Component.h"
#include "Vector2.h"

class Transform final : public Component
{
public:
	~Transform();

	void SetParent(Transform* transform);
	
	Vector2 GetPosition() const;
	void SetPosition(Vector2 position);
	void SetLocalPosition(Vector2 position);
	void Move(Vector2 offset);
	
	void SetOrigin(Vector2 origin);
	void CenterOrigin();
	Vector2 GetOrigin() const;
	
	void SetScale(float width, float height);
	Vector2 GetScale() const;
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

	Vector2 origin_;

	std::vector<Transform*> children_;

	friend class Entity;
};
