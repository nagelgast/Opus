#include "pch.h"
#include "SFMLTexture.h"

SFMLTexture::SFMLTexture(const std::string& path)
{
	loadFromFile(path);
}
