#pragma once

#include "BaseRenderer.h"
#include <SFML/Graphics.hpp>

#include "SFMLWindow.h"

class SFMLEntityRenderer;
class Camera;
class Entity;

class SFMLRenderer final : public BaseRenderer
{
public:
	explicit SFMLRenderer(BaseWindow& window);
	void Render(const std::vector<std::shared_ptr<Entity>>& entities) const override;
	void SetCamera(const Camera& camera) override;

private:
	std::unique_ptr<BaseEntityRenderer> CreateEntityRendererInstance() const override;

	void DrawEntity(SFMLEntityRenderer* entity_renderer) const;

	std::weak_ptr<Camera> camera_;
	sf::RenderWindow& window_;
};

