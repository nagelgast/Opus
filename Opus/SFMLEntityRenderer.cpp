#include "pch.h"
#include "SFMLEntityRenderer.h"

#include "Entity.h"
#include "Shape.h"
#include "Vector2.h"
#include "Transform.h"

void SFMLEntityRenderer::SetSize(float width, float height)
{
	scale_ = {width, height};
	if (drawable_shape_)
	{
		drawable_shape_->setScale(scale_);
	}

	if (drawable_sprite_)
	{
		const auto& rect = drawable_sprite_->getTextureRect();
		sf::Vector2f sprite_scale = { width / rect.width, height / rect.height };
		drawable_sprite_->setScale(sprite_scale);
	}
}

void SFMLEntityRenderer::SetSprite(const std::string& path, int left, int top, int width, int height)
{
	texture_ = std::make_unique<sf::Texture>();
	texture_->loadFromFile(path);

	drawable_sprite_ = std::make_unique<sf::Sprite>();
	drawable_sprite_->setTexture(*texture_);
	drawable_sprite_->setTextureRect({ left, top, width, height });
}

void SFMLEntityRenderer::SetShape(const Shape shape, float r, float g, float b, float a)
{
	switch (shape)
	{
	case Shape::kCircle:
		drawable_shape_ = std::make_unique<sf::CircleShape>(0.5f);
		break;
	case Shape::kSquare:
		sf::Vector2f length = { 1, 1 };
		drawable_shape_ = std::make_unique<sf::RectangleShape>(length);
		break;
	}

	drawable_shape_->setFillColor(sf::Color(
		static_cast<sf::Uint8>(r * 255),
		static_cast<sf::Uint8>(g * 255),
		static_cast<sf::Uint8>(b * 255),
		static_cast<sf::Uint8>(a * 255)
	));
}

void SFMLEntityRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	const auto& corner = entity_->GetTransform().GetPosition() - entity_->GetTransform().GetOrigin();
	const sf::Vector2f draw_pos = {corner.x, corner.y};
	//DrawBox(target, states, draw_pos, scale_, sf::Color::Magenta);

	if (drawable_shape_)
	{
		drawable_shape_->setPosition(draw_pos);
		target.draw(*drawable_shape_, states);
	}

	if (drawable_sprite_)
	{
		drawable_sprite_->setPosition(draw_pos);
		target.draw(*drawable_sprite_, states);
	}
}

void SFMLEntityRenderer::DrawBox(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& position,
	const sf::Vector2f& size, const sf::Color& color) const
{
	sf::RectangleShape box;
	box.setSize(size);
	box.setPosition(position);
	box.setFillColor(sf::Color::Transparent);
	box.setOutlineThickness(1);
	box.setOutlineColor(color);
	target.draw(box, states);
}
