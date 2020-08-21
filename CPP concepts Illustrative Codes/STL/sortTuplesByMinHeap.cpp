// Run this using g++ -std=C++11 sortVectorOfTuples.cpp

#include<iostream>
#include<tuple>
#include<queue>
#include<algorithm>

using namespace std; 
  
class sortbysec 
{ 
public: 
	// This function has to be named 'operator'
    int operator() (const tuple<int, int, int>& a,  
                    const tuple<int, int, int>& b) 
    { 
        return (get<1>(a) > get<1>(b)); // this inequality sign  is reqd for increasing order
    } 
}; 
int main(){
	
	priority_queue< tuple<int, int, int>, vector<tuple<int, int, int>>, sortbysec > pq;
	pq.push(make_tuple(1, 2, 3)); 
    pq.push(make_tuple(2, 3, 1)); 
    pq.push(make_tuple(3, 1, 2)); 
	
	while (!pq.empty()){
		tuple<int,int,int>pq_top = pq.top();
		cout << get<0>(pq_top) << " " 
             << get<1>(pq_top) << " " 
             << get<2>(pq_top) << "\n";
		pq.pop();
	}			
	
	return 0;
}