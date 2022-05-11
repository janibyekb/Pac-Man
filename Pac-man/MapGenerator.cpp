#include "MapGenerator.h"
#include <fstream>


MapGenerator::MapGenerator(TileGraph* tileGraph, TextureManager* textureManager)
{
	pTileGraph = tileGraph;
	pTextureManager = textureManager;
	GameObject::tileGraph = tileGraph;

}



bool MapGenerator::Load(std::string path)
{
	std::fstream file;

	file.open(path.c_str(), std::ios::in);

	if (file.is_open() == false)
		return false;

	std::string line;

	int x = 0;
	int y = 0;

	// read by line by line
	while (std::getline(file, line)) {
		// taking lines to one vector line
		std::vector<char> chars(line.begin(), line.end());
		
		for (unsigned int x = 0; x < chars.size(); x++) {
			GameObject* newObject = NULL;
			Tile* tile = pTileGraph->GetTileAt(x, y);

			switch (chars[x])
			{
			case 'x':
				newObject = new Wall(tile, pTextureManager->Get("wall"));
				break;
			case '.':
				newObject = new Point(tile, pTextureManager->Get("point"));
				break;
			case 'p':
				newObject = new Pacman(tile, pTextureManager->Get("pacman"));
				break;
			case 'E':
				newObject = new Ghost(tile, pTextureManager->Get("ghost"));
				break;
			}

			// If the object was created, add it to the vector
			if (newObject != NULL)
				objectVector.push_back(newObject);
		}

		y++;
	}

	file.close();

}

void MapGenerator::SettingTo(std::vector<GameObject*>& vector)
{
	for (unsigned int i = 0; i < objectVector.size(); i++) {
		vector.push_back(objectVector[i]);
	}
}