#include "BranchBoundNode.h"
#include "data_structures.h"
#include "STMinCutSolver.h"

Graph BranchBoundNode::get_graph() {
	return refGraph;
}

map<int, Vertex> BranchBoundNode::get_terminal_set() {
	return terminal_set;
}

map<int, map<int, Vertex>> BranchBoundNode::get_seed_sets() {
	return seed_sets;
}

double BranchBoundNode::get_score() {
	return my_score;
}

int BranchBoundNode::get_depth() {
	return my_depth;
}

list<int> BranchBoundNode::identify_unassigned_vertices(Graph argGraph,
		map<int,Vertex> arg_terminal_list, map<int,map<int,Vertex>> arg_seed_sets) {

	//create a list of all vertices in graph
	list<int> retList;
	for (int i = 0; i < argGraph.get_graph_size() ;i++) {
		//add all vertices to retList
		retList.push_back(i);
	}
	//remove all the terminals from retList (as they are already implicitly 'assigned')
	for (int search_vertex: retList) {
		//if the search_vertex is present in terminal_set, then remove it from retList
		if (terminal_set.count(search_vertex) !=0) {
			retList.remove(search_vertex);
		}
	}
	//iterate over retList and search each seed_set in arg_seed_sets for search_vertex,
	//if it is there, then it has been assigned; remove it!
	for (int search_vertex : retList) {
		for (map<int,Vertex> seed_set : arg_seed_sets) {
			if (seed_set.count(search_vertex) != 0) {
				//i.e. search_vertex present in seed_set, then remove search_vertex from retList
				retList.remove(search_vertex);
			}
		}

	}
	return retList;
}


void BranchBoundNode::connect_vertex_to_seed_set(int vertex_no, int terminal_no) {
	//will add the vertex to seed set associated with terminal_no, by adding a large
	//capacity edge between vertex, terminal
	refGraph.add_edge(terminal_no, vertex_no, INFINITY);
}

void BranchBoundNode::reassign_seed_sets(int terminal_no, map<int, Vertex> new_seed_set) {
	seed_sets.erase(terminal_no);
	seed_sets[terminal_no] = new_seed_set;
	//modify refGraph correctly now by cementing the appropriate edges
	for (Vertex v: new_seed_set) {
		refGraph.add_edge(terminal_no, v.vertex_no, INFINITY);
		}
	return;
	}

map<int, Vertex> BranchBoundNode::compute_source_set(int source_vertex_no) {
	map<int,Vertex> new_source_set = seed_sets.find(source_vertex_no);
	//create a fresh copy of refGraph
	Graph copyGraph = Graph(refGraph.get_graph_size(), false);
	copyGraph.set_adj_mat(refGraph.get_adj_mat());
	copyGraph.set_num_edges(refGraph.get_num_edges());

	int s = source_vertex_no;
	int t;

	//cement bonds between source terminal vertex and all the other vertices in its seed set
	// this should already be the case!!
	for (Vertex v : seed_sets[source_vertex_no]){
		copyGraph.add_edge(source_vertex_no,v.vertex_no, INFINITY);
	}
	//cement connections between all other terminal vertices
	for (Vertex source_tv:terminal_set) {
		for (Vertex end_tv: terminal_set) {
			//only cement connection between non-source_vertex_no edges
			if (!(source_tv.vertex_no == source_vertex_no || end_tv.vertex_no == source_vertex_no)) {
				copyGraph.add_edge(source_tv.vertex_no, end_tv.vertex_no, INFINITY);
				t = source_tv.vertex_no;
			}
		}
	}
	//at end of loop, t is some non-source_vertex_no vertex
	STMinCutSolver solver = STMinCutSolver(copyGraph, s, t);
	solver.solve_max_flow();
	set<Edge> cut_set = solver.solve_min_cut();
	for (Edge e: cut_set) {
		//only if start_vertex is not already present in the new_source_set
		if (new_source_set.count(e.start_vertex) == 0) {
			list<int> pars = refGraph.parents(e.start_vertex);
			list<int> chns = refGraph.children(e.start_vertex);
			Vertex vertex_obj = Vertex(e.start_vertex, pars, chns);
			new_source_set[e.start_vertex] = vertex_obj;
		}
		//same for end_vertex
		if (new_source_set.count(e.end_vertex) == 0) {
			list<int> pars = refGraph.parents(e.end_vertex);
			list<int> chns = refGraph.children(e.end_vertex);
			Vertex vertex_obj = Vertex(e.end_vertex, pars, chns);
			new_source_set[e.end_vertex] = vertex_obj;
		}
	}
	return new_source_set;
	}

double BranchBoundNode::compute_score() {
	list<Edge> all_edges = refGraph.get_edges();
	double sum = 0;
	map<int,Vertex> curr_seed_set;
	for (Vertex curr_terminal : terminal_set) {
		curr_seed_set = seed_sets.find(curr_terminal.vertex_no);
		for (Edge e : all_edges) {
				//check if edge's start_vertex is in the current seed set
				if (curr_seed_set.count(e.start_vertex) > 0) {
					//now iterate through the other seed sets
					for (map<int,Vertex> other_seed_set: seed_sets) {
						//check if edge's end_vertex is in this other seed set
						if (other_seed_set.count(e.end_vertex) > 0) {
							//but before adding edge weight to running sum, check if both seed_sets
							// are not the same!
							//(i.e. edges internal to a seed set should not be counted)
							if (curr_seed_set != other_seed_set) {
								sum +=e.capacity;
							}
						}
					}

				}
			}

}
	my_score =  0.5*sum;
	return my_score;
}


bool BranchBoundNode::is_leaf_node() {
	if (identify_unassigned_vertices(refGraph, terminal_set, seed_sets).size() == 0) {
		return true;
	}
	return false;
}
