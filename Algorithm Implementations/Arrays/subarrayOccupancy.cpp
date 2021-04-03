// A grid is represented by n arrays, each of size m (i.e. n rows and m columns)
// Occupancy information is represented by tuple (r,c1,c2), which means columns c1 to c2 of row r are occupied
// Find number of unoccupied cells

// k = number of occupancy tuples provided
// Naive solution: O(m*k + n*m)	 // represent grid by n*m booleans and update (c2-c1) booleans using each occupancy tuple 	
// Efficient solution: O(klogk)	 // implemented below

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int unoccupiedCells (int n, int m, vector<vector<int>> occupiedTuples){
	vector<vector<pair<int,int>>> rowwiseOccupiedPairs(n);
	// rowwiseOccupiedPairs[r] contains a vector of <pairs {c1,c2} s.t. (r,c1,c2) is an occupancy tuple>
	for(int i=0; i<occupiedTuples.size(); i++){
		int r = occupiedTuples[i][0]-1;
		int c1 = occupiedTuples[i][1]-1;
		int c2 = occupiedTuples[i][2]-1;
		rowwiseOccupiedPairs[r].push_back({c1,c2});
	}
	
	int unoccupied = 0;
	
	for (int i=0; i<n; i++){
		if (rowwiseOccupiedPairs[i].size() == 0){
			unoccupied += m;
			continue;
		}
		
		sort(rowwiseOccupiedPairs[i].begin(), rowwiseOccupiedPairs[i].end()); 	// will be sorted by the first element of the pairs
		
		int row_unoccupied = rowwiseOccupiedPairs[i][0].first;
		int row_end = rowwiseOccupiedPairs[i][0].second;
		
		for (int j=1; j<rowwiseOccupiedPairs[i].size(); j++){
			if (rowwiseOccupiedPairs[i][j].first > row_end){
				row_unoccupied += rowwiseOccupiedPairs[i][j].first - 1 - row_end;
			}
			row_end = max(row_end, rowwiseOccupiedPairs[i][j].second);
		}
		
		row_unoccupied += m - 1 - row_end;
		
		unoccupied += row_unoccupied;
	}
	
	return unoccupied;
}

int main() {
	int rows=4, cols=4;
	vector<vector<int>> occupiedTuples {
		{2, 2, 3},
		{3, 1, 4},
		{4, 4, 4}
	};
	
	cout<< unoccupiedCells (rows,cols,occupiedTuples);
	return 0;
}

