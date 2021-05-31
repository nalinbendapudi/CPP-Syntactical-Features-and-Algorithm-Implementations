/*
C++ concepts used in this implementation:
1. STL set is used as a priority queue for A* as STL priority queue doesn't have anyway to update values. In STL set we can delete and re-insert values
2. Since the values of set are Node*, a comparator needs to be defined using a lambda function
3. STL unordered_map is used as as standard hash map (similar to python dictionary)
4. Since the keys of unordered_map are pair<int,int>, a hash needs to be defined using a lambda function
5. A-star search takes functions for finding heuristics and neighbours as arguments using function pointers
6. A new type 'coord' is defined using typedef
7. Print function for 'coord' is defined using operator overloading
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <math.h>
#include <algorithm>

using namespace std;

// 2D coordinate (x,y)
typedef pair<int, int> coord;
ostream& operator<< (ostream &stream, coord config){
    stream <<"(" <<config.first <<","<<config.second <<")";
    return stream;
}

// Occupance Grid class
class OccGrid{
public:
    vector<vector<bool>> grid;
    int numRows, numCols;
    OccGrid(const vector<vector<bool>> &grid) : grid(grid) {
        numRows = grid.size();
        numCols = grid[0].size();
    }
    bool isValid (coord config) const{
        return config.first >= 0 && config.first < numRows && config.second >= 0 && config.second <numCols;
    }
    bool isFree(coord config) const{
        return grid[config.first][config.second];
    }
    bool isOccupied(coord config) const{
        return !grid[config.first][config.second];
    }
};

// Functions to find neighbours
vector<pair<coord,double>> get_4way_nbrs (const coord& config){
    int x = config.first, y= config.second;
    return { {{x,y+1},1}, {{x,y-1},1}, {{x+1,y},1}, {{x-1,y},1} };
}
vector<pair<coord,double>> get_8way_nbrs (const coord& config){
    int x = config.first, y= config.second;
    return { {{x,y+1},1}, {{x,y-1},1}, {{x+1,y},1}, {{x-1,y},1}, {{x-1,y-1},1.4}, {{x-1,y+1},1.4}, {{x+1,y-1},1.4}, {{x+1,y+1},1.4} };
}

// Distance functions (for heuristic)
double manhattan_dist(const coord& config1, const coord& config2){
    double dx = abs(config1.first - config2.first);
    double dy = abs(config1.second - config2.second);
    return dx + dy;
}
double diagonal_dist(const coord& config1, const coord& config2){
    double dx = abs(config1.first - config2.first);
    double dy = abs(config1.second - config2.second);
    return 1.4*min(dx,dy) + abs(dx-dy);
}
double euclidean_dist(const coord& config1, const coord& config2){
    double dx = config1.first - config2.first;
    double dy = config1.second - config2.second;
    return sqrt(dx*dx + dy*dy);
}

// A-star Node class
class Node{
public:
    coord config;
    Node* parent;
    double g,h,f;
    Node (coord config, double g, double h, Node* p = nullptr) : config(config), parent(p){
        this->g = g;
        this->h = h;
        f = g+h;
    }
};

vector<coord> find_path (Node* node_ptr){
    vector<coord> path;
    while (node_ptr!=nullptr){
        path.push_back(node_ptr->config);
        node_ptr = node_ptr->parent;
    }
    reverse(path.begin(), path.end());
    return path;
}

// A-star function
vector<coord> astar_search(const OccGrid &grid, coord& startconfig, coord& stopconfig, double (*heuristic)(const coord&, const coord&), vector<pair<coord,double>>(*get_nbrs)(const coord&) ){
    
    auto coord_hash = [&grid](coord config){
        return hash<int>()(config.first * grid.numCols + config.second);
    };
    unordered_map<coord, Node*, decltype(coord_hash)> config_node_map (1,coord_hash);
    
    auto node_comp = [&coord_hash](Node* nodeptr1, Node* nodeptr2){
        if(nodeptr1->f < nodeptr2->f)
            return true;
        if(nodeptr1->f > nodeptr2->f)
            return false;
        if(coord_hash(nodeptr1->config) < coord_hash(nodeptr2->config))
			return true;
		return false;
    };
    set< Node*, decltype(node_comp) > prio_que (node_comp);
    
    Node* startnode_ptr = new Node(startconfig,0,heuristic(startconfig,stopconfig));
    prio_que.insert(startnode_ptr);
    config_node_map[startconfig] = startnode_ptr;
    
    while(!prio_que.empty()){
        
        Node* node_ptr = *prio_que.begin();
        prio_que.erase(prio_que.begin());
        // cout<< node_ptr->config <<" "<<node_ptr->f <<": ";
        
        if (node_ptr->config == stopconfig){
            cout << "Goal distance is "<< node_ptr->g << endl;
            return find_path(node_ptr);
        }

        for(auto& nbr :  get_nbrs(node_ptr->config)){
            coord nbrconfig = nbr.first;
            double dist = nbr.second;
            if (grid.isValid(nbrconfig) && grid.isFree(nbrconfig)){
                // cout<<nbrconfig<<" ";
                Node* nbrnode_ptr = new Node(nbrconfig, node_ptr->g + dist, heuristic(nbrconfig,stopconfig), node_ptr);
                if (!config_node_map.count(nbrconfig)){
                    // cout<<nbrconfig<<" ";
                    prio_que.insert(nbrnode_ptr);
                    config_node_map[nbrconfig] = nbrnode_ptr;
                }
                else if (config_node_map[nbrconfig]->g > nbrnode_ptr->g){
                    // cout<<nbrconfig<<" ";
                    prio_que.erase(config_node_map[nbrconfig]);
                    prio_que.insert(nbrnode_ptr);
                    config_node_map[nbrconfig] = nbrnode_ptr;
                }
            }
        }
        // cout<<endl;
	    // cout<<"q - ";
	    // for (auto const& a : prio_que){
	    // cout<< a->config << " " << a->f << " ";
	    // }
	    // cout<<endl;
	

    }
    
    return {};
}

int main() {
    
    // Description of the Grid
    // 1: The cell is not blocked, 0: The cell is blocked
    OccGrid grid({ 
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 }, 
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 }, 
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 }, 
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 }, 
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 }, 
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 }, 
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 }, 
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } 
    }); 
	
    coord startconfig = {0,0};
    coord stopconfig  = {6,9};
    
    
    vector<coord> path = astar_search(grid, startconfig, stopconfig, diagonal_dist, get_8way_nbrs);
    if (path.size() == 0)
        cout<<"Goal not found" <<endl;
    else{
        cout<<"Path:"<<endl;
        for (const coord& config: path){
            cout<<config<<" ";
        }
    }
    
}