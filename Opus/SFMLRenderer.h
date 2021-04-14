#pragma once

#include "BaseRenderer.h"
#include <SFML/Graphics.hpp>

#include "SFMLWindow.h"

class Camera;
class Entity;

class SFMLRenderer final : public BaseRenderer
{
public:
	explicit SFMLRenderer(const std::shared_ptr<BaseWindow>& window);
	void Render(const std::vector<std::shared_ptr<Entity>>& entities) const override;
	void SetCamera(const std::shared_ptr<Camera>& camera) override;

private:
	std::unique_ptr<BaseEntityRenderer> CreateEntityRendererInstance() const override;

	std::weak_ptr<Camera> camera_;
	sf::RenderWindow& window_;
};
