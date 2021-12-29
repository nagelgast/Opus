#include "pch.h"
#include "SFMLTextureManager.h"

#include "SFMLTexture.h"

std::shared_ptr<Texture> SFMLTextureManager::Load(const std::string& path)
{
	return std::make_shared<SFMLTexture>(path);
}
