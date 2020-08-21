#include <iostream>
#include <queue>
#include <vector>
# include <stack>
#include <climits>

#define INF INT_MAX

using namespace std;

typedef pair<int,int> coord;
typedef pair<coord,double> info;	

ostream& operator<<(ostream& stream, const coord &a){	// overloading out-stream operator to print coordinates
	stream << "(" << a.first << "," << a.second << ")" ;
	return stream;
}

class compareDist { 	// Utility class to define a comparator for priority queue
public: 
	int operator() (const info &a, const info &b){ 
        return (a.second > b.second); // this inequality sign  is reqd for increasing order
    } 
}; 

class Cell{
public:
	coord parent;
	double f, g, h;		// h: heuristic (approx. dist to dest), g: dist from source, f:=g+h
	void updateF(){
		if (g==INF)
			f=INF;
		else
			f = g+h;
	}
};

class Grid{
	int R,C;
	Cell** cells;
	bool** obstacles;
public:	
	Grid(int R, int C) : R(R) , C(C) {
		cells = new Cell*[R];
		for (int i=0; i<R; i++)
			cells[i] = new Cell[C];
		
		obstacles = new bool*[R];
		for (int i=0; i<R; i++)
			obstacles[i] = new bool[C]();
	}
	bool isValid(int r, int c){
		return r<R && r>=0 && c<C && c>=0;
	}
	void addObstacle(int r, int c){
		obstacles[r][c] = true;
	}
	void calculateHeuristics (coord dest){
		for(int r=0; r<R; r++){
			double x_diff = r-dest.first;
			for(int c=0; c<C; c++){
				double y_diff = c-dest.second;
				cells[r][c].h = min(x_diff,y_diff)*1.4 + abs(x_diff-y_diff);
			}
		}
	}
	double shortestPath (coord src, coord dest){		// Returns the distance of the shortest path. Also prints the path
		
		//initialize visited vector
		vector<vector<bool>> visited (R, vector<bool>(C,false));
		
		// calculate h value for all cells
		calculateHeuristics(dest);
		
		//initialize g and f values for all cells
		for(int r=0; r<R; r++){
			for(int c=0; c<C; c++){
				cells[r][c].g = INF;
				cells[r][c].updateF();
			}
		}
		cells[src.first][src.second].g = 0;
		cells[src.first][src.second].updateF();
		
		// intialize priority queue
		priority_queue <info,vector<info>,compareDist> pq;		// Priority queue contains pairs. Each pair has indices of cell (coord) and f value (double)
		pq.push({src,cells[src.first][src.second].f});
		
		// A* algorithm:
		while(!pq.empty()){
			
			coord current = pq.top().first;
			pq.pop();
			if (current==dest)		// comment-out this if statement if u want to calculate shortest distances to all cells
				break;
			
			int r = current.first, c = current.second;	
			if(visited[r][c])	// we are adding the cell multiple times to the pq, instead of updating it. Hence we might encounter a visited cell
				continue;
			visited[r][c] = true;
			
			int r_next, c_next;
			
			//North
			r_next = r+1, c_next = c;
			if(isValid(r_next,c_next) && !obstacles[r_next][c_next] && !visited[r_next][c_next] && cells[r_next][c_next].g > cells[r][c].g + 1){
				cells[r_next][c_next].g = cells[r][c].g + 1;
				cells[r_next][c_next].updateF();
				cells[r_next][c_next].parent = {r,c};
				pq.push({{r_next,c_next},cells[r_next][c_next].f});
			}
			//South
			r_next = r-1, c_next = c;
			if(isValid(r_next,c_next) && !obstacles[r_next][c_next] && !visited[r_next][c_next] && cells[r_next][c_next].g > cells[r][c].g + 1){
				cells[r_next][c_next].g = cells[r][c].g + 1;
				cells[r_next][c_next].updateF();
				cells[r_next][c_next].parent = {r,c};
				pq.push({{r_next,c_next},cells[r_next][c_next].f});
			}
			//East
			r_next = r, c_next = c+1;
			if(isValid(r_next,c_next) && !obstacles[r_next][c_next] && !visited[r_next][c_next] && cells[r_next][c_next].g > cells[r][c].g + 1){
				cells[r_next][c_next].g = cells[r][c].g + 1;
				cells[r_next][c_next].updateF();
				cells[r_next][c_next].parent = {r,c};
				pq.push({{r_next,c_next},cells[r_next][c_next].f});
			}
			//West
			r_next = r, c_next = c-1;
			if(isValid(r_next,c_next) && !obstacles[r_next][c_next] && !visited[r_next][c_next] && cells[r_next][c_next].g > cells[r][c].g + 1){
				cells[r_next][c_next].g = cells[r][c].g + 1;
				cells[r_next][c_next].updateF();
				cells[r_next][c_next].parent = {r,c};
				pq.push({{r_next,c_next},cells[r_next][c_next].f});
			}
			//North-East
			r_next = r+1, c_next = c+1;
			if(isValid(r_next,c_next) && !obstacles[r_next][c_next] && !visited[r_next][c_next] && cells[r_next][c_next].g > cells[r][c].g + 1.4){
				cells[r_next][c_next].g = cells[r][c].g + 1.4;
				cells[r_next][c_next].updateF();
				cells[r_next][c_next].parent = {r,c};
				pq.push({{r_next,c_next},cells[r_next][c_next].f});
			}
			//North-West
			r_next = r+1, c_next = c-1;
			if(isValid(r_next,c_next) && !obstacles[r_next][c_next] && !visited[r_next][c_next] && cells[r_next][c_next].g > cells[r][c].g + 1.4){
				cells[r_next][c_next].g = cells[r][c].g + 1.4;
				cells[r_next][c_next].updateF();
				cells[r_next][c_next].parent = {r,c};
				pq.push({{r_next,c_next},cells[r_next][c_next].f});
			}
			//South-East
			r_next = r-1, c_next = c+1;
			if(isValid(r_next,c_next) && !obstacles[r_next][c_next] && !visited[r_next][c_next] && cells[r_next][c_next].g > cells[r][c].g + 1.4){
				cells[r_next][c_next].g = cells[r][c].g + 1.4;
				cells[r_next][c_next].updateF();
				cells[r_next][c_next].parent = {r,c};
				pq.push({{r_next,c_next},cells[r_next][c_next].f});
			}
			//South-West
			r_next = r-1, c_next = c-1;
			if(isValid(r_next,c_next) && !obstacles[r_next][c_next] && !visited[r_next][c_next] && cells[r_next][c_next].g > cells[r][c].g + 1.4){
				cells[r_next][c_next].g = cells[r][c].g + 1.4;
				cells[r_next][c_next].updateF();
				cells[r_next][c_next].parent = {r,c};
				pq.push({{r_next,c_next},cells[r_next][c_next].f});
			}
		}
		
		double shortest_dist = cells[dest.first][dest.second].f;
		if (shortest_dist!=INF){
		// Tracing back the hierarchy:
		stack<coord> s;
		coord cell_index = dest;
		while(cell_index!=src){
			s.push(cell_index);
			cell_index = cells[cell_index.first][cell_index.second].parent;
		}
		// Printing the path:
			cout<<"Shortest path is: ";
			cout<<src;
			while(!s.empty()){
				cout<<" --> "<<s.top();
				s.pop();
			}
		}
		return shortest_dist;
	}	
};

int main(){
	
	// Description of the Grid - 1: The cell is not blocked, 0: The cell is blocked
    vector<vector<bool>> grid = 
    { 
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 }, 
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 }, 
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 }, 
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 }, 
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 }, 
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 }, 
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } 
    }; 
	int R = grid.size();
	int C = grid[0].size();
	// Creating a Grid object with R rows and C columns:
	Grid g(R,C);
	// Adding obstacles:
	for(int r=0; r<R; r++)
		for(int c=0; c<C; c++)
			if (!grid[r][c])
				g.addObstacle(r,c);
	
	coord src = {8,0}, dest = {0,0};
	// calling the A* algorithm:
	double res = g.shortestPath(src,dest);
	if(res!=INF)
		cout<<"\nLength of shortest path is: "<<res;
	else
		cout<<"There is no path from "<<src<<" to "<<dest;
	return 0;
}