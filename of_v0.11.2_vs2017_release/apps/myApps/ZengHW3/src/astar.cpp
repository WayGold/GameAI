#include "astar.h"

vector<Vertex*> Pathfinding::a_star(vector<Vertex*>& all_vertices, Vertex* src, Vertex* dst) {
	std::cerr << "Running A Star!" << std::endl;

	Vertex* working = nullptr;
	Vertex* neighbor = nullptr;

	std::priority_queue<pair<Vertex*, int>, vector<pair<Vertex*, int>>, pairComp> queue;

	// Reset All Vertices
	for (auto i = all_vertices.begin(); i != all_vertices.end(); i++) {
		(*i)->dist = INT_MAX;
		(*i)->prev_vertex = -1;
		(*i)->done = false;
	}

	// Distance to Source Set to Zero
	src->dist = 0;
	src->estimated_total_cost = heuristic_random(src);

	// Push Source to Open List with ETC
	queue.push(make_pair(src, src->estimated_total_cost));

	// Iterate Open List to Process Each Vertex
	while (!queue.empty()) {

		// Get the smallest element in the open list, auto sorted by priority queue
		working = queue.top().first;
		queue.pop();

		// If it is the goal vertex, terminate to save run time
		if (working->index == dst->index)
			break;

		if (!(working->done)) {

			// Mark the vertex as done (edges processed)
			working->done = true;

			for (auto itr = working->edges.begin(); itr != working->edges.end(); itr++) {
				// Calculate the new distance
				neighbor = itr->first;
				int cost = working->dist + itr->second;

				// Check whether we found a shorter path, if so update
				if (cost < neighbor->dist) {

					int preCalcHeuristic = -1;

					// In closed list, remark it to the open queue
					if (neighbor->done) {
						neighbor->done = false;
						preCalcHeuristic = neighbor->estimated_total_cost - neighbor->dist;
					}

					neighbor->prev_vertex = working->index;
					neighbor->dist = cost;
					neighbor->estimated_total_cost = cost +
						(preCalcHeuristic == -1) ? heuristic_random(neighbor) : preCalcHeuristic;

					// Put the vertex to the open list/queue with ETC
					queue.push(make_pair(neighbor, neighbor->estimated_total_cost));
				}
			}
		}
	}

	vector<Vertex*> path;

	// A Path is Found
	if (working != nullptr) {
		// Push the Goal
		path.push_back(all_vertices[working->index]);
		// Go through the stored previous vertex for each visited
		while (working->prev_vertex != -1) {
			path.push_back(all_vertices[working->prev_vertex]);
			working = all_vertices[working->prev_vertex];
		}
		// Reverse the path so it is from src -> goal
		std::reverse(path.begin(), path.end());
	}

	// Return the path to the destination
	return path;
}

vector<Vertex*> Pathfinding::a_star(vector<Vertex*>& all_vertices, Vertex* src, Vertex* dst, int& o_visited)
{
	//std::cerr << "Running A Star!" << std::endl;

	Vertex* working = nullptr;
	Vertex* neighbor = nullptr;

	std::priority_queue<pair<Vertex*, int>, vector<pair<Vertex*, int>>, pairComp> queue;

	// Reset All Vertices
	for (auto i = all_vertices.begin(); i != all_vertices.end(); i++) {
		(*i)->dist = INT_MAX;
		(*i)->prev_vertex = -1;
		(*i)->done = false;
	}

	// Distance to Source Set to Zero
	src->dist = 0;
	src->estimated_total_cost = heuristic(src);

	// Push Source to Open List with ETC
	queue.push(make_pair(src, src->estimated_total_cost));

	// Iterate Open List to Process Each Vertex
	while (!queue.empty()) {

		// Get the smallest element in the open list, auto sorted by priority queue
		working = queue.top().first;
		queue.pop();

		// If it is the goal vertex, terminate to save run time
		if (working->index == dst->index)
			break;

		if (!(working->done)) {

			// Mark the vertex as done (edges processed)
			working->done = true;

			for (auto itr = working->edges.begin(); itr != working->edges.end(); itr++) {
				// Calculate the new distance
				neighbor = itr->first;
				int cost = working->dist + itr->second;

				// Check whether we found a shorter path, if so update
				if (cost < neighbor->dist) {

					int preCalcHeuristic = -1;

					// In closed list, remark it to the open queue
					if (neighbor->done) {
						neighbor->done = false;
						preCalcHeuristic = neighbor->estimated_total_cost - neighbor->dist;
					}

					neighbor->prev_vertex = working->index;
					neighbor->dist = cost;
					neighbor->estimated_total_cost = cost +
						(preCalcHeuristic == -1) ? heuristic(neighbor) : preCalcHeuristic;

					// Put the vertex to the open list/queue with ETC
					queue.push(make_pair(neighbor, neighbor->estimated_total_cost));
				}
				o_visited++;
			}
		}
	}

	vector<Vertex*> path;

	// A Path is Found
	if (working != nullptr) {
		// Push the Goal
		path.push_back(all_vertices[working->index]);
		// Go through the stored previous vertex for each visited
		while (working->prev_vertex != -1) {
			path.push_back(all_vertices[working->prev_vertex]);
			working = all_vertices[working->prev_vertex];
		}
		// Reverse the path so it is from src -> goal
		std::reverse(path.begin(), path.end());
	}

	// Return the path to the destination
	return path;
}
