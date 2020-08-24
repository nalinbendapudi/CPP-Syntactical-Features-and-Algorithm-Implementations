#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <unordered_set>
#include <cmath>
#include <random>

using namespace std;

random_device rand_dev;
mt19937 gen(rand_dev());	// Declaring random number generator

class Point{
public:
	double x,y;		// cartesian coordinates of the point
	Point(double x, double y) : x(x), y(y) {
	}
	Point(){
	}
	double sqDist(const Point &other) const{
		//Returns square of distance between point (x,y) and (other.x,other.y)
		return (x-other.x)*(x-other.x) + (y-other.y)*(y-other.y);
	}
	Point interpolate(const Point &other, double step) const{
		//Returns a point which lies on the line segment joining this point and other point, at a distance of 'step' units from this point
		double dist = sqrt(sqDist(other));
		return Point( x+(other.x-x)*step/dist , y+(other.y-y)*step/dist );
	}
};

ostream& operator<<(ostream& stream, const Point &p){
	// overloading out-stream operator to print Point class objects
	stream << "(" << p.x << "," << p.y << ")" ;
	return stream;
}

class LineSegment{
	Point p1,p2;	//End-points of line segment
public:
	LineSegment(double x1, double y1, double x2, double y2)  { 	// Overloaded Constructor
		p1 = Point(x1,y1);
		p2 = Point(x2,y2);
	}
	LineSegment(Point p1, Point p2) : p1(p1), p2(p2) {			// Overloaded constructor
	}
	bool intersects (const LineSegment &other) const{
		/* Line segment defined by points p1 and p2 intersects line segment defined by other.p1 and other.p2 if and only if both of the following conditions are ture:
			1. other.p1 and other.p2 lie on opposite sides of line defined by p1 and p2
			2. p1 and p2 lie on opposite sides of line defined by other.p1 and other.p2
		Above rule can't be applied if any 3 points are colinear.
			If a point is colinear with points of the other line segment, check if it lies between the points of the other line segment
			For example, if other.p1 is colinear with p1 and p2, check if other.p1 is in between p1 and p2
			If points A,B,C are colinear, then B lies on line segment AC iff min(A.x,C.x)<=B.x<=max(A.x,C.x) AND min(A.y,C.y)<=B.y<=max(A.y,C.y)
		*/
		double diff1 = (other.p1.y - p1.y) * (p2.x - p1.x) - (other.p1.x - p1.x) * (p2.y - p1.y);	// other.p1 w.r.t. line p1-p2
		double diff2 = (other.p2.y - p1.y) * (p2.x - p1.x) - (other.p2.x - p1.x) * (p2.y - p1.y);	// other.p2 w.r.t. line p1-p2
		double diff3 = (p1.y - other.p1.y) * (other.p2.x - other.p1.x) - (p1.x - other.p1.x) * (other.p2.y - other.p1.y);	// p1 w.r.t. line other.p1-other.p2
		double diff4 = (p2.y - other.p1.y) * (other.p2.x - other.p1.x) - (p2.x - other.p1.x) * (other.p2.y - other.p1.y);	// p2 w.r.t. line other.p1-other.p2

		if (diff1==0){			// other.p1 is colinear with p1 and p2
			if( min(p1.x,p2.x) <= other.p1.x && other.p1.x <= max(p1.x,p2.x) && min(p1.y,p2.y) <= other.p1.y && other.p1.y <= max(p1.y,p2.y))
				return true;	// other.p1 lies between p1 and p2
		}
		if (diff2==0){		// other.p2 is colinear with p1 and p2
			if( min(p1.x,p2.x) <= other.p2.x && other.p2.x <= max(p1.x,p2.x) && min(p1.y,p2.y) <= other.p2.y && other.p2.y <= max(p1.y,p2.y))
				return true;	// other.p2 lies between p1 and p2
		}
		if (diff3==0){		// p1 is colinear with other.p1 and other.p2
			if( min(other.p1.x,other.p2.x) <= p1.x && p1.x <= max(other.p1.x,other.p2.x) && min(other.p1.y,other.p2.y) <= p1.y && p1.y <= max(other.p1.y,other.p2.y))
				return true;	// p1 lies between other.p1 and other.p2
		}
		if (diff4==0){		// p2 is colinear with other.p1 and other.p2
			if( min(other.p1.x,other.p2.x) <= p2.x && p2.x <= max(other.p1.x,other.p2.x) && min(other.p1.y,other.p2.y) <= p2.y && p2.y <= max(other.p1.y,other.p2.y))
				return true;	// p2 lies between other.p1 and other.p2
		}
		if(diff1==0 || diff2==0 || diff3==0 || diff4==0)	// A,B,C are colinear in one or more cases, but B doesn't lie on AC in any case (else it would have returned true by now)
			return false;
		// no 3 points are colinear
		return (diff1 > 0)^(diff2 > 0) && (diff3 > 0)^(diff4 > 0);	// Condition 1 AND Condition 2 from above

	}
	bool pointOnLineSegment(const Point &p) const{
		if((p.y - p1.y) * (p2.x - p1.x) - (p.x - p1.x) * (p2.y - p1.y) == 0){
			if( min(p1.x,p2.x) <= p.x && p.x <= max(p1.x,p2.x) && min(p1.y,p2.y) <= p.y && p.y <= max(p1.y,p2.y)){
				return true;
			}
		}
		return false;
	}
};

