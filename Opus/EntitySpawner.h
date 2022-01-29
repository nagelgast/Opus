#pragma once

#include <string>

class Space;
class Entity;
class Transform;
struct Vector2;

class EntitySpawner
{
public:
	Entity& Create(const std::string& name = std::string()) const;
	Entity& Create(const Vector2& position, const std::string& name = std::string()) const;
	Entity& Create(Transform& parent, const std::string& name = std::string()) const;

	template <typename T>
	T& Create(const std::string& name = std::string())
	{
		auto& entity = Create(name);
		T& component = entity.AddComponent<T>();
		return component;
	}

	template <typename T>
	T& Create(const Vector2& position, const std::string& name = std::string())
	{
		auto& entity = Create(position, name);
		auto& component = entity.AddComponent<T>();
		return component;
	}

	template <typename T>
	T& Create(Transform& parent, const std::string& name = std::string())
	{
		auto& entity = Create(parent, name);
		auto& component = entity.AddComponent<T>();
		component.space_ = space_;
		return component;
	}
protected:
	// TODO Find a way to make this a reference
	Space* space_ = nullptr;
};
