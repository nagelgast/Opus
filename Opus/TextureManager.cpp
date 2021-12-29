#include "pch.h"
#include "TextureManager.h"

#include "Texture.h"

std::shared_ptr<Texture> TextureManager::Get(const std::string& path)
{
	if (textures_.count(path))
	{
		return textures_[path];
	}

	textures_[path] = Load(path);
	return textures_[path];
}
