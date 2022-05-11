#pragma once
#include "TileGraph.h"
#include "TextureManager.h"

#include "Wall.h"
#include "Point.h"
#include "Pacman.h"
#include "Ghost.h"
//#include "GameObject.h"
class GameObject;

class Map
{
public:


	Map(TileGraph* tileGraph, TextureManager* textureManager);

	// Load map file and generate all objects
	bool Load(std::string path);

	// Setting pose of object
	void SettingTo(std::vector<GameObject*>& vector);

private:
	std::vector<GameObject*> objectVector;

	TileGraph* pTileGraph;
	TextureManager* pTextureManager;
};