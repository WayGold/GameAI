#pragma once
#include "Graph.h"
#include "dijkstra.h"
#include <queue>
#include <iostream>
#include <algorithm>
#include <random>
#include <time.h>

namespace Pathfinding {

	// Constant Guess, under-estimate
	inline int heuristic(Vertex* vertex) {
		return 1;
	}

	// Random Guess, not stable
	inline int heuristic_random(Vertex* vertex) {
		srand(time(NULL));
		return rand() % 1200 + 100;
	}

	vector<Vertex*> a_star(vector<Vertex*>& all_vertices, Vertex* src, Vertex* dst);
	vector<Vertex*> a_star(vector<Vertex*>& all_vertices, Vertex* src, Vertex* dst, int& o_visited);
}