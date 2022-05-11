#pragma once

#include <SDL.h>
#include "Texture.h"
#include "GameObject.h"
#include "Tile.h"
#include "TileGraph.h"
#include "Pacman.h"



class Ghost : public GameObject
{
public:
	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	static const int Velocity = 1;

	Ghost(Tile* tile, Texture* texture);
	~Ghost();


	void SetTile(Tile* newTile);

	// Sets the next tile (to which pacman will go)
	void SetNextTile(Tile* newNextTile);

	void Update();

	void Render();

	void Delete();

	SDL_Rect GetCollider();

	SDL_Point GetPosition();

	Tile* GetTile();

	Tile* GetNextTile();


private:
	bool CheckForCollision(const SDL_Rect& otherCollider);

	bool CheckForCollision(const SDL_Rect& collider, const SDL_Rect& otherCollider);

	static bool isNoWall(Tile* tile);

	Texture* ghostTexture;

	Direction moveDir;
	Direction nextDir;

	SDL_Point position;

	Tile* currTile;
	Tile* nextTile;

	std::vector<Tile*> path;
	
	SDL_Rect collider;
};

