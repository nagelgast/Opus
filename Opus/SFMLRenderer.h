#pragma once

#include "BaseRenderer.h"
#include <SFML/Graphics.hpp>

#include "SFMLWindow.h"

class Space;
struct Input;
class SFMLEntityRenderer;
class Camera;
class Entity;

class SFMLRenderer final : public BaseRenderer
{
public:
	explicit SFMLRenderer(BaseWindow& window);
	void CheckDebugState(const Input& input) override;
	void Render() const override;
	void SetCamera(const Camera& camera) override;

private:
	std::unique_ptr<BaseEntityRenderer> CreateEntityRendererInstance() const override;

	void DrawEntity(const SFMLEntityRenderer* entity_renderer) const;
	void DebugDrawEntity(Entity& entity) const;

	void DrawSpace(const Space& space, std::vector<Entity*> hidden_entities) const;

	static SFMLEntityRenderer* GetRenderer(const Entity& entity);

	std::weak_ptr<Camera> camera_;
	sf::RenderWindow& window_;

	bool draw_debug_entity_;
	bool draw_debug_grid_;
};
