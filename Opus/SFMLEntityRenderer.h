#pragma once

#include "BaseEntityRenderer.h"
#include <SFML/Graphics.hpp>
#include <memory>

#include "ParticleSettings.h"

struct ParticleSettings;
struct Particle;
class Entity;

class SFMLEntityRenderer final : public BaseEntityRenderer, public sf::Drawable
{
public:
	void SetTexture(Texture& texture) override;
	void SetTextureRect(const Rect& rect) override;

	void SetParticles(const ParticleSettings& settings) override;
	void UpdateParticles(std::vector<Particle>& particles) override;

	void SetShape(const Shape& shape) override;
	void SetText(const char* text) override;
	
	Rect GetTextureRect() const override;
	float GetWidth() override;
	
	void SetColor(const Color& color) override;

	void SetMirrored(const bool& value) override;

	void Reset() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	static void DrawRect(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
	static void DrawCircle(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& position, const float radius, const sf::Color& color);
	static void DrawLine(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color& color);
private:
	sf::Vector2f scale_;

	bool mirrored_ = false;

	// TODO Do these need to be smart pointers or can I just store them here?
	std::unique_ptr<sf::Text> drawable_text_;
	std::unique_ptr<sf::Shape> drawable_shape_;
	std::unique_ptr<sf::VertexArray> drawable_vertices_;

	// TODO Make separate ParticleRenderer class
	std::unique_ptr<sf::Sprite> drawable_sprite_;
	const ParticleSettings* particle_settings_ = nullptr;

	// TODO Store in font manager
	sf::Font font_;

	sf::IntRect ConvertRect(const Rect& rect);
};
