#include "TextureManager.h"
#include <unordered_map>

void TextureManager::Add(std::string id, Texture* texture)
{
	texturesMap[id] = texture;
}


Texture* TextureManager::Get(std::string id)
{
	return texturesMap[id];
}

void TextureManager::Free()
{
	for (auto& tr : texturesMap) {
		//texturesMap.erase(tr.first);

	}


}

TextureManager::~TextureManager()
{
	Free();
}
