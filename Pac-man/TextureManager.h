#pragma once

#include <unordered_map>

#include "Texture.h"

class TextureManager
{
public:
	//adding a texture to the manager
	void Add(std::string id, Texture* texture);
	Texture* Get(std::string id);

	void Free();

	~TextureManager();

private:
	std::unordered_map<std::string, Texture*> texturesMap;
};

