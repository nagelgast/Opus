#include "pch.h"
#include "SFMLEntityRenderer.h"

#include <iostream>



#include "Color.h"
#include "Entity.h"
#include "Shape.h"
#include "Sprite.h"
#include "Vector2.h"
#include "Transform.h"

void SFMLEntityRenderer::SetSprite(const Sprite sprite)
{
	texture_ = std::make_unique<sf::Texture>();
	texture_->loadFromFile(sprite.path);

	drawable_sprite_ = std::make_unique<sf::Sprite>();
	drawable_sprite_->setTexture(*texture_);
	drawable_sprite_->setTextureRect({
		static_cast<int>(sprite.rect.left),
		static_cast<int>(sprite.rect.top),
		static_cast<int>(sprite.rect.width),
		static_cast<int>(sprite.rect.height)
	});
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

void SFMLEntityRenderer::Reset()
{
	texture_ = nullptr;
	drawable_sprite_ = nullptr;
	drawable_shape_ = nullptr;
}

void SFMLEntityRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	const auto& transform = entity_->GetTransform();
	const auto scale = transform.GetScale();
	const sf::Vector2f draw_scale = {scale.x, scale.y};
	const auto& corner = transform.GetPosition() - transform.GetOrigin();
	const sf::Vector2f draw_pos = {corner.x, corner.y};

	if (drawable_shape_)
	{
		drawable_shape_->setScale(draw_scale);
		drawable_shape_->setPosition(draw_pos);
		target.draw(*drawable_shape_, states);
	}

	if (drawable_sprite_)
	{
		// TODO Optimize this
		const auto& rect = drawable_sprite_->getTextureRect();
		const sf::Vector2f sprite_scale = {
			draw_scale.x / static_cast<int>(rect.width), draw_scale.y / static_cast<int>(rect.height)
		};

		drawable_sprite_->setScale(sprite_scale);
		drawable_sprite_->setPosition(draw_pos);
		target.draw(*drawable_sprite_, states);
	}

	if(drawable_text_)
	{
		drawable_text_->setPosition(draw_pos);
		target.draw(*drawable_text_, states);
	}
}

void SFMLEntityRenderer::DrawBox(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& position,
                                 const sf::Vector2f& size, const sf::Color& color)
{
	sf::RectangleShape box;
	box.setSize(size);
	box.setPosition(position);
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineThickness(1);
	box.setOutlineColor(color);
	target.draw(box, states);
}