class Environment{
	int searchSpace_x; 		// Width of 2D search space
	int searchSpace_y;		// Heigh of 2D search space

	vector<LineSegment> obstacles;	// Data structure to store obstacles (Obstacles are modeled as line-segments)

	uniform_real_distribution<double> uniform01Distr = uniform_real_distribution<double>(0,1);	// Uniform Random number generator

public:
	Environment(int x, int y) : searchSpace_x(x), searchSpace_y(y){
	}
	void addObstacles (LineSegment ls){								// overloaded function to add obstacles
		obstacles.push_back(ls);
	}
	void addObstacles (Point p1, Point p2){							// overloaded function to add obstacles
		obstacles.push_back(LineSegment(p1,p2));
	}
	void addObstacles (double x1, double y1, double x2, double y2){	// overloaded function to add obstacles
		obstacles.push_back(LineSegment(x1,y1,x2,y2));
	}
	bool collisionCheck (const LineSegment &ls) const{			// returns true if ls intersects with any of the obstacles
		for (auto obstacle : obstacles){
			if (obstacle.intersects(ls)){
				return true;
			}
		}
		return false;
	}
	bool collisionCheck (const Point &p) const{
		for (auto obstacle : obstacles){
			if (obstacle.pointOnLineSegment(p)){
				return true;
			}
		}
		return false;
	}
	Point genRandomPoint(){
		double x = uniform01Distr(gen);
		double y = uniform01Distr(gen);
		return Point(x*searchSpace_x, y*searchSpace_y);
	}
	LineSegment genRandomLineSegment(){
		Point p1 = genRandomPoint();
		Point p2 = genRandomPoint();
		return LineSegment(p1,p2);
	}
};

class RRT {
	// Hyper-Parameters:
	double stepSize;		// Next node is this distance away from the nearest explored node
	double nbdSize;			// The neighbourhood from which parent is chosen is a square with side-length='nbdSize'*2. nbdSize should be greater than stepSize
	double goalRadius;		// The goal is a circle of radius='goalRadius' centered at the goal-point
	double goalBias;		// number between 0 and 1. Probability with which next node is chosen in the direction of the goal

	// Data structures to store nodes (Nodes are modeled as points)
	vector<Point> nodes;
	vector<int> parent;				// parent[i] contains the index (in the vector: nodes) of the parent of the node at nodes[i]
	vector<vector<int>> children;	// children[i] contains a vector of indices of the the direct children of node at nodes[i]
	vector<double> distance;		// distance[i] contains the distance (fromsource node) of the node at nodes[i]
	map<double,int> xMap;			// stores x-ccordinates of nodes in sorted order, so that nearest node can be found is O(logn) time
	map<double,int> yMap;			// stores y-ccordinates of nodes in sorted order, so that nearest node can be found is O(logn) time

