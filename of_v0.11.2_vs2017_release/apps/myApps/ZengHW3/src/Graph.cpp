#include "Graph.h"

Graph::Graph(void) {
}

Graph::~Graph()
{
	for (unsigned int i = 0; i < all_vertices.size(); i++) {
		delete(all_vertices.at(i));
	}
}

Vertex* Graph::add_vertex(string i_name)
{
	Vertex* to_add = new Vertex();
	to_add->name = i_name;
	to_add->index = all_vertices.size();

	all_vertices.push_back(to_add);
	vertices_map.insert(make_pair(i_name, to_add));

	return to_add;
}

void Graph::add_edge(Vertex* src, Vertex* sink, int weight, bool is_shared)
{
	src->edges.push_back(make_pair(sink, weight));
	sink->in_edges.push_back(make_pair(src, weight));

	if (is_shared) {
		sink->edges.push_back(make_pair(src, weight));
		src->in_edges.push_back(make_pair(sink, weight));
		numOfEdges++;
	}

	numOfEdges++;
}

void Graph::generate_preset()
{
	add_vertex("Geisel");
	add_vertex("Price Center");
	add_vertex("Center Hall");
	add_vertex("CSE");
	add_vertex("Warren Lecture Hall");
	add_vertex("Pepper Canyon");
	add_vertex("ERC");
	add_vertex("CogSci Building");
	add_vertex("Peterson Hall");
	add_vertex("APM");
	add_vertex("Galbraith");
	add_vertex("RIMAC");
	add_vertex("Village");
	add_vertex("Goody's");
	add_vertex("Taco Villa");
	add_vertex("Biomed Library");
	add_vertex("Sun God");
	add_vertex("Triton Fountain");

	/* From Geisel to Everywhere Else */
	add_edge(vertices_map["Geisel"], vertices_map["Price Center"], 150);
	add_edge(vertices_map["Geisel"], vertices_map["Center Hall"], 400);
	add_edge(vertices_map["Geisel"], vertices_map["CSE"], 600);
	add_edge(vertices_map["Geisel"], vertices_map["Warren Lecture Hall"], 450);
	add_edge(vertices_map["Geisel"], vertices_map["ERC"], 1000);
	add_edge(vertices_map["Geisel"], vertices_map["CogSci Building"], 350);
	add_edge(vertices_map["Geisel"], vertices_map["Peterson Hall"], 290);
	add_edge(vertices_map["Geisel"], vertices_map["APM"], 400);
	add_edge(vertices_map["Geisel"], vertices_map["Galbraith"], 1100);
	add_edge(vertices_map["Geisel"], vertices_map["RIMAC"], 700);
	add_edge(vertices_map["Geisel"], vertices_map["Village"], 1200);
	add_edge(vertices_map["Geisel"], vertices_map["Goody's"], 500);
	add_edge(vertices_map["Geisel"], vertices_map["Taco Villa"], 700);
	add_edge(vertices_map["Geisel"], vertices_map["Biomed Library"], 750);
	add_edge(vertices_map["Geisel"], vertices_map["Triton Fountain"], 400);
	add_edge(vertices_map["Geisel"], vertices_map["Sun God"], 400);
	add_edge(vertices_map["Geisel"], vertices_map["Pepper Canyon"], 800);

	/* From ERC to Everywhere Else */
	add_edge(vertices_map["ERC"], vertices_map["Price Center"], 150);
	add_edge(vertices_map["ERC"], vertices_map["Center Hall"], 1100);
	add_edge(vertices_map["ERC"], vertices_map["CSE"], 1300);
	add_edge(vertices_map["ERC"], vertices_map["Warren Lecture Hall"], 1300);
	add_edge(vertices_map["ERC"], vertices_map["CogSci Building"], 800);
	add_edge(vertices_map["ERC"], vertices_map["Peterson Hall"], 800);
	add_edge(vertices_map["ERC"], vertices_map["APM"], 800);
	add_edge(vertices_map["ERC"], vertices_map["Galbraith"], 1700);
	add_edge(vertices_map["ERC"], vertices_map["RIMAC"], 300);
	add_edge(vertices_map["ERC"], vertices_map["Village"], 260);
	add_edge(vertices_map["ERC"], vertices_map["Goody's"], 550);
	add_edge(vertices_map["ERC"], vertices_map["Taco Villa"], 1400);
	add_edge(vertices_map["ERC"], vertices_map["Biomed Library"], 1700);
	add_edge(vertices_map["ERC"], vertices_map["Triton Fountain"], 1300);
	add_edge(vertices_map["ERC"], vertices_map["Sun God"], 1100);
	add_edge(vertices_map["ERC"], vertices_map["Pepper Canyon"], 1700);

	/* From CSE to Everywhere Else */
	add_edge(vertices_map["CSE"], vertices_map["Price Center"], 450);
	add_edge(vertices_map["CSE"], vertices_map["Center Hall"], 700);
	add_edge(vertices_map["CSE"], vertices_map["Warren Lecture Hall"], 240);
	add_edge(vertices_map["CSE"], vertices_map["CogSci Building"], 800);
	add_edge(vertices_map["CSE"], vertices_map["Peterson Hall"], 750);
	add_edge(vertices_map["CSE"], vertices_map["APM"], 850);
	add_edge(vertices_map["CSE"], vertices_map["Galbraith"], 1400);
	add_edge(vertices_map["CSE"], vertices_map["RIMAC"], 1000);
	add_edge(vertices_map["CSE"], vertices_map["Village"], 1500);
	add_edge(vertices_map["CSE"], vertices_map["Goody's"], 800);
	add_edge(vertices_map["CSE"], vertices_map["Taco Villa"], 1100);
	add_edge(vertices_map["CSE"], vertices_map["Biomed Library"], 1100);
	add_edge(vertices_map["CSE"], vertices_map["Triton Fountain"], 500);
	add_edge(vertices_map["CSE"], vertices_map["Sun God"], 800);
	add_edge(vertices_map["CSE"], vertices_map["Pepper Canyon"], 700);

	/* Some Extra In Between Edges */
	add_edge(vertices_map["Warren Lecture Hall"], vertices_map["Center Hall"], 550);
	add_edge(vertices_map["Warren Lecture Hall"], vertices_map["Pepper Canyon"], 450);
	add_edge(vertices_map["Warren Lecture Hall"], vertices_map["CSE"], 240);
	add_edge(vertices_map["Pepper Canyon"], vertices_map["Center Hall"], 600);
	add_edge(vertices_map["Price Center"], vertices_map["Triton Fountain"], 230);
	add_edge(vertices_map["Peterson Hall"], vertices_map["APM"], 100);
	add_edge(vertices_map["Sun God"], vertices_map["Taco Villa"], 200);
	add_edge(vertices_map["Taco Villa"], vertices_map["Galbraith"], 400);
}

