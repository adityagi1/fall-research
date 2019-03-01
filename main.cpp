//#include "IsolationBranchTree.cpp"
//using namespace std;
#include <stdio.h>
#include "IsolationBranchTree.h"


void test_func() {
	//creating inputGraph
	Graph inputGraph = Graph(8,false);

	//adding relevant edges
	inputGraph.add_edge(0,1,4.0);
	inputGraph.add_edge(1,2,3.0);
	inputGraph.add_edge(2,3,2.0);
	inputGraph.add_edge(3,4,3.0);
	inputGraph.add_edge(4,5,4.0);
	inputGraph.add_edge(2,6,2.0);
	inputGraph.add_edge(6,7,3.0);
	inputGraph.add_edge(7,8,3.0);
	inputGraph.add_edge(6,9,2.0);
	inputGraph.add_edge(9,10,3.0);
	inputGraph.add_edge(10,11,4.0);
	inputGraph.add_edge(3,9,2.0);
	//creating terminal list
	list<int> input_list = {0,5,8,11};
	IsolationBranchTree testObj = IsolationBranchTree(inputGraph, input_list);
	testObj.execute();
	testObj.show_final_seed_sets();
	return;
}



int main() {
	printf("%i", 108);
	test_func();
	return 0;
}







