#include "TileGraph.h"

TileGraph::TileGraph()
{
	tile_width = -1;
	tile_height = -1;
	win_width = -1;
	win_height = -1;
	tileGraph = nullptr;
}

TileGraph::TileGraph(int i_width, int i_height, const int i_winWidth, const int i_winHeight) :
	tile_width(i_width), tile_height(i_height), win_width(i_winWidth), win_height(i_winHeight)
{
	tileGraph = new Graph();
}

TileGraph::~TileGraph()
{
	if (tileGraph)
		delete tileGraph;
}

void TileGraph::updateGraph(vector<Obstacle*> i_allObstacles)
{
	// Initial Construct, empty tileGraph, first update cost a large amount of runtime
	if (tileGraph == nullptr || tileGraph->all_vertices.size() == 0) {

		if (tileGraph == nullptr)
			tileGraph = new Graph();
		
		// Translate into Tile Graph Vertices
		for (int row = 0; row < win_height / tile_height; row++) {
			for (int col = 0; col < win_width / tile_width; col++) {

				bool has_overlap = false;

				for (auto itr = i_allObstacles.begin(); itr != i_allObstacles.end(); itr++) {
					if (checkObstacleOverlap(row, col, *itr))
						has_overlap = true;
				}

				// Only Add Vertex to Map When The Tile Has No Obstacle Inside
				if (!has_overlap) {
					// Add new vertex to the graph
					//IMPORTANT: string is formatted as "row, col"
					auto new_vertex = tileGraph->add_vertex(to_string(row) + ", " + to_string(col));
					// Record the col/row data
					new_vertex->row = row;
					new_vertex->col = col;
				}
			}
		}

		// Connect All Vertices, Check all 8 vertices around current vertex, connect if exist
		for (auto itr = tileGraph->all_vertices.begin(); itr != tileGraph->all_vertices.end(); itr++) {
			// Get all 8 vertices' key to search in vertice map: "row, col"
			vector<string> queryStringKey;
			// Top Left, Top Right, Bottom Left, Bottom Rigth (Order)
			queryStringKey.push_back(to_string((*itr)->row - 1) + ", " + to_string((*itr)->col - 1));
			queryStringKey.push_back(to_string((*itr)->row - 1) + ", " + to_string((*itr)->col + 1));
			queryStringKey.push_back(to_string((*itr)->row + 1) + ", " + to_string((*itr)->col - 1));
			queryStringKey.push_back(to_string((*itr)->row + 1) + ", " + to_string((*itr)->col + 1));
			// Top, Bottom, Left, Right
			queryStringKey.push_back(to_string((*itr)->row - 1) + ", " + to_string((*itr)->col));
			queryStringKey.push_back(to_string((*itr)->row + 1) + ", " + to_string((*itr)->col));
			queryStringKey.push_back(to_string((*itr)->row) + ", " + to_string((*itr)->col - 1));
			queryStringKey.push_back(to_string((*itr)->row) + ", " + to_string((*itr)->col + 1));

			int idx = 0;

			for (auto key_itr = queryStringKey.begin(); key_itr != queryStringKey.end(); key_itr++) {
				// Find the vertex
				auto working_itr = tileGraph->vertices_map.find(*key_itr);
				int weight;

				if (working_itr != tileGraph->vertices_map.end()) {
					// Found, Connect to current
					// First 4 Vertices are diagonal, give weight 5
					if (idx < 4) {
						weight = 5;
					}
					// Top Bottom give weight 3
					else if (idx > 3 && idx < 6) {
						weight = 3;
					}
					// Left Right give weigth 4
					else {
						weight = 4;
					}
					// Mutaul Connect
					tileGraph->add_edge(working_itr->second, (*itr), weight, false);
				}
			}
		}
		// Update Last Frame Obstacle Number
		obstacle_num = i_allObstacles.size();

		return;
	}

	// Not Initial Construction, Check for new obstacles and remove vertices accordingly
	if (tileGraph != nullptr) {
		int numOfNewObstacles = i_allObstacles.size() - obstacle_num;
		int back_index = i_allObstacles.size() - 1;

		// Loop Through New Obstacles
		for (int index = back_index; index >= int(i_allObstacles.size() - numOfNewObstacles); index--) {

			for (auto itr = tileGraph->all_vertices.begin(); itr != tileGraph->all_vertices.end(); itr++) {

				// Check For Overlap With Existing Tile Vertices
				if (checkObstacleOverlap((*itr)->row, (*itr)->col, i_allObstacles.at(index))) {
					// Remove Vertex and All its Incoming and Outgoing Edges
					itr = tileGraph->remove_vertex(itr);
				}
			}
		}
	}

	// Update Last Frame Obstacle Number
	obstacle_num = i_allObstacles.size();
}

glm::vec2 TileGraph::quantized(glm::vec2 i_pos)
{
	int col = floor(i_pos.x / tile_width);
	int row = floor(i_pos.y / tile_height);

	return glm::vec2(row, col);
}

glm::vec2 TileGraph::localized(glm::vec2 i_rowCol)
{
	int y = i_rowCol.x * tile_height + tile_height / 2;
	int x = i_rowCol.y * tile_width + tile_width / 2;

	return glm::vec2(x, y);
}

bool TileGraph::checkObstacleOverlap(int i_row, int i_col, Obstacle* i_obstacle)
{
	// Tile Center in real space
	glm::vec2 tile_center = localized(glm::vec2(i_row, i_col));

	// Calculate Tile Border Points
	glm::vec2 tile_top_left = glm::vec2(tile_center.x - (tile_width) / 2, tile_center.y - (tile_height) / 2);
	glm::vec2 tile_bottom_right = glm::vec2(tile_center.x + (tile_width), tile_center.y + (tile_height) / 2);

	// Obstacle Borders
	glm::vec2 obs_top_left = i_obstacle->top_left;
	glm::vec2 obs_bottom_right = i_obstacle->bottom_right;

	// Check overlap with obstacle
	if (tile_top_left.x == tile_bottom_right.x 
		|| tile_top_left.y == tile_bottom_right.y 
		|| obs_top_left.x == obs_bottom_right.x
		|| obs_top_left.y == obs_bottom_right.y) {
		// the line cannot have positive overlap
		return false;
	}

	// If one rectangle is on left side of other
	if (tile_top_left.x >= obs_bottom_right.x || obs_top_left.x >= tile_bottom_right.x)
		return false;

	// If one rectangle is above other
	if (tile_bottom_right.y <= obs_top_left.y || obs_bottom_right.y <= tile_top_left.y)
		return false;

	return true;
}

Vertex* TileGraph::at(glm::vec2 rowCol)
{
	auto result = tileGraph->vertices_map.find(to_string(int(rowCol.x)) + ", " + to_string(int(rowCol.y)));
	if (result != tileGraph->vertices_map.end())
		return (*result).second;
	return nullptr;
}
