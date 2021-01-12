// Implementation to DFS on directed graph
// Graph is stores as adjacency list

#include<iostream>
#include<list>
using namespace std;

class Graph
{
	int V;
	list<int> *adj;
	void DFSUtil (int v, bool visited[]);
	
public:
	
	Graph (int V);
	void addEdge(int v, int w);
	void DFS(int v);
	
};

//constructor
Graph::Graph (int V)
{
	this->V = V;
	adj = new list<int>[V];
}

// function to add an edge from v to w
void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
}

// recursive DFS utility function
void Graph::DFSUtil (int v, bool visited[])
{
	visited[v] = true;
	cout<<v<<" ";
	
	list<int>::iterator i;
	for (i = adj[v].begin(); i!=adj[v].end(); i++)
		if(!visited[*i])
			DFSUtil(*i,visited);
		
}

// main DFS function. Just calls DFSUtil from given vertex
void Graph::DFS(int v)
{
	bool* visited = new bool[V];
	for (int i=0; i<V; i++)
		visited[i] = false;
	DFSUtil(v,visited);
	cout<<endl;
}

int main()
{
	Graph g(5);
	g.addEdge(0,1);
	g.addEdge(0,2);
	g.addEdge(1,2);
	g.addEdge(2,0);
	g.addEdge(2,3);
	
	int startNode = 2;
	cout<<" DFS starting from node "<<startNode<<" :"<<endl;
	g.DFS(startNode);
	
	return 0;
}
	