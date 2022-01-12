#include "pch.h"
#include "SFMLEntityRenderer.h"

#include <iostream>

#include "SFMLTexture.h"

#include "Color.h"
#include "Entity.h"
#include "Shape.h"
#include "Vector2.h"
#include "Transform.h"
#include "Particle.h"
#include "ParticleSettings.h"

void SFMLEntityRenderer::SetTexture(Texture& texture)
{
	const auto sfml_texture = static_cast<SFMLTexture*>(&texture);  // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)

	drawable_sprite_ = std::make_unique<sf::Sprite>();
	drawable_sprite_->setTexture(*sfml_texture);
}

void SFMLEntityRenderer::SetTextureRect(const Rect& rect)
{
	if (!drawable_sprite_) return;

	drawable_sprite_->setTextureRect(ConvertRect(rect));
}

void SFMLEntityRenderer::SetParticles(const ParticleSettings& settings)
{
	particle_settings_ = &settings;
	drawable_vertices_ = std::make_unique<sf::VertexArray>(sf::Quads, particle_settings_->particle_count * 4);

	const sf::IntRect& texture_rect = drawable_sprite_->getTextureRect();
	const sf::Color& color = ConvertColor(particle_settings_->color);

	for (auto i = 0; i < particle_settings_->particle_count; i++)
	{
		sf::Vertex* quad = &drawable_vertices_->operator[](i * 4);
		quad[0].texCoords = sf::Vector2f(0, 0);
		quad[1].texCoords = sf::Vector2f(texture_rect.width, 0);
		quad[2].texCoords = sf::Vector2f(texture_rect.width, texture_rect.height);
		quad[3].texCoords = sf::Vector2f(0, texture_rect.height);

		quad[0].color = color;
		quad[1].color = color;
		quad[2].color = color;
		quad[3].color = color;
	}
}

void SFMLEntityRenderer::UpdateParticles(std::vector<Particle>& particles)
{
	const auto size = static_cast<float>(particle_settings_->size);

	for (std::size_t i = 0; i < particles.size(); i++)
	{
		const auto& particle = particles[i];

		auto particle_size = size;

		if (particle_settings_->use_scale)
		{
			auto progress = 1 - particle.lifetime / particle_settings_->lifetime;
			auto delta = particle_settings_->scale_end - particle_settings_->scale_start;
			auto scale = progress * delta;
			particle_size  = size * (particle_settings_->scale_start + scale);
		}


		sf::Vertex* quad = &drawable_vertices_->operator[](i * 4);

		const auto half_size = particle_size * 0.5f;
		sf::Vector2f corner_pos = {particle.position.x - half_size, particle.position.y - half_size};

		quad[0].position = corner_pos;
		quad[1].position = {corner_pos.x + particle_size, corner_pos.y};
		quad[2].position = {corner_pos.x + particle_size, corner_pos.y + particle_size };
		quad[3].position = {corner_pos.x, corner_pos.y + particle_size };
	}
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
	drawable_shape_->setFillColor(ConvertColor(color));
}

void SFMLEntityRenderer::SetMirrored(const bool& value)
{
	mirrored_ = value;
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
		drawable_shape_->setPosition(draw_origin);
		target.draw(*drawable_shape_, states);
	}
	else if (drawable_sprite_)
	{
		if (drawable_vertices_)
		{
			states.texture = drawable_sprite_->getTexture();
			target.draw(*drawable_vertices_, states);
			//states.texture = nullptr;
		}
		else
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
			drawable_sprite_->setPosition({ pos.x - sprite_offset.x, pos.y - sprite_offset.y });
			target.draw(*drawable_sprite_, states);
		}
	}
	else if(drawable_text_)
	{
		drawable_text_->setPosition(draw_origin);
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

sf::Color SFMLEntityRenderer::ConvertColor(const Color& color)
{
	return {
		static_cast<sf::Uint8>(color.r * 255),
		static_cast<sf::Uint8>(color.g * 255),
		static_cast<sf::Uint8>(color.b * 255),
		static_cast<sf::Uint8>(color.a * 255)
	};
}
