#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Point{
    double x;
    double y;
public:
    int label;
    Point(double x, double y) : x(x), y(y) {}
    Point(double x, double y, int l) : x(x), y(y), label(l) {}
    double dist (const Point &p){
        return (x-p.x)*(x-p.x) + (y-p.y)*(y-p.y);
    }
};

class KNN{
    vector<Point> points;
public:
    KNN(){
        points = {};
    }
    void addPoint(Point p){
        points.push_back(p);
    }
    int classify (Point newPoint, int K){
        auto comp = [newPoint]( Point p1, Point p2 ) { return p1.dist(newPoint) > p2.dist(newPoint); };
        priority_queue <Point, vector<Point>, decltype(comp)> dist_pq (comp);
        for(Point p : points){
            dist_pq.push(p);
        }
        unordered_map<int,int> labels_umap;
        for (int i=0; i<K; i++){
            int lbl = dist_pq.top().label;
            // cout<<lbl<<" ";
            labels_umap[lbl]++;
            dist_pq.pop();
        }
        // cout<<endl;
        int max = 0, maxLabel;
        for (auto itr = labels_umap.begin(); itr != labels_umap.end(); itr++){
            if(itr->second > max){
                max = itr->second;
                maxLabel = itr->first;
            }
        }
        
        return maxLabel;
    }
};

int main() {
    KNN knn;
    knn.addPoint(Point(0,0,0));
    knn.addPoint(Point(0,1,1));
    knn.addPoint(Point(0,2,2));
    knn.addPoint(Point(0,3,3));
    int label = knn.classify(Point(0,1.49), 4);
    cout<<label;
    
}