#pragma once

#include "BaseEntityRenderer.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Entity;

class SFMLEntityRenderer final : public BaseEntityRenderer, public sf::Drawable
{
public:
	void SetSize(float width, float height) override;

	void SetSprite(Sprite sprite) override;
	void SetShape(const Shape& shape) override;
	void SetColor(const Color& color) override;

	void Reset() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void DrawBox(sf::RenderTarget& target, sf::RenderStates states, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color) const;

	sf::Vector2f scale_;

	std::unique_ptr<sf::Texture> texture_;
	std::unique_ptr<sf::Sprite> drawable_sprite_;
	std::unique_ptr<sf::Shape> drawable_shape_;
};
