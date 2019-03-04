#include <list>
#include <map>
#include <queue>
#include "STMinCutSolver.cpp"
#include "BranchBoundNode.h"
#ifndef ISOLATIONBRANCHTREE_H
#define ISOLATIONBRANCHTREE_H

//a comparision class to compare BranchBoundNode objects (used for PQ)
class Compare {
public:
	bool operator() (BranchBoundNode a, BranchBoundNode b) {
		return a.get_score() < b.get_score();
	}
};

class IsolationBranchTree {
private:
	Graph refGraph;
	BranchBoundNode best_node_found;
	double upper_bound;
	int max_depth;
	priority_queue<BranchBoundNode,vector<BranchBoundNode>, Compare> node_list;
	list<int> terminals;

public:
	void IsolationBranchTree(Graph inputGraph, list<int> input_terminals) {
		refGraph = inputGraph;
		upper_bound = INFINITY;
		max_depth = 0;
		terminals = input_terminals;

		return;
	}
	BranchBoundNode initialize();
	BranchBoundNode create_child_node(Graph argGraph, int terminal_vertex,
			map<int,map<int,Vertex>> arg_seed_sets, int arg_depth);
	int assign_vertex(BranchBoundNode arg_node);
	void execute();
	map<int,list<int>> show_final_seed_sets();
};

#endif
