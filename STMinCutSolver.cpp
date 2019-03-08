/*This C file contains an implementation of the Ford-Fulkerson Max. flow Algorithm
@Author: Aditya Tyagi
Adaptations made to C implementation of the Ford-Fulkerson Algorithm
from http://www.aduni.org/courses/algorithms/courseware/handouts/Reciation_09.html
@Author: Mark Dettinger, Last modified 2001-02-21
*/

#include "STMinCutSolver.h"


STMinCutSolver::STMinCutSolver(Graph argGraph, Vertex sv, Vertex tv) {
			thisGraph = argGraph;
			sourceVertex = sv;
			terminalVertex = tv;
			//as max-flow value is currently zero
			max_flow_min_cut = 0;
			//capacity contains capacity of adjacency matrix representation
			capacity = argGraph.get_adj_mat();
			flow = {{0}};
}
bool STMinCutSolver::bfs(int start, int target){
	//u,v represent vertices
	int u,v;
	//n represents number of vertices in graph
	int n = thisGraph.get_graph_size();
	// pred containing path
	int pred[n];
	//color contains whether a node is visited (BLACK), in queue (GREY), or unvisited (WHITE)
	int color[n];
	//queue to store nodes waiting to be processed
	queue<int> myQueue;
	//set all nodes to be unvisited (WHITE)
	for (u = 0; u < n; u++) {
		color[u] = WHITE;
	}
	pred[start] = -1;
	myQueue.push(start);
	color[start] == GRAY;
	while (!(myQueue.empty())) {
		//retreive the next element from myQueue
		u = myQueue.front();
		//and then pop it out of the queue
		myQueue.pop();
		color[u] = BLACK;
        // Search all adjacent white nodes v. If the capacity
        // from u to v in the residual network is positive,
        // enqueue v. (implicitly also has to be a neighbor of v)
		for (v = 0; v< n; v++) {
			if (color[v] == WHITE && capacity[u][v] - flow[u][v] > 0.0) {
				myQueue.push(v);
				color[v] == GRAY;
				pred[v] = u;
			}
		}
	}
	//if the color of the target node is black, that means it was reached from START.(and path exists)
	return color[target] == BLACK;
}




//implementations
double STMinCutSolver::solve_max_flow() {
	double max_flow;
	int s = sourceVertex.vertex_no;
	int t = terminalVertex.vertex_no;
	int n = thisGraph.get_graph_size();
	int i,j,u;
	int pred[n];
	//initialize empty flow
	for (i = 0; i<n;i++) {
		for (j = 0; j < n;j++) {
			flow[i][j] = 0.0;
		}
	}
	//while there is an augmenting path, increment flow along that path.
	while (bfs(s,t)) {
	//first determine the amount by which to increment flow
		double increment = oo;
		for (u = n-1; pred[u]>=0; u = pred[u]) {
			increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
		}
		//now increment the flow
		for (u = n-1;pred[u] >= 0; u = pred[u]) {
			flow[pred[u]][u] += increment;
			flow[u][pred[u]] -= increment;
		}
		max_flow += increment;
	}
	//no more augmenting paths left, because loop has terminated, so we have max flow.
	//set max_flow_min_cut to appropriate value
	max_flow_min_cut = max_flow;
	return max_flow;
}


list <Edge> STMinCutSolver::solve_min_cut() {
	list<Edge> ret_list;
	//double** adj_mat = thisGraph.get_adj_mat();
	for (int r = 0; r < thisGraph.get_graph_size();r++) {
		for (int c = 0; c < thisGraph.get_graph_size();c++) {
			if (flow[r][c] == capacity[r][c]) {
				ret_list.push_back(Edge(r,c,capacity[r][c]));
			}
		}
	}
	cut_set = ret_list;
	return ret_list;
}


/* OLD CODE:
 *
 * Declarations
   int n;  // number of nodes
   int e;  // number of edges
   double capacity[MAX_NODES][MAX_NODES]; // capacity matrix
   double flow[MAX_NODES][MAX_NODES];     // flow matrix
   int color[MAX_NODES]; // needed for breadth-first search
   int pred[MAX_NODES];  // array to store augmenting path

 *
 *
 * double min (double x, double y) {
    return x<y ? x : y;  // returns minimum of x and y
    }

//A Queue for Breadth-First Search
int head,tail;
int q[MAX_NODES+2];


void ff_enqueue (int x) {
    q[tail] = x;
    tail++;
    color[x] = GRAY;
}

int ff_dequeue () {
    int x = q[head];
    head++;
    color[x] = BLACK;
    return x;
}
//arr_cpy copies data from src_arr, to dest_arr. assumes square arrays of dimension DIM.
void arr_cpy(double** dest_arr, double** src_arr, int dim) {
	for (int row_ind = 0; row_ind < dim; row_ind++) {
		for (int col_ind = 0; col_ind < dim; col_ind++) {
			dest_arr[row_ind][col_ind] = src_arr[row_ind][col_ind];
		}
	}
	return;
}

//Initialize all the necessary global variables (n,e,capacity) using existing data types.
void initialize(int num_nodes, int num_edges, double** arg_adj_mat) {
  if ((num_nodes == 0) ||  (num_edges == 0)) {
    return;
  }
  n = num_nodes;
  e = num_edges;
  //capacity = new double[MAX_NODES][MAX_NODES];
  //flow = new double[MAX_NODES][MAX_NODES];
  //color = new int[n];
  //pred = new int[n];
  arr_cpy(capacity, arg_adj_mat, n);
}
 *
//Breadth-First Search for an augmenting path
int bfs (int start, int target) {
    int u,v;
    for (u=0; u<n; u++) {
	color[u] = WHITE;
    }
    head = tail = 0;
    ff_enqueue(start);
    pred[start] = -1;
    while (head!=tail) {
	u = ff_dequeue();
        // Search all adjacent white nodes v. If the capacity
        // from u to v in the residual network is positive,
        // enqueue v.
	for (v=0; v<n; v++) {
	    if (color[v]==WHITE && capacity[u][v]-flow[u][v]>0.0) {
        ff_enqueue(v);
        pred[v] = u;
	    }
	}
    }
    // If the color of the target node is black now,
    // it means that we reached it.
    return color[target]==BLACK;
}

//Ford-Fulkerson Algorithm with BFS to obtain augmenting paths (Edmunds-Karp Implementation)
double max_flow (int source, int sink) {
    int i,j,u;
    // Initialize empty flow.
    double max_flow = 0.0;
    for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
        flow[i][j] = 0.0;
	}
    }
    // While there exists an augmenting path,
    // increment the flow along this path.
    while (bfs(source,sink)) {
  // Determine the amount by which we can increment the flow.
	double increment = oo;
	for (u=n-1; pred[u]>=0; u=pred[u]) {
	    increment = min(increment,capacity[pred[u]][u]-flow[pred[u]][u]);
	}
  // Now increment the flow.
	for (u=n-1; pred[u]>=0; u=pred[u]) {
	    flow[pred[u]][u] += increment;
	    flow[u][pred[u]] -= increment;
	}
	max_flow += increment;
    }
    // No augmenting path anymore. We are done.
  return max_flow;
}
*/


