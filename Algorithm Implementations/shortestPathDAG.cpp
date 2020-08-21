// Each edge is stored as a tuple of int (vertex no.) and double (weight) 
// Adjacency list is a list of such tuples/ edges

// Run this using g++ -std=C++11 shortestPathDAG.cpp

#include<iostream>
#include<tuple>
#include<list>
#include<stack>
#include<climits>
#define INF INT_MAX

using namespace std;

class Graph{
	int V;
	list<tuple<int,double>> *adj;
	void topoSortUtil (int v, bool visited[], stack<int> &Stack);
	
public:
	Graph (int V);
	void addEdge(int u, int v, int weight);
	void shortestPath(int s);
};

Graph::Graph(int V){
	this->V = V;
	adj = 	new list<tuple<int,double>>[V];
}

void Graph::addEdge(int u, int v, int weight){
	adj[u].push_back(make_tuple(v,weight));
}

void Graph::topoSortUtil (int v, bool visited[], stack<int> &Stack){
	visited[v] = true;
	list<tuple<int,double>>::iterator i;
	for(i=adj[v].begin(); i!=adj[v].end(); ++i){
		if(!visited[get<0>(*i)]){
			topoSortUtil(get<0>(*i),visited,Stack);
		}
	}
	Stack.push(v);
}

void Graph::shortestPath(int s){
	//initialize visited array, Stack
	stack<int> Stack;
	bool *visited = new bool[V];
	for(int i=0; i<V; i++){
		visited[i] = false;
	}
	// call util for all unvisited nodes
	for (int i=0; i<V; i++){
		if(!visited[i]){
			topoSortUtil(i,visited,Stack);
		}
	}
	// Initialize distance array
	double dist[V];
	for(int i=0; i<V; i++){
		dist[i] = INF;
	}
	dist[s]=0;
	// Process each vertex in topo-order
	while(!Stack.empty()){
		int u = Stack.top();
		Stack.pop();
		list<tuple<int,double>>::iterator i;
		if (dist[u]!=INF){
			for(i=adj[u].begin(); i!=adj[u].end(); i++){
				if(dist[get<0>(*i)] > dist[u]+get<1>(*i)){
					dist[get<0>(*i)] = dist[u]+get<1>(*i);
				}
			}
		}
	}
	// Print shortest distances
	for(int i=0; i<V; i++){
		(dist[i] == INF) ? cout<<"INF " : cout<<dist[i]<<" ";
	}
	cout<<endl;
}

int main(){
	
	Graph g(6);
	g.addEdge(0, 1, 5); 
    g.addEdge(0, 2, 3); 
    g.addEdge(1, 3, 6); 
    g.addEdge(1, 2, 2); 
    g.addEdge(2, 4, 4); 
    g.addEdge(2, 5, 2); 
    g.addEdge(2, 3, 7); 
    g.addEdge(3, 4, -1); 
    g.addEdge(4, 5, -2); 
  
    int s = 1; 
    cout << "Following are shortest distances from source " << s <<"\n"; 
    g.shortestPath(s); 
  
    return 0; 
}