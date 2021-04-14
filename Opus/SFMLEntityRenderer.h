#pragma once

#include "BaseEntityRenderer.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Entity;

class SFMLEntityRenderer : public BaseEntityRenderer, public sf::Drawable
{
public:
	void SetSize(float width, float height) override;

	void SetSprite(const std::string& path, int left, int top, int width, int height) override;
	void SetShape(Shape shape, float r, float g, float b, float a) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void DrawBox(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color) const;

	sf::Vector2f scale_;

	std::unique_ptr<sf::Texture> texture_;
	std::unique_ptr<sf::Sprite> drawable_sprite_;
	std::unique_ptr<sf::Shape> drawable_shape_;
};