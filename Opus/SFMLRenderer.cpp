#include "pch.h"
#include "SFMLRenderer.h"

#include "Camera.h"
#include "CircleCollider.h"
#include "Entity.h"
#include "Input.h"
#include "RectCollider.h"
#include "SFMLEntityRenderer.h"
#include "Transform.h"
#include "../Game/Interactable.h"

SFMLRenderer::SFMLRenderer(BaseWindow& window) :
	window_(dynamic_cast<SFMLWindow&>(window).GetWindow()),
    draw_debug_entity_(false),
    draw_debug_grid_(false)
{
}

void SFMLRenderer::CheckDebugState(const Input& input)
{
	// TODO this these elsewhere
	if (input.f1.pressed)
	{
		draw_debug_entity_ = !draw_debug_entity_;
	}
	if (input.f2.pressed)
	{
		draw_debug_grid_ = !draw_debug_grid_;
	}
}

void SFMLRenderer::Render() const
{
	window_.clear();

	if(!camera_.expired())
	{
		const auto camera = camera_.lock();
		const auto position = camera->entity_->GetTransform().GetPosition();
		window_.setView(sf::View({position.x, position.y}, static_cast<sf::Vector2f>(window_.getSize())));
	}

	// TODO Make this part of a separate debug render class
	if (draw_debug_grid_)
	{
		for (int i = 0; i < 20; i++)
		{
			constexpr int grid_spacing = 100;
			constexpr int grid_brightness = 20;
			const sf::Color grid_color = {grid_brightness, grid_brightness, grid_brightness};
			auto cur_pos = static_cast<float>(i * grid_spacing);
			SFMLEntityRenderer::DrawLine(window_, sf::RenderStates::Default, { 0, cur_pos}, { 2000, cur_pos}, grid_color);
			SFMLEntityRenderer::DrawLine(window_, sf::RenderStates::Default, { cur_pos, 0 }, { cur_pos, 2000 }, grid_color);
		}
	}

	const std::vector<Entity*> hidden_entities{};
	DrawSpace(Game::GetWorldSpace(), hidden_entities);
	window_.setView(window_.getDefaultView());
	DrawSpace(Game::GetScreenSpace(), hidden_entities);

	// TODO Implement solution for drawing debug rendering for invisible entities
	for (const auto& entity : hidden_entities)
	{
		DebugDrawEntity(*entity);
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

void SFMLRenderer::DrawEntity(const SFMLEntityRenderer* entity_renderer) const
{
	window_.draw(*entity_renderer);
}

void SFMLRenderer::DebugDrawEntity(Entity& entity) const
{
	if (!draw_debug_entity_) return;

	// Draw interactable bounds
	auto* interactable = entity.GetComponent<Interactable>();
	if (interactable)
	{
		const auto bounds = interactable->GetGlobalBounds();
		SFMLEntityRenderer::DrawRect(window_, sf::RenderStates::Default, { bounds.left, bounds.top }, { bounds.width, bounds.height }, sf::Color::Cyan);
	}

	// Draw collider bounds
	auto* rect_collider = entity.GetComponent<RectCollider>();
	if (rect_collider)
	{
		const auto bounds = rect_collider->GetGlobalBounds();
		SFMLEntityRenderer::DrawRect(window_, sf::RenderStates::Default, { bounds.left, bounds.top }, { bounds.width, bounds.height }, sf::Color::Magenta);
	}
	auto* circle_collider = entity.GetComponent<CircleCollider>();
	if (circle_collider)
	{
		const auto collider_position = circle_collider->GetGlobalPosition();
		const auto radius = circle_collider->GetGlobalRadius();
		SFMLEntityRenderer::DrawCircle(window_, sf::RenderStates::Default, { collider_position.x, collider_position.y }, radius, sf::Color::Magenta);
	}

	// Draw position
	const auto& position = entity.GetTransform().GetPosition();
	SFMLEntityRenderer::DrawLine(window_, sf::RenderStates::Default, { position.x - 10, position.y }, { position.x + 10, position.y }, sf::Color::White);
	SFMLEntityRenderer::DrawLine(window_, sf::RenderStates::Default, { position.x, position.y - 10 }, { position.x, position.y + 10 }, sf::Color::White);

}

void SFMLRenderer::DrawSpace(const Space& space, std::vector<Entity*> hidden_entities) const
{
	const auto& entities = space.GetEntities();
	for (const auto& entity : entities)
	{
		if (entity->ShouldRender())
		{
			const auto entity_renderer = GetRenderer(*entity);
			DrawEntity(entity_renderer);
			DebugDrawEntity(*entity_renderer->entity_);
		}
		else
		{
			hidden_entities.push_back(entity.get());
		}
	}
}

SFMLEntityRenderer* SFMLRenderer::GetRenderer(const Entity& entity)
{
	// Static cast is used for performance. If the engine was initialized correctly the cast is guaranteed to succeed.
	const auto entity_renderer = static_cast<SFMLEntityRenderer*>(entity.GetRenderer());  // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
	return entity_renderer;
}
