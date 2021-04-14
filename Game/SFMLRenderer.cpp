#include "SFMLRenderer.h"

#include "Entity.h"
#include "SFMLEntityRenderer.h"
#include "BaseCamera.h"
#include "SFMLCamera.h"


SFMLRenderer::SFMLRenderer(sf::RenderWindow& window) : window_(window)
{
	view_ = window.getDefaultView();
}

void SFMLRenderer::Render(const std::vector<std::shared_ptr<Entity>>& entities) const
{
	window_.clear();
	window_.setView(view_);
	for (const auto& entity : entities)
	{
		if (entity->HasRenderer())
		{
			auto entity_renderer = static_cast<SFMLEntityRenderer*>(entity->GetRenderer());
			window_.draw(*entity_renderer);
		}
	}
	window_.display();
}

void SFMLRenderer::SetCamera(BaseCamera& camera)
{
	view_ = sf::View(camera.GetPosition(), {1024,768});
}

std::unique_ptr<BaseCamera> SFMLRenderer::CreateCamera() const
{
	return std::make_unique<SFMLCamera>();
}

std::unique_ptr<BaseEntityRenderer> SFMLRenderer::CreateEntityRendererInstance() const
{
	return std::make_unique<SFMLEntityRenderer>();
}
