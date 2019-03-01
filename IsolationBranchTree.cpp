#include "IsolationBranchTree.h"

BranchBoundNode IsolationBranchTree::initialize() {
	map<int, Vertex> tm;
	//creating terminal_map argument
	for (int t : terminals) {
		tm[t] = Vertex(t, refGraph.parents(t), refGraph.children(t));
	}
	//create initial seed sets, consisting of respective terminals
	map<int,map<int,Vertex>> ss_by_terminal;
	for (int t: terminals) {
		map<int,Vertex> seed_set;
		seed_set[t] = Vertex(t, refGraph.parents(t), refGraph.children(t));
		ss_by_terminal[t] = seed_set;
	}
	//root node is always at depth 0
	return BranchBoundNode(refGraph, tm, ss_by_terminal,0);


};


BranchBoundNode IsolationBranchTree::create_child_node(Graph argGraph, int terminal_vertex,
		map<int,map<int,Vertex>> arg_seed_sets, int arg_depth) {
	//creating terminal_map argument
	map<int, Vertex> tm;
	for (int t : terminals) {
		tm[t] = Vertex(t, refGraph.parents(t), refGraph.children(t));
	}
	//creating seed-set map argument (not necessary anymore)
	/*
	map<int,map<int,Vertex>> ss_by_terminal;
	for (int t: terminals) {
		map<int,Vertex> seed_set;
		for (int vertex_no : arg_seed_sets[t]) {
			seed_set[vertex_no] = Vertex(vertex_no,
					refGraph.parents(vertex_no),refGraph.children(vertex_no));
		}
		ss_by_terminal[t] = seed_set;
	}*/
	//now passing arguments to constructor
	return BranchBoundNode(argGraph, tm, arg_seed_sets, arg_depth);

}

int IsolationBranchTree::assign_vertex(BranchBoundNode arg_node) {
	list<int> v_list = arg_node.identify_unassigned_vertices(arg_node.get_graph(), arg_node.get_terminal_set(),
			arg_node.get_seed_sets());
	//simply return the first element in v_list. can optimize later
	return v_list.pop_front();
}


void IsolationBranchTree::execute() {
	BranchBoundNode root_node = initialize();
	for (int terminal_vertex: terminals) {
		//compute source set for terminal_vertex
		map<int,Vertex> source_set = root_node.compute_source_set(terminal_vertex);
		// assign newly computed source_set to terminal_vertex at root_node
		root_node.reassign_seed_sets(terminal_vertex, source_set);
		}
	//compute score for root node
	root_node.compute_score();
	//add root node to PQ
	node_list.push(root_node);
	//while there are still elements in PQ (NO: UNASSIGNED VERTICES)
	while (!(node_list.empty())) {
		//pop node off PQ
		BranchBoundNode expand_node = node_list.pop();
		//check if leaf node:
		if (expand_node.is_leaf_node()) {
			//if it is a leaf node, then guaranteed to be optimal due to PQ return order
			//we have found our solution!
			best_node_found = expand_node;
			return;
		}
		//find target vertex
		int target_vertex = assign_vertex(expand_node);
		//expand node by adding children
		for (int terminal_vertex:terminals) {
			// condense seed sets, inv. about passing values
			BranchBoundNode child_node = create_child_node(expand_node.get_graph(),
					terminal_vertex, expand_node.get_seed_sets(), expand_node.get_depth() + 1);
			//STEP 1: solve the current node by first connecting target_vertex to terminal_vertex
			child_node.connect_vertex_to_seed_set(target_vertex, terminal_vertex);
			//STEP 2: compute source_set
			map<int,Vertex> source_set = child_node.compute_source_set(terminal_vertex);
			//STEP 3: reassign seed_sets in node
			child_node.reassign_seed_sets(terminal_vertex, source_set);
			//STEP 4: compute node_score
			child_node.compute_score();
			//STEP 5: add to the PQ
			node_list.push(child_node);
		}

	}
	return;
}

map<int, list<int>> IsolationBranchTree::show_final_seed_sets() {
	map<int,list<int>> retMap;
	for (Vertex t: best_node_found.get_terminal_set()) {
		list<int> seed_list;
		map<int,Vertex> seed_set = best_node_found.get_seed_sets().at(t.vertex_no);
		for (Vertex v : seed_set) {
			seed_list.push_back(v.vertex_no);
		}
		retMap[t] = seed_list;
	}
	return retMap;
}

/* IMPLEMENT LATER:
list<Edge> IsolationBranchTree::show_final_cut_set() {
}
*/



