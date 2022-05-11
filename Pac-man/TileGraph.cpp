#include "TileGraph.h"
#include <algorithm>

TileGraph::TileGraph()
{
	tiles = NULL;

	width = 0;
	height = 0;
}

TileGraph::~TileGraph()
{
	delete[] tiles;
}

TileGraph::TileGraph(int w, int h)
{
	// Create a dynamic array of Tiles
	tiles = new Tile[w * h];

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			tiles[x + (y * w)].SetPos(x, y);
		}
	}

	width = w;
	height = h;
}



Tile* TileGraph::GetTileAt(int x, int y)
{
	int index = GetIndex(x, y);
	if (index < 0)
		return NULL;

	return &tiles[index];
}

Pacman* TileGraph::GetPacman()
{
	for (int i = 0; i < (width * height); i++) {
		Tile tile = tiles[i];

		if (tile.GetPacman() != NULL)
			return tile.GetPacman();
	}

	return NULL;
}

Point* TileGraph::GetPoint()
{
	for (int i = 0; i < (width * height); i++) {
		Tile tile = tiles[i];

		if (tile.GetPoint() != NULL)
			return tile.GetPoint();
	}

	return NULL;


}

int TileGraph::GetIndex(int x, int y)
{
	if (x >= width || y >= height)
		return -1;

	if (x < 0 || y < 0)
		return -1;

	return x + y * width;
}

std::array<Tile*, 4> TileGraph::Get_Neighbours(Tile* tile)
{
	std::array<Tile*, 4> neighbours;

	int x = tile->GetPosition().x;
	int y = tile->GetPosition().y;

	neighbours[0] = GetTileAt(x, y + 1);	
	neighbours[1] = GetTileAt(x + 1, y);		
	neighbours[2] = GetTileAt(x, y - 1);		
	neighbours[3] = GetTileAt(x - 1, y);		

	return neighbours;
}