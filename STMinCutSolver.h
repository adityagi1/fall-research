#include "data_structures.h"

class STMinCutSolver {
public:
	Graph thisGraph;
	Vertex sourceVertex;
	Vertex terminalVertex;
	double max_flow_min_cut;
	list<Edge> cut_set;


	//constructor
	void STMinCutSolver(Graph argGraph, Vertex sv, Vertex tv) {
		thisGraph = argGraph;
		sourceVertex = sv;
		terminalVertex = tv;
		//as max-flow value is currently zero
		max_flow_min_cut = 0;
		//also call initialize function to initiative global variables
		int num_vertices = thisGraph.get_graph_size();
		int num_edges = thisGraph.get_num_edges();
		double** graph_adj_mat = thisGraph.get_adj_mat();
		initialize(num_vertices,num_edges,graph_adj_mat);
	}
	double solve_max_flow();
	list <Edge> solve_min_cut();
}
