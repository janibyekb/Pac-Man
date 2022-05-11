#include "Djikstra_Search.h"
#include "PriorityQueue.h"

Djikstra_Search::Djikstra_Search(TileGraph* tileGraph)
{
	pTileGraph = tileGraph;

	avoidFunction = [](Tile* tile) {
		return false;
	};
}

std::vector<Tile*> Djikstra_Search::CalculateRoute(Tile* start, Tile* goal)
{
	std::unordered_map<Tile*, Tile*> came_from;		// Chosen path
	std::unordered_map<Tile*, float> cost_so_far;	// Cost of movement

	PriorityQueue<Tile*, float> frontier;			

	came_from[start] = start;
	cost_so_far[start] = 0;

	frontier.put(start, 0);

	while (!frontier.empty())
	{
		// Get a tile with the biggest priority
		Tile* current = frontier.get();

		if (current == goal)
			break;

		// Check all neighbours
		for (auto next : pTileGraph->Get_Neighbours(current)) {
			float new_cost = cost_so_far[current] + 1;

			if (next != NULL && (!cost_so_far.count(next) || new_cost < cost_so_far[next]))
			{
				if (avoidFunction(next)) new_cost = INFINITY;

				cost_so_far[next] = new_cost;
				float priority = new_cost + Heuristic(next, goal);
				frontier.put(next, priority);
				came_from[next] = current;
			}
		}
	}

	vector<Tile*> path;
	Tile* current = goal;

	path.push_back(current);

	while (current != start)
	{
		current = came_from[current];
		path.push_back(current);
	}

	// reversing the list to start from beginning
	reverse(path.begin(), path.end());

	return path;
}

void Djikstra_Search::SetAvoidFunction(function<bool(Tile*)> newFunction)
{
	avoidFunction = newFunction;
}

inline float Djikstra_Search::Heuristic(Tile* a, Tile* b)
{
	return std::abs(a->GetPosition().x - b->GetPosition().x) + std::abs(a->GetPosition().y - b->GetPosition().y);
}
