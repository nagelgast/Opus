#pragma once

#include "BaseRenderer.h"
#include <SFML/Graphics.hpp>

class Entity;

class SFMLRenderer final : public BaseRenderer
{
public:
	explicit SFMLRenderer(sf::RenderWindow&);
	
	void Render(const std::vector<std::shared_ptr<Entity>>& entities) const override;

private:
	void SetCamera(BaseCamera& camera) override;
	std::unique_ptr<BaseCamera> CreateCamera() const override;
	std::unique_ptr<BaseEntityRenderer> CreateEntityRendererInstance() const override;


	sf::RenderWindow& window_;
	sf::View view_;
};

