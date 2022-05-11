#pragma once

#include <SDL.h>

class Pacman;
class Wall;
class Point;
class Ghost;


class Tile
{
public:
	const static int Width = 25;
	const static int Height = 25;

	Tile();
	Tile(int x, int y);
    // setting  pointer to the particular object in tile

	void SetPacman(Pacman* pacman); 

	void SetWall(Wall* wall);

	void SetPoint(Point* wall);

	void SetGhost(Ghost* blinky);

	void SetPos(int x, int y);

	Pacman* GetPacman();
	//Point* GetPoint();

	Wall* GetWall();

	Point* GetPoint();

	Ghost* GetGhost();

	SDL_Point GetPosition();

private:
	SDL_Point position;

	Pacman* pPacman;
	Wall* pWall;
	Point* pPoint;
	Ghost* pGhost;
};