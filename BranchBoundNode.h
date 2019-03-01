#include "STMinCutSolver.cpp"
#include <set>
#include <map>
#define INFINITY 1000000.0

class BranchBoundNode{
private:
	Graph refGraph;
	//map with terminal key, and value = Vertex associated with that terminal
	map<int, Vertex> terminal_set;
	//map with int as key (terminal vertex no.), and value = map containing all vertices in seed set.
	map<int, map<int, Vertex>> seed_sets;
	double my_score;
	int my_depth;
	list<int> unassigned_vertices;
public:
	BranchBoundNode(Graph argGraph, map<int,Vertex> terminals, map<int, map<int, Vertex>> arg_seed_sets, int depth) {
		refGraph = argGraph;
		terminal_set = terminals;
		seed_sets = arg_seed_sets;
		my_depth = depth;
		my_score = 0;
		unassigned_vertices = identify_unassigned_vertices(refGraph, terminals, arg_seed_sets);
	}
	//basic accessor methods
	Graph get_graph();
	map<int,Vertex> get_terminal_set();
	map<int, map<int, Vertex>> get_seed_sets();
	double get_score();
	int get_depth();
	//core methods
	list<int> identify_unassigned_vertices(Graph argGraph, map<int,Vertex> arg_terminal_list,
			map<int,map<int,Vertex>> arg_seed_sets);
	void connect_vertex_to_seed_set(int vertex_no, int terminal_no);
	map<int, Vertex> compute_source_set(int source_vertex_no);
	void reassign_seed_sets(int terminal_no, map<int,Vertex> new_seed_set);
	double compute_score();
	bool is_leaf_node();
};
