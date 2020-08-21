#include <iostream>
#include <list>
#include <queue>
#include <vector>
# include <stack>
#include <climits>

#define INF INT_MAX

using namespace std;

typedef pair<int,double> info;	

class compareDist { 	// Utility class to define a comparator for priority queue
public: 
	int operator() (const info &a, const info &b){ 
        return (a.second > b.second); // this inequality sign  is reqd for increasing order
    } 
}; 

class Vertex {
public:
	int parent;
	list<info> adj;	// list of pairs. Each pair has index of node (int) and weight of edge to that node (double)
};

class Graph{
	int V; 				// Number of vertices
	Vertex* vertex;		// Array of vertices
	bool directed;		// true if graph is directed
public:
	Graph(int V, bool directed = true) : V(V), directed(directed) {
		vertex = new Vertex[V];
	}
	~Graph(){
		delete []vertex;
	}
	void addEdge (int v1, int v2, double weight){	// adds a directed edge from v1 to v2 if graph is directed. If undirected, adds edge inopposite direction also
		vertex[v1].adj.push_back({v2,weight});
		if(!directed)
			vertex[v2].adj.push_back({v1,weight});
	}
	double shortestPath (int src, int dest){		// returns the distance of shortest path from src to dest. Also prints the path
		
		//initialize visited vector
		vector <bool> visited (V,false);
		
		//initialize distance vector
		vector <double> dist (V,INF);
		dist[src] = 0;
		
		// intialize priority queue
		priority_queue <info,vector<info>,compareDist> pq;		// Priority queue contains pairs. Each pair has index of node (int) and dist from source (double)
		pq.push({src,0});
		
		// Dijksta Algorithm:
		while(!pq.empty()){
			int current = pq.top().first;
			pq.pop();
			if (current==dest)		// comment out this if statement if u want to calculate shortest distances to all vertices
				break;
			if(visited[current])	// we are adding the vertex multiple times to the pq, instead of updating it. Hence we might encounter a visited vertex
				continue;
			visited[current] = true;
			
			list <info> :: iterator i;
			for(i=vertex[current].adj.begin(); i!=vertex[current].adj.end(); i++){
				int next = (*i).first;
				double weight = (*i).second;
				if(!visited[next] && dist[next]>dist[current]+weight){
					dist[next] = dist[current]+weight;
					vertex[next].parent = current;
					pq.push({next,dist[next]});
				}
			}			
		}
		
		if (dist[dest]!=INF){
		// Tracing back the hierarchy:
		stack<int> s;
		int vertex_index = dest;
		while(vertex_index!=src){
			s.push(vertex_index);
			vertex_index = vertex[vertex_index].parent;
		}
		// Printing the path:
			cout<<"Shortest path is: ";
			cout<<src;
			while(!s.empty()){
				cout<<" --> "<<s.top();
				s.pop();
			}
		}
		
		return dist[dest];
	}
};
	
int main(){
	
	Graph g(10,false);	// Creating an undirected graph of 10 vertices
	g.addEdge(0, 1, 4); 
    g.addEdge(0, 7, 8); 
    g.addEdge(1, 2, 8); 
    g.addEdge(1, 7, 11); 
    g.addEdge(2, 3, 7); 
    g.addEdge(2, 8, 2); 
    g.addEdge(2, 5, 4); 
    g.addEdge(3, 4, 9); 
    g.addEdge(3, 5, 14); 
    g.addEdge(4, 5, 10); 
    g.addEdge(5, 6, 2); 
    g.addEdge(6, 7, 1); 
    g.addEdge(6, 8, 6); 
    g.addEdge(7, 8, 7);  
	
	int src = 0, dest = 5;
	double res = g.shortestPath(src,dest);
	if(res!=INF)
		cout<<"\nLength of shortest path is: "<<res;
	else
		cout<<"There is no path from "<<src<<" to "<<dest;
	return 0;
}	