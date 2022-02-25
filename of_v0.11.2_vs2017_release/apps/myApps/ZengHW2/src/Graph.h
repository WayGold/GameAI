#pragma once
#include <string>
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

struct Vertex {
	string name;
	vector<pair<Vertex*, int>> edges;
	vector<pair<Vertex*, int>> in_edges;

	int index;
	int prev_vertex = -1;
	int dist = INT_MAX;
	int estimated_total_cost = INT_MAX;

	// For tile graph representation
	int row = -1;
	int col = -1;

	bool done = false;
};

class Graph {
public:
	vector<Vertex*> all_vertices;
	unordered_map<string, Vertex*> vertices_map;

	int numOfEdges = 0;

	Graph(void);
	~Graph();

	Vertex* add_vertex(string i_name);

	void generate_preset();
	void add_edge(Vertex* src, Vertex* sink, int weight, bool is_shared = false);
	
	bool read_from_file(string path);
	vector<Vertex*>::iterator Graph::remove_vertex(vector<Vertex*>::iterator i_vertex_itr);
};