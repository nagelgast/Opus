#pragma once

#include <memory>
#include <map>
#include <string>
#include <typeindex>
#include <vector>

class Collider;
class Transform;
class BaseEntityRenderer;
struct Vector2;
class EntityController;
class Component;
struct Input;

class Entity
{
public:
	Entity();
	Entity(Entity&);
	~Entity();

	void Start(EntityController* ec);
	
	virtual void Update() {}
	virtual void FixedUpdate() {}
	void UpdateComponents();
	void FixedUpdateComponents();
	void Destroy();

	std::shared_ptr<Collider> AddComponent(const Collider& c);
	std::shared_ptr<Entity> Instantiate() const;


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

	std::shared_ptr<Entity> Instantiate(Entity&& e) const;
	std::vector<std::shared_ptr<Entity>>& GetEntities() const;
	float GetDeltaTime() const;
	float GetFixedDeltaTime() const;
	const Input& GetInput() const;

	Transform& GetTransform() const;

	void SetName(const std::string& name);

	BaseEntityRenderer* CreateRenderer();
	BaseEntityRenderer* GetRenderer() const;
	bool HasRenderer() const;
	
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

	friend class EntityController;
};
