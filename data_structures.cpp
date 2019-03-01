#include "data_structures.h"

//member function definitions

////accessor method for no. of vertices
int Graph::get_graph_size() {
  return n;
}

//accessor method for no. of edges
int Graph::get_num_edges() {
	return e;
}

//accessor method for adjacency matrix
double** Graph::get_adj_mat() {
	return adj_mat;
}


//get_edge_weight takes a graph pointer, start_vertex_no., end_vertex_no., and  returns the edge_weight
double Graph::get_edge_weight(int start_vertex_no, int end_vertex_no) {
  return adj_mat[start_vertex_no][end_vertex_no];
}

bool Graph::get_directed() {
	return directed;
}

list<Edge> Graph::get_edges() {
	return edges;
}

void Graph::set_graph_size(int new_g_size) {
	n = new_g_size;
}

void Graph::set_num_edges(int new_num_edges) {
	e = new_num_edges;
}

void Graph::set_adj_mat(double** new_adj_mat) {
	adj_mat = new_adj_mat;
}

//change_edge_weight takes a graph pointer, start_vertex_no., end_vertex_no., new_weight and changes the edge_weight
void Graph::change_edge_weight(int start_vertex_no, int end_vertex_no, double new_weight) {
		adj_mat[start_vertex_no][end_vertex_no] = new_weight;
	if (!directed){
		adj_mat[end_vertex_no][start_vertex_no] = new_weight;
	}
	//search for current edge from edges
	list<Edge>::iterator it = edges.begin();
	Edge old_edge =  *it;
	int sv = old_edge.start_vertex;
	int tv = old_edge.end_vertex;
	while (!(sv == start_vertex_no && tv == end_vertex_no)){
		advance(it,1);
		old_edge = *it;
		sv = old_edge.start_vertex;
		tv = old_edge.end_vertex;
	}
	edges.erase(it);

	edges.push_back(Edge(start_vertex_no, end_vertex_no, new_weight));
}

//add_edge() takes a graph_t pointer, start_vertex_no, end_vertex_no, weight and adds the edge to the graph
void Graph::add_edge(int start_vertex_no, int end_vertex_no, double edge_weight) {
  //add_edge operation is only supposed to be used when there is no edge already present
	// to change edge weight, you change_edge_weight method
	if (adj_mat[start_vertex_no][end_vertex_no] != 0) {
	  return;
  }

	adj_mat[start_vertex_no][end_vertex_no] = edge_weight;
  if (!directed){
  		adj_mat[end_vertex_no][start_vertex_no] = edge_weight;
  	}
  e++;
  //add the edge to edges_list
  Edge new_edge = Edge(start_vertex_no, end_vertex_no, edge_weight);
  edges.push_back(new_edge);
}

int Graph::num_children(int vertex_no) {
	  int nc = 0;
	  for (int ch_no = 0; ch_no < n; ch_no++) {
	    if (adj_mat[vertex_no][ch_no] != 0) {
	      nc++;
	    }
	  }
	  return nc;
}


int Graph::num_parents(int vertex_no) {
	int np = 0;
	int num_rows = sizeof(adj_mat)/sizeof(adj_mat[0]);
	for (int p_no = 0; p_no < num_rows; p_no++) {
	    if (adj_mat[p_no][vertex_no] != 0) {
	      np++;
	    }
	  }
	return np;
}

//children() takes a graph_t pointer and a vertex_no and returns the children of the vertex as a list
// if vertex_no has 0 children, then return a NULL pointer.
list<int> Graph::children(int vertex_no) {
	list <int> ret_list;
	// find the length of the list to be returned (i.e. the no. of children)
  int num = num_children(vertex_no);
  //return a NULL pointer is num == 0
  if (num == 0) {return nullptr;}
  int i = 0;
  while (i < n){
    if (adj_mat[vertex_no][i] != 0) {
    	ret_list.push_back(i);
    }
    i++;
  }
  return ret_list;
}

//parents() takes a graph_t pointer and a vertex_no and returns the parents of the vertex as a list
// if vertex_no has 0 parents, then return a NULL pointer.
list<int> Graph::parents(int vertex_no) {
  list<int> ret_list;
	// find the length of the list to be returned (i.e. the no. of children)
  int np = num_parents(vertex_no);
  if (np == 0) {return nullptr;}
  int num_rows = sizeof(adj_mat)/sizeof(adj_mat[0]);
  int i = 0;
  while (i < num_rows){
    if (adj_mat[i][vertex_no] != 0) {
      ret_list.push_back(i);
    }
    i++;
  }
  return ret_list;
}

//add_child() takes a graph_t pointer, parent_vertex_no, child_vertex_no, edge_weight and adds the child to the graph
//with the appropriate parent and incident edge_weight.
void Graph::add_child(int parent_vertex_no, int child_vertex_no, double edge_weight) {
  if (child_vertex_no < 0 || child_vertex_no >= n ||
     parent_vertex_no < 0 || parent_vertex_no >= n) {
    return;
  }
  adj_mat[parent_vertex_no][child_vertex_no] = edge_weight;
  if (!directed){
  		adj_mat[child_vertex_no][parent_vertex_no] = edge_weight;
  	}
  return;
  edges.push_back(Edge(parent_vertex_no, child_vertex_no, edge_weight));
}
