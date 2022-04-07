#pragma once
#include "astar.h"
#include "rigidBody.h"
#include "TileGraph.h"
#include <assert.h>

namespace Pathfinding {
	inline vector<Vertex*> getPath(RigidBody* pathFinder, RigidBody* seekTarget, TileGraph* tileGraph) {
		// Vec2 (row, col)
		glm::vec2 current_pos = tileGraph->quantized(pathFinder->position);
		glm::vec2 dst_pos = tileGraph->quantized(seekTarget->position);

		// Find src and dst vertices
		Vertex* src = tileGraph->at(current_pos);
		Vertex* dst = tileGraph->at(dst_pos);

		vector<Vertex*> empty;
		if (dst == nullptr || src == nullptr)
			return empty;

		// Call Path Finding Algorithm to Output a Path
		return Pathfinding::a_star(tileGraph->tileGraph->all_vertices, src, dst);
	}

	inline bool has_arrive(RigidBody* pathFinder, Vertex* dst, TileGraph* tileGraph) {
		glm::vec2 current_pos = tileGraph->quantized(pathFinder->position);
		glm::vec2 dst_pos = glm::vec2(dst->row, dst->col);

		if (current_pos == dst_pos)
			return true;
		
		return false;
	}
}