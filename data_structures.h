/*Contains implementation of basic Queue & Graph Data Structures for use in the Isoation Branching Implementation
@Author: Aditya Tyagi*/
#define MAXQUEUESIZE 100000
#define MAXGRAPHSIZE 6
#include <queue>
#include <list>
#include <iterator>

using namespace std;

class Vertex {
public:
	int vertex_no;
	list <int> parents;
	list <int> children;
public:
	Vertex(int v_num, list<int> par, list<int> chn) {
		vertex_no = v_num;
		parents = par;
		children = chn;
	}
};

class Edge {
public:
	int start_vertex;
	int end_vertex;
	double capacity;
public:
	Edge (int a, int b, double cap) {
	start_vertex = a;
	end_vertex = b;
	capacity = cap;}

	void print_me() {
		printf("(%i,%i):%i",start_vertex,end_vertex,capacity);
	}
};


class Graph {
private:
	// num of vertices in the graph
	int n;
	// graph represented as an adjacency list of doubles
	double adj_mat[][];
	//no. of edges
	int e;
	//true if directed, false if not
	bool directed;
	//list of all Edges in the graph
	list<Edge> edges;
	//
public:
	//constructor
	//constructs a Graph with numVertices vertices and no edges. edges need to be added by calling add_edge
	Graph(int numVertices, bool dir) {
		n = numVertices;
		directed = dir;
		e= 0;
		//initialize adj_mat to all zeroes
		double adj_mat[numVertices][numVertices] = {{0}};
		for (int i = 0; i < numVertices; i++) {
		     adj_mat[i] = new double[numVertices];
		     for (int j = 0; j < numVertices; j++) {
		         adj_mat[i][j] = 0.0;
		 }
		}
	}

	//member functions
	//accessor methods:
	int get_graph_size();
	int get_num_edges();
	double** get_adj_mat();
	double get_edge_weight(int start_vertex_no, int end_vertex_no);
	bool get_directed();
	list<Edge> get_edges();
	//mutator methods (set):
	void set_graph_size(int g_size);
	void set_num_edges(int num_edges);
	void set_adj_mat(double** new_adj_mat);
	void change_edge_weight(int start_vertex_no, int end_vertex_no, double new_weight);
	void add_edge(int start_vertex_no, int end_vertex_no, double edge_weight);
	int num_parents(int vertex_no);
	int num_children(int vertex_no);
	list<int> children(int vertex_no);
	list<int> parents(int vertex_no);
	void add_child(int parent_vertex_no, int child_vertex_no, double edge_weight);
};
