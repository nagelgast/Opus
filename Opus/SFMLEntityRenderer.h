#pragma once

#include "BaseEntityRenderer.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Entity;

class SFMLEntityRenderer final : public BaseEntityRenderer, public sf::Drawable
{
public:
	void SetSprite(const Sprite sprite) override;
	void SetTextureRect(const Rect& rect) override;

	void SetShape(const Shape& shape) override;
	void SetText(const char* text) override;
	
	Rect GetTextureRect() const override;
	float GetWidth() override;
	
	void SetColor(const Color& color) override;

	void Mirror() override;

	void Reset() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	static void DrawRect(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);
	static void DrawCircle(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& position, const float radius, const sf::Color& color);
	static void DrawLine(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color& color);
private:
	sf::Vector2f scale_;

	bool mirrored_ = false;

	std::unique_ptr<sf::Sprite> drawable_sprite_;
	std::unique_ptr<sf::Text> drawable_text_;
	std::unique_ptr<sf::Shape> drawable_shape_;

	// TODO Store in font manager
	sf::Font font_;

	sf::IntRect ConvertRect(const Rect& rect);
};
