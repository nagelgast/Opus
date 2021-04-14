#include "SFMLRenderer.h"


#include "Camera.h"
#include "Entity.h"
#include "SFMLEntityRenderer.h"

SFMLRenderer::SFMLRenderer(sf::RenderWindow& window) : window_(window)
{
}

void SFMLRenderer::Render(const std::vector<std::shared_ptr<Entity>>& entities) const
{
	window_.clear();
	if(camera_.expired())
	{
		window_.setView(window_.getDefaultView());
	}
	else
	{
		const auto camera = camera_.lock();
		window_.setView(sf::View(camera->entity_->GetPosition(), static_cast<sf::Vector2f>(window_.getSize())));
	}
	
	for (const auto& entity : entities)
	{
		if (entity->HasRenderer())
		{
			// Static cast is used for performance. If the engine was initialized correctly the cast is guaranteed to succeed.
			const auto* entity_renderer = static_cast<SFMLEntityRenderer*>(entity->GetRenderer());  // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
			window_.draw(*entity_renderer);
		}
	}
	window_.display();
}

void SFMLRenderer::SetCamera(const std::shared_ptr<Camera>& camera)
{
	camera_ = camera;
}


std::unique_ptr<BaseEntityRenderer> SFMLRenderer::CreateEntityRendererInstance() const
{
	return std::make_unique<SFMLEntityRenderer>();
}
