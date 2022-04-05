#pragma once
#include "Graph.h"
#include "Obstacle.h"
#include "ofMain.h"
#include <math.h>

class TileGraph {
public:
	int tile_width;
	int tile_height;
	int win_width, win_height;
	int obstacle_num = -1;

	Graph* tileGraph;

	TileGraph();
	TileGraph(int i_width, int i_height, const int i_winWidth, const int i_winHeight);
	~TileGraph();

	void updateGraph(vector<Obstacle*> i_allObstacles);

	glm::vec2 quantized(glm::vec2 i_pos);
	glm::vec2 localized(glm::vec2 i_rowCol);

	bool checkObstacleOverlap(int i_row, int i_col, Obstacle* i_obstacle);
	Vertex* at(glm::vec2 rowCol);
};