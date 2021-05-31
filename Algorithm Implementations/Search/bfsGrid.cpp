#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef pair<int,int> coord;

ostream& operator<<(ostream& stream, const coord& p){
    stream<<"("<<p.first<<","<<p.second<<")";
    return stream;
}

class Cell{
    int data;
};

class Grid{
    Cell** cell;
    bool** obst;
    int R,C;
    
public:
    
    Grid(int R, int C) : R(R), C(C) {
        cell = new Cell*[R];
        for(int i=0; i<R; i++){
            cell[i] = new Cell[C];
        }
        obst = new bool*[R];
        for(int i=0; i<R; i++){
            obst[i] = new bool[C]();
        }
    }
    
    void addObst(int x, int y){
        obst[x][y] = true;
    }
    
    bool isValid (coord p){
        if(p.first>=0 && p.first<R)
            if(p.second>=0 && p.second<C)
                if(!obst[p.first][p.second])
                    return true;
        return false;
    }   
    
    void bfs(coord start, coord goal){
        vector<vector<bool>> queued (R, vector<bool>(C,false));
        queue<pair<coord,int>> q;
        int current_level = -1;
        
        q.push({start,0});
        queued[start.first][start.second] = true;
        
        while(!q.empty()){
            coord p = q.front().first;
            int lvl = q.front().second;
            q.pop();
            if (lvl > current_level){
                cout<<"\n"<<lvl<<" --> ";
                current_level = lvl;
            }
            cout<<p<<" ";
            
            // comment if you want to do BFS on entire grid without stopping at goal
            if (p.first==goal.first && p.second==goal.second)
                break;
            
            int x = p.first, y = p.second;
            
            if (isValid({x-1,y}) && !queued[x-1][y]){
                q.push({{x-1,y},lvl+1});
                queued[x-1][y] = true;
            }
            if (isValid({x+1,y}) && !queued[x+1][y]){
                q.push({{x+1,y},lvl+1});
                queued[x+1][y] = true;
            }
            if (isValid({x,y-1}) && !queued[x][y-1]){
                q.push({{x,y-1},lvl+1});
                queued[x][y-1] = true;
            }
            if (isValid({x,y+1}) && !queued[x][y+1]){
                q.push({{x,y+1},lvl+1});
                queued[x][y+1] = true;
            }            
        }
    }
};


int main() {
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
				g.addObst(r,c);
    
	pair<int,int> start = {8,0}, goal = {0,0};
	g.bfs(start,goal);
	
}