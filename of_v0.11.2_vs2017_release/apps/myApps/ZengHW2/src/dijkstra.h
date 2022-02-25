#pragma once
#include "Graph.h"
#include <queue>
#include <iostream>
#include <algorithm>

namespace Pathfinding {
	class pairComp {
	public:
		inline bool operator()(pair<Vertex*, int> a, pair<Vertex*, int> b) const {
			if (get<1>(a) != get<1>(b)) return get<1>(a) > get<1>(b);
			return get<0>(a)->name < get<0>(b)->name;
		}
	};

	/* Dijkstra for weighted graph pathfinder */
	vector<Vertex*> dijkstra(vector<Vertex*>& all_vertices, Vertex* src, Vertex* dst);
	vector<Vertex*> dijkstra(vector<Vertex*>& all_vertices, Vertex* src, Vertex* dst, int& o_visited);
}