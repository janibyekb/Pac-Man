#pragma once
#include <queue>
#include <unordered_map>
#include <functional>

#include "TileGraph.h"
#include "PriorityQueue.h"

class Djikstra_Search
{
public:
	Djikstra_Search(TileGraph* tileGraph);

	//calculating the path
	std::vector<Tile*> CalculateRoute(Tile* start, Tile* goal);

	// what to avoid
	void SetAvoidFunction(function<bool(Tile*)> newFunction);

private:
	static inline float Heuristic(Tile* a, Tile* b);

	TileGraph* pTileGraph;
	function<bool(Tile*)> avoidFunction;
};