	int nearestNodeIndex(const Point &p){
		// This is an O(n) method. This should be replaced with O(logn) method using balanced kd-tree
		int minIndex=0;
		double minDist = p.sqDist(nodes[0]);
		for (int i=1; i<nodes.size(); i++){
			double dist = p.sqDist(nodes[i]);
			if (dist<minDist){
				minDist = dist;
				minIndex = i;
			}
		}
		return minIndex;
	}

	vector<int> neighbourNodeIndices (const Point &p){
		double min_x = p.x - nbdSize;
		double max_x = p.x + nbdSize;
		double min_y = p.y - nbdSize;
		double max_y = p.y + nbdSize;

		unordered_set<int> xSet, ySet;
		map<double,int>::iterator it_low,it_high;
		vector<int> neighbours;

		it_low = xMap.lower_bound(min_x);
		it_high = xMap.upper_bound(max_x);
		for(auto it=it_low; it!=it_high; it++){
			xSet.insert(it->second);
		}
		it_low = yMap.lower_bound(min_y);
		it_high = yMap.upper_bound(max_y);
		for(auto it=it_low; it!=it_high; it++){
			ySet.insert(it->second);
		}
		for (auto itr = xSet.begin(); itr != xSet.end(); itr++) {
            if(ySet.find(*itr)!=ySet.end()){
					neighbours.push_back(*itr);
				}
		}
        return neighbours;
	}

	void printAncestory(const int targetIndex){
		// Prints hiearchy from source (index=0 in nodes vector) to targetIndex
		stack<int> s;
		int index = targetIndex;
		while(index!=0){
			s.push(index);
			index = parent[index];
		}
		cout<<0<<" "<<nodes[0]<<endl;
		while(!s.empty()){
			cout<<" --> "<<s.top()<<" "<<nodes[s.top()]<<endl;
			s.pop();
		}
	}

