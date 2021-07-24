
#include<iostream>
#include <queue>
#include "GraphHeader.h"
#include <math.h>
#include <random>


using namespace std;
//Constructors
Graph::Graph()
{
	this->V = 0;
	edges = NULL;
}

Graph::Graph(int V)
{
	this->V = V;
	edges = new set<int>[V]; //Using set because we dont need duplicates edges, graph is undirected. 
}
//Copy Constructor
Graph::Graph(const Graph& lastG)
{
	edges = NULL;
	*this = lastG;
}

//Destructor
Graph::~Graph()
{
	if (edges != NULL)
		delete[] edges;
}
//Operators Overloading
Graph& Graph::operator= (const Graph& lastG)
{
	if (this != &lastG)
		if (edges != NULL)
			delete[] edges;

	V = lastG.V;
	edges = new set<int>[V];
	for (int i = 0; i < V;i++)
		edges[i] = lastG.edges[i];

	return *this;
}


//BFS algorithm from web(GeeksforGeeks)
//BFS made to check the number of edges connected, and return array of them.
int* Graph::BFS(int sourceVertex) const
{
	// Create a queue for BFS
	set<int>::iterator i;
	queue<int> q;

	//Creating an array of connected vertexes
	int* distanceArray = new int[V];
	for (int i = 0; i < V; i++)
		distanceArray[i] = 0;
	distanceArray[sourceVertex] = 0;


	q.push(sourceVertex);


	while (!q.empty()) {
		int currVertex = q.front();
		q.pop();

		for (i = edges[currVertex].begin(); i != edges[currVertex].end(); ++i) {
			int nearVertex = *i;
			if (distanceArray[nearVertex] == -1) {
				distanceArray[nearVertex] = distanceArray[currVertex] + 1;
				q.push(nearVertex);
			}
		}
	}

	return distanceArray;
}

int Graph::addEdge(int current, int next) {


	//Graph is undirected - If 1 is connected to 2, 2 is connected to 1 as well. 
	edges[current].insert(next);
	edges[next].insert(current);
	return 1;
}


set<int>& Graph::checkVertexEdge(int V) const {
	return edges[V];
}


int Graph::getV() const {
	return V;
}