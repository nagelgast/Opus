#include "pch.h"
#include "SFMLEntityRenderer.h"

#include <iostream>

#include "SFMLTexture.h"

#include "Color.h"
#include "Entity.h"
#include "Game.h"
#include "Shape.h"
#include "Sprite.h"
#include "Vector2.h"
#include "Transform.h"

void SFMLEntityRenderer::SetSprite(const Sprite sprite)
{
	const auto& texture = static_cast<SFMLTexture*>(Game::GetTextureManager().Get(sprite.path).get());  // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)

	drawable_sprite_ = std::make_unique<sf::Sprite>();
	drawable_sprite_->setTexture(*texture);
	SetTextureRect(sprite.rect);
}

void SFMLEntityRenderer::SetTextureRect(const Rect& rect)
{
	if (!drawable_sprite_) return;

	drawable_sprite_->setTextureRect(ConvertRect(rect));
}

void SFMLEntityRenderer::SetShape(const Shape& shape)
{
	switch (shape)
	{
	case Shape::kCircle:
		drawable_shape_ = std::make_unique<sf::CircleShape>(0.5f);
		break;
	case Shape::kSquare:
		sf::Vector2f length = {1, 1};
		drawable_shape_ = std::make_unique<sf::RectangleShape>(length);
		break;
	}
}

void SFMLEntityRenderer::SetText(const char* text)
{
	if(!font_.loadFromFile("../Game/Fonts/Fontin-Regular.ttf"))
	{
		std::cout << "Failed to load font.\n";
	}
	drawable_text_ = std::make_unique<sf::Text>(text, font_, 18);
}

Rect SFMLEntityRenderer::GetTextureRect() const
{
	if (!drawable_sprite_) return {};

	const auto& rect = drawable_sprite_->getTextureRect();
	return { rect.left, rect.top, rect.width, rect.height };
}

float SFMLEntityRenderer::GetWidth()
{
	if(drawable_text_)
	{
		return drawable_text_->getGlobalBounds().width;
	}

	return 0;
}

void SFMLEntityRenderer::SetColor(const Color& color)
{
	drawable_shape_->setFillColor(sf::Color(
		static_cast<sf::Uint8>(color.r * 255),
		static_cast<sf::Uint8>(color.g * 255),
		static_cast<sf::Uint8>(color.b * 255),
		static_cast<sf::Uint8>(color.a * 255)
	));
}

void SFMLEntityRenderer::Mirror()
{
	mirrored_ = !mirrored_;
}

void SFMLEntityRenderer::Reset()
{
	drawable_sprite_ = nullptr;
	drawable_shape_ = nullptr;
}

void SFMLEntityRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	const auto& transform = entity_->GetTransform();
	const auto scale = transform.GetScale();
	const auto& pos = transform.GetPosition();
	const sf::Vector2f draw_pos = { pos.x, pos.y };
	const sf::Vector2f draw_scale = { scale.x, scale.y };
	const auto draw_offset = draw_scale * 0.5f;
	const auto draw_origin = draw_pos - draw_offset;

	if (drawable_shape_)
	{
		drawable_shape_->setScale(draw_scale);
		drawable_shape_->setPosition(draw_pos);
		target.draw(*drawable_shape_, states);
	}

	if (drawable_sprite_)
	{
		auto& sprite_rect = drawable_sprite_->getTextureRect();
		auto sprite_offset = draw_offset;
		sprite_offset.x *= static_cast<float>(sprite_rect.width);
		sprite_offset.y *= static_cast<float>(sprite_rect.height);
		auto sprite_scale = draw_scale;

		if (mirrored_)
		{
			sprite_scale.x *= -1;
			sprite_offset.x *= -1;
		}

		drawable_sprite_->setScale(sprite_scale);
		drawable_sprite_->setPosition({ pos.x - sprite_offset.x, pos.y - sprite_offset.y});
		target.draw(*drawable_sprite_, states);
	}

	if(drawable_text_)
	{
		drawable_text_->setPosition(draw_pos);
		target.draw(*drawable_text_, states);
	}
}

void SFMLEntityRenderer::DrawRect(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& position,
                                 const sf::Vector2f& size, const sf::Color& color)
{
	sf::RectangleShape rect;
	rect.setSize(size);
	rect.setPosition(position);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1);
	rect.setOutlineColor(color);
	target.draw(rect, states);
}

void SFMLEntityRenderer::DrawCircle(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& position,
	const float radius, const sf::Color& color)
{
	sf::CircleShape circle;
	circle.setRadius(radius);
	circle.setPosition(position);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(1);
	circle.setOutlineColor(color);
	target.draw(circle, states);
}

void SFMLEntityRenderer::DrawLine(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& start,
	const sf::Vector2f& end, const sf::Color& color)
{
	const sf::Vertex line[] =
	{
		sf::Vertex(start, color),
		sf::Vertex(end, color)
	};

	target.draw(line, 2, sf::Lines);
}

sf::IntRect SFMLEntityRenderer::ConvertRect(const Rect& rect)
{
	return {
		static_cast<int>(rect.left),
		static_cast<int>(rect.top),
		static_cast<int>(rect.width),
		static_cast<int>(rect.height)
	};
}