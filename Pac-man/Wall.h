#pragma once

#include "GameObject.h"
#include "Texture.h"
#include "TileGraph.h"


class Wall : public GameObject
{
public:

	Wall(Tile* tile, Texture* texture);
	~Wall();


	void SetTile(Tile* newTile);

	// Mark the object to be deleted
	void Delete();

	// Renders the wall
	void Render();

	SDL_Rect GetCollider();

	SDL_Point GetPosition();

	Tile* GetTile();

private:
	bool CheckForWall(Tile* tile);

	Texture* wallTexture;
	//int connections;
	static SDL_Rect textureClips[16];

	SDL_Point position;

	Tile* currTile;

	SDL_Rect collider;
};

