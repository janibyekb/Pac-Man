#pragma once

#include <SDL.h>
#include "Texture.h"
#include "GameObject.h"
#include "Tile.h"
#include "TileGraph.h"
#include "Point.h"

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Pacman : public GameObject
{
public:

	//bool static alive;
	int score;
	bool isWon;
	bool isLost;


	static const int Velocity = 2;

	Pacman(Tile* tile, Texture* texture);
	~Pacman();

	//Setting tile
	void SetTile(Tile* newTile);
	// setting the next tile
	void SetNextTile(Tile* newNextTile);

	void HandleEvents(SDL_Event* event);

	void Update();

	void Render();

	void Delete();

	Direction GetMoveDirection();

	SDL_Rect GetCollider();

	SDL_Point GetPosition();

	Tile* GetTile();

	Tile* GetNextTile();

private:

	bool isMoveable(Direction direction);

	//Checking if pacman is colliding with other collider
	bool CheckForCollision(const SDL_Rect& otherCollider);

	// Checking if given collider is colliding with another collider
	bool CheckForCollision(const SDL_Rect& collider, const SDL_Rect& otherCollider);

	Texture* pacmanTexture;

	Direction moveDir;
	Direction nextDir;

	SDL_Point position;

	Tile* currTile;
	Tile* nextTile;

	SDL_Rect collider;
};

//int Pacman::point = 0;

