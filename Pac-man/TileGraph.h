#pragma once

#include <array>
#include "Tile.h"

class Pacman;
class Point;

class TileGraph
{
public:
	TileGraph();
	TileGraph(int w, int h);
	~TileGraph();

	Tile* GetTileAt(int x, int y);

	std::array<Tile*, 4> Get_Neighbours(Tile* tile);
	Pacman* GetPacman();
	Point* GetPoint();

private:
	Tile* tiles;
	int width;
	int height;

	int GetIndex(int x, int h);
};

