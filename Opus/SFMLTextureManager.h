#pragma once
#include "TextureManager.h"
class SFMLTextureManager :
    public TextureManager
{
protected:
	std::shared_ptr<Texture> Load(const std::string& path) override;
};

