#pragma once

#include <memory>
#include <map>
#include <string>
#include <typeindex>
#include <vector>

#include "Opus.h"

class Collider;
class Transform;
class BaseEntityRenderer;
class Vector2;
class EntityController;
class Component;
struct Input;

class Entity
{
public:
	OPUS_API Entity();
	OPUS_API Entity(Entity&);
	OPUS_API ~Entity();

	OPUS_API void Start(EntityController* ec);
	
	OPUS_API void Update();
	void FixedUpdate();
	OPUS_API void Destroy();

	OPUS_API std::shared_ptr<Collider> AddComponent(const Collider& c);
	OPUS_API std::shared_ptr<Entity> Instantiate() const;


	template <typename T> std::shared_ptr<T> AddComponent()
	{
		return AddComponent(T());
	}
	
	template <typename T> std::shared_ptr<T> AddComponent(T c)
	{
		auto c_ptr = std::make_shared<T>(c);
		c_ptr->entity_ = this;

		components_[std::type_index(typeid(*c_ptr))] = c_ptr;

		return c_ptr;
	}

	
	template <typename T> std::shared_ptr<T> GetComponent()
	{
		const std::type_index index(typeid(T));

		if (components_.count(index) != 0)
		{
			return std::static_pointer_cast<T>(components_[index]);
		}

		return nullptr;
	}

	OPUS_API std::shared_ptr<Entity> Instantiate(Entity&& e) const;
	OPUS_API std::vector<std::shared_ptr<Entity>>& GetEntities() const;
	OPUS_API float GetDeltaTime() const;
	OPUS_API float GetFixedDeltaTime() const;
	OPUS_API const Input& GetInput() const;

	OPUS_API Transform& GetTransform() const;

	OPUS_API void SetName(const std::string& name);

	OPUS_API BaseEntityRenderer* CreateRenderer();
	OPUS_API BaseEntityRenderer* GetRenderer() const;
	OPUS_API bool HasRenderer() const;
	
	void OnCollision(const Collider& other);

private:
	void OnDestroy();
	
	std::string name_;
	EntityController* ec_ = nullptr;
	std::shared_ptr<Transform> transform_;
	std::unique_ptr<BaseEntityRenderer> renderer_;

	std::shared_ptr<Collider> collider_;
	std::map<std::type_index, std::shared_ptr<Component>> components_{};

	bool destroyed_ = false;
};
