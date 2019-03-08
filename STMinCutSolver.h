#include "data_structures.h"
#include <queue>
#include <list>
#ifndef STMINCUTSOLVER_H
#define STMINCUTSOLVER_H


//Basic Definitions
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX_NODES 1000
#define oo 1000000000.0


//some function definitions
void initialize(int num_nodes, int num_edges, double** arg_adj_mat);

class STMinCutSolver {
private:
	Graph thisGraph;
	Vertex sourceVertex;
	Vertex terminalVertex;
	double capacity [MAX_NODES][MAX_NODES];
	double flow[MAX_NODES][MAX_NODES];
	double max_flow_min_cut;
	list<Edge> cut_set;

public:
	//constructor
	STMinCutSolver(Graph argGraph, Vertex sv, Vertex tv);
	bool bfs(int start, int target);
	double solve_max_flow();
	list <Edge> solve_min_cut();

};

#endif
