#include "pch.h"
#include "SFMLRenderer.h"

#include "Camera.h"
#include "Entity.h"
#include "SFMLEntityRenderer.h"

SFMLRenderer::SFMLRenderer(const std::shared_ptr<BaseWindow>& window) : window_(dynamic_cast<SFMLWindow&>(*window).GetWindow())
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
		const auto position = camera->entity_->GetPosition();
		window_.setView(sf::View({position.x, position.y}, static_cast<sf::Vector2f>(window_.getSize())));
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
