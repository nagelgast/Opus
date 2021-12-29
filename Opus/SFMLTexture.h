#pragma once

#include <SFML/Graphics.hpp>

#include "Texture.h"

class SFMLTexture : public Texture, public sf::Texture
{
public:
	explicit SFMLTexture(const std::string& path);
};

