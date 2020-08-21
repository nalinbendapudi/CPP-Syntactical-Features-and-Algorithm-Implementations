// Run this using g++ -std=C++11 sortVectorOfTuples.cpp

#include<iostream>
#include<tuple>
#include<vector>
#include<algorithm>

using namespace std; 
  
bool sortbysec(const tuple<int, int, int>& a,  
               const tuple<int, int, int>& b) 
{ 
    return (get<1>(a) < get<1>(b)); 
} 
  
int main() 
{ 
	vector<tuple<int, int, int> > v; 
    v.push_back(make_tuple(1, 2, 3)); 
    v.push_back(make_tuple(2, 3, 1)); 
    v.push_back(make_tuple(3, 1, 2)); 
  
    cout << "Vector of Tuples (before sorting: \n"; 
    for (int i = 0; i < v.size(); i++)  
        cout << get<0>(v[i]) << " " 
             << get<1>(v[i]) << " " 
             << get<2>(v[i]) << "\n"; 
    
    sort(v.begin(), v.end(), sortbysec); 
    
	cout << "Sorted Vector of Tuple on basis"
           " of Second element of tuple:\n"; 
    for (int i = 0; i < v.size(); i++)  
        cout << get<0>(v[i]) << " " 
             << get<1>(v[i]) << " " 
             << get<2>(v[i]) << "\n";
			 
    return 0; 
} 