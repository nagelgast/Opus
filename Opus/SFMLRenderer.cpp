#include "pch.h"
#include "SFMLRenderer.h"

#include "Camera.h"
#include "CircleCollider.h"
#include "Entity.h"
#include "RectCollider.h"
#include "SFMLEntityRenderer.h"
#include "Transform.h"
#include "../Game/Interactable.h"

const bool kDrawDebug = false;

SFMLRenderer::SFMLRenderer(BaseWindow& window) : window_(dynamic_cast<SFMLWindow&>(window).GetWindow())
{
}

void SFMLRenderer::Render(const std::vector<std::shared_ptr<Entity>>& entities) const
{
	// TODO Actively keep track of renderer and UI entities
	std::vector<SFMLEntityRenderer*> world_entity_renderers{};
	std::vector<SFMLEntityRenderer*> screen_entity_renderers{};

	for (const auto& entity : entities)
	{
		if (entity->ShouldRender())
		{
			// Static cast is used for performance. If the engine was initialized correctly the cast is guaranteed to succeed.
			const auto entity_renderer = static_cast<SFMLEntityRenderer*>(entity->GetRenderer());  // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)

			if(entity_renderer->in_world_space_)
			{
				world_entity_renderers.push_back(entity_renderer);
			}
			else
			{
				screen_entity_renderers.push_back(entity_renderer);
			}
		}
	}

	window_.clear();
	
	if(!camera_.expired())
	{
		const auto camera = camera_.lock();
		const auto position = camera->entity_->GetTransform().GetPosition();
		window_.setView(sf::View({position.x, position.y}, static_cast<sf::Vector2f>(window_.getSize())));
	}

	for (const auto& entity_renderer : world_entity_renderers)
	{
		DrawEntity(entity_renderer);
	}

	window_.setView(window_.getDefaultView());

	for (const auto& entity_renderer : screen_entity_renderers)
	{
		DrawEntity(entity_renderer);
	}
	
	window_.display();
}

void SFMLRenderer::SetCamera(const Camera& camera)
{
	// TODO For some reason, this tanks debugging speed???
	//camera_ = camera;
}


std::unique_ptr<BaseEntityRenderer> SFMLRenderer::CreateEntityRendererInstance() const
{
	return std::make_unique<SFMLEntityRenderer>();
}

void SFMLRenderer::DrawEntity(SFMLEntityRenderer* entity_renderer) const
{
	window_.draw(*entity_renderer);
	
	if (kDrawDebug)
	{
		auto entity = entity_renderer->entity_;
		auto& transform = entity->GetTransform();
		auto position = transform.GetPosition() - transform.GetOrigin();
		auto scale = transform.GetScale();
		SFMLEntityRenderer::DrawRect(window_, sf::RenderStates::Default, {position.x, position.y}, {scale.x, scale.y}, sf::Color::Red);

		auto* interactable = entity->GetComponent<Interactable>();
		if (interactable)
		{
			const auto bounds = interactable->GetGlobalBounds();
			SFMLEntityRenderer::DrawRect(window_, sf::RenderStates::Default, { bounds.left, bounds.top }, { bounds.width, bounds.height }, sf::Color::Cyan);
		}
		
		auto* rect_collider = entity->GetComponent<RectCollider>();
		if (rect_collider)
		{
			const auto bounds = rect_collider->GetGlobalBounds();
			SFMLEntityRenderer::DrawRect(window_, sf::RenderStates::Default, { bounds.left, bounds.top }, { bounds.width, bounds.height }, sf::Color::Magenta);
		}

		auto* circle_collider = entity->GetComponent<CircleCollider>();
		if (circle_collider)
		{
			const auto position = circle_collider->GetGlobalPosition();
			const auto radius = circle_collider->GetGlobalRadius();
			SFMLEntityRenderer::DrawCircle(window_, sf::RenderStates::Default, {position.x, position.y}, radius, sf::Color::Magenta);
		}
	}
}