bool Graph::read_from_file(string path)
{
	// Load File
	ifstream file(path);

	// Check Loading Error
	if (!file) {
		std::cout << "unable to open file";
		return false;
	}
	else {
		std::cout << "File Loaded, Start Constructing Graph....";
	}

	string line_unparsed;

	while (getline(file, line_unparsed))
	{
		//cout << line_unparsed << endl;

		if (line_unparsed == "")
			continue;

		std::stringstream ss(line_unparsed);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> line(begin, end);

		if (line.size() == 0)
			continue;

		if (line[0] == "c")
			continue;

		// Create all vertices
		if (line[0] == "p") {
			int num_vertices = stoi(line[2]);
			for (int i = 1; i <= num_vertices; i++) {
				add_vertex(to_string(i));
			}
			cout << "Graph initialized with " << all_vertices.size() << " Vertices" << endl;
		}

		if (line[0] == "a") {
			add_edge(all_vertices[static_cast<size_t>(stoi(line[1])) - 1], 
				all_vertices[static_cast<size_t>(stoi(line[2])) - 1], stoi(line[3]));
		}
	}

	std::cout << "Graph Constructed with " << all_vertices.size() << " numbers of Vertices and " 
		<< numOfEdges << " Edges." << std::endl;
}

vector<Vertex*>::iterator Graph::remove_vertex(vector<Vertex*>::iterator i_vertex_itr)
{
	Vertex* i_vertex = *i_vertex_itr;
	// Find the vertex
	auto to_remove_itr = vertices_map.find(i_vertex->name);
	
	// Check whether the vertex is in the graph
	if (to_remove_itr == vertices_map.end())
		return i_vertex_itr;

	auto to_remove = (*to_remove_itr).second;

	// First Remove Its Outgoing Edges
	for (auto itr = to_remove->edges.begin(); itr != to_remove->edges.end(); itr++) {
		// Search for all occurrences for the to remove vertex from other's in edges
		auto in_itr = (*itr).first->in_edges.begin();

		while (in_itr != (*itr).first->in_edges.end()) {
			if ((*in_itr).first->name == to_remove->name) {
				in_itr = (*itr).first->in_edges.erase(in_itr);
			}
			else {
				in_itr++;
			}
		}
		numOfEdges--;
	}

	// Then Remove Its Incoming Edges
	for (auto itr = to_remove->in_edges.begin(); itr != to_remove->in_edges.end(); itr++) {
		// Search for all occurrences for the to remove vertex from other's out edges
		auto in_itr = (*itr).first->edges.begin();

		while (in_itr != (*itr).first->edges.end()) {
			if ((*in_itr).first->name == to_remove->name) {
				in_itr = (*itr).first->edges.erase(in_itr);
			}
			else {
				in_itr++;
			}
		}
		numOfEdges--;
	}

	// Update index for all other vertices after it
	for (int i = to_remove->index + 1; i < all_vertices.size(); i++) {
		all_vertices.at(i)->index--;
	}

	// Remove from all_vertices and vertices_map, and finally delete Vertex
	auto to_return = all_vertices.erase(all_vertices.begin() + to_remove->index);
	vertices_map.erase(to_remove->name);

	delete to_remove;

	return to_return;
}
