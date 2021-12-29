#pragma once

#include <map>
#include <memory>
#include <string>

class Texture;

class TextureManager
{
public:
	virtual ~TextureManager() = default;

	std::shared_ptr<Texture> Get(const std::string& path);
protected:
	virtual std::shared_ptr<Texture> Load(const std::string& path) = 0;
private:
	std::map<std::string, std::shared_ptr<Texture>> textures_;
};