	void updateChildrenDistances(int index){
		// This function will be called after the 'distance' of a node is updated, so that the 'distance's of the node's  descendants could also be updated accordingly
		for (int child : children[index]){
			distance[child] = distance[index] + sqrt(nodes[index].sqDist(nodes[child]));
			updateChildrenDistances(child);
		}
	}

public:
	RRT(double stepSize, double nbdSize, double goalRadius, double goalBias) : stepSize(stepSize), nbdSize(nbdSize), goalRadius(goalRadius), goalBias(goalBias){
	}
	void rrt_star(Point src, Point goal, Environment env){
		nodes.push_back(src);
		distance.push_back(0);
		parent.push_back(0);
		xMap.insert({src.x,0});
		yMap.insert({src.y,0});
		children.push_back({});
		if (src.sqDist(goal) < goalRadius*goalRadius){
			cout<<"source is already at the goal point";
			return;
		}
		else{
			cout<<"source (Node 0) at "<<src<<endl;
            cout<<"Goal is at "<<goal<<endl;
		}
		bernoulli_distribution bernoulli01Distr(goalBias);
		int numNodes = 0;
		while(true){
			/*
				Step ONE: Choose Next Node's direction (Either randomly or towards the goal)
			*/
			Point nextNode;
			if(bernoulli01Distr(gen)){	// choose new node towards goal
				nextNode = goal;
			}
			else{	// select new random node
				nextNode = env.genRandomPoint();
			}
			/*
				Step TWO: Find nearest node (possible parent node), and interpolate to bring the newNode upto 'stepSize' distance from its parent
			*/
			int parentIndex = nearestNodeIndex(nextNode);
			if(nodes[parentIndex].sqDist(nextNode) > stepSize*stepSize)
				nextNode = nodes[parentIndex].interpolate(nextNode,stepSize);
			/*
				Step THREE: Check for obstacle collision
			*/
			if(env.collisionCheck(LineSegment(nodes[parentIndex],nextNode))){		// If collisionCheck returns true, that is line segment intersects with some obstacle
					continue;															// We do nothing in this iteration
				}
			else{																	// If collision check returns false, that is line segement doesn't intersect any obstacle
				numNodes++;															// We add the nextNode to the tree
				nodes.push_back(nextNode);
				xMap.insert({nextNode.x,numNodes});
				yMap.insert({nextNode.y,numNodes});
				parent.push_back(parentIndex);
				distance.push_back(distance[parentIndex] + sqrt(nodes[parentIndex].sqDist(nextNode)));
				children.push_back({});
			}
			/*
				Step FOUR: Choose optimal parent for nextNode from neighbouring nodes such that its distance is minimized
			*/
			for (int neighborIndex : neighbourNodeIndices(nextNode)){
				if(distance[numNodes] > distance[neighborIndex] + sqrt(nodes[neighborIndex].sqDist(nextNode))){
					if(env.collisionCheck(LineSegment(nodes[neighborIndex],nextNode))){
						parent[numNodes] = neighborIndex;
						distance[numNodes] = distance[neighborIndex] + sqrt(nodes[neighborIndex].sqDist(nextNode));
					}
				}
			}
			children[parent[numNodes]].push_back(numNodes);
			/*
				Step FIVE: Check if distance of any of the neighbouring nodes can be minimized if nextNode becomes their parent
							If any such rewiring can be done for a neighbouring node, distances of all its children (and descendants) need to be updated recursively
			*/
			for (int neighborIndex : neighbourNodeIndices(nextNode)){
				if(distance[neighborIndex] > distance[numNodes] + sqrt(nodes[neighborIndex].sqDist(nextNode))){
					if(env.collisionCheck(LineSegment(nodes[neighborIndex],nextNode))){
						parent[neighborIndex] = numNodes;
						distance[neighborIndex] = distance[numNodes] + sqrt(nodes[neighborIndex].sqDist(nextNode));
						updateChildrenDistances(neighborIndex);
					}
				}
			}
            /*
				Step SIX: Break from the loop if nextNode is within 'goalRadius' distance to the goal
			*/
			if(nextNode.sqDist(goal) < goalRadius*goalRadius){
				cout<<"Goal reached !!"<<endl;
				cout<<"Total Number of Nodes generated: "<<numNodes<<endl;
				cout<<"Distance of path from source to goal: "<<distance[numNodes]<<endl;
				cout<<"Nodes in the shortest path from source to goal:\n";
				printAncestory(numNodes);
				break;
			}
		}
	}
};

int main(){
	int windowX = 500, windowY = 500;
	Environment env(windowX,windowY);

/* // GENERATE RANDOM OBSTACLES, SOURCE AND DESTINATION
	int numObstacles = 5;
	for (int i=0; i<numObstacles; i++){
		env.addObstacles(env.genRandomLineSegment());	// Creating random obstacles
	}
	Point src = env.genRandomPoint();
	while(env.collisionCheck(src))			// If random src point lies on any of the obstacles, generate another random point
		src = env.genRandomPoint();
	Point goal = env.genRandomPoint();
	while(env.collisionCheck(goal))		// If random goal point lies on any of the obstacles, generate another random point
		goal = env.genRandomPoint();
*/
	// Rectangular Obstacle in the middle of the window
	env.addObstacles(LineSegment(100,100,100,400));
	env.addObstacles(LineSegment(100,400,400,400));
	env.addObstacles(LineSegment(400,400,400,100));
	env.addObstacles(LineSegment(400,100,100,100));
	// Source and Goal at diagonally opposite ends
	Point src(50,50);
	Point goal(450,450);
	// Hyper-parameters:
	double stepSize = 5, nbdSize = 10, goalRadius = 1, goalBias = 0.1;

	RRT rrtObj(stepSize, nbdSize, goalRadius, goalBias);
	rrtObj.rrt_star(src,goal,env);

	return 0;
}
