#pragma once

#include <memory>
#include <string>

#include "BaseInputHandler.h"
#include "BaseRenderer.h"
#include "BaseTime.h"
#include "CollisionSystem.h"

#include "TextureManager.h"
#include "BaseWindow.h"
#include "Service.h"
#include "Space.h"

class Game
{
public:
	explicit Game(int width, int height, int fps_limit, int fixed_update_ms, const std::string& title);

	void Run();
	void Exit();

	static Space& GetWorldSpace();
	static Space& GetScreenSpace();
	static Space& GetDebugSpace();

	void SetCamera(const Camera& camera) const;
	void SetCollisionMatrix(const std::map<int, std::vector<int>>& collision_matrix);

	static const BaseTime& GetTime();
	static const Input& GetInput();

	// TODO These should not be public
	static const BaseRenderer& GetRenderer();
	static CollisionSystem& GetCollisionSystem();
	static TextureManager& GetTextureManager();


	template <typename T>
	T& AddService()
	{
		auto c_ptr = std::make_unique<T>();

		const auto type = std::type_index(typeid(*c_ptr));
		services_[type] = std::move(c_ptr);

		return static_cast<T&>(*services_[type]);
	}
	
	template <typename T>
	static T* GetService()
	{
		const std::type_index index(typeid(T));

		if (instance_->services_.count(index) != 0)
		{
			return static_cast<T*>(instance_->services_[index].get());
		}

		return nullptr;
	}

private:
	void HandleInput() const;
	void FixedUpdate();
	void Update();
	void HandleOutput();

	static Game* instance_;

	std::unique_ptr<BaseWindow> window_;
	std::unique_ptr<BaseRenderer> renderer_;
	std::unique_ptr<BaseInputHandler> input_handler_;
	std::unique_ptr<BaseTime> time_;
	std::unique_ptr<TextureManager> texture_manager_;

	std::map<std::type_index, std::unique_ptr<Service>> services_{};

	// TODO Make system
	CollisionSystem collision_system_;

	Space world_space_;
	Space screen_space_;
	Space debug_space_;
};
