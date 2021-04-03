// Given size of array:n. Initially the array is empty
// Given Query vector: [q1,q2,...qn]
// Each query qi of the form [a,b,k]. Add k to each element of the array from index a to index b (both inclusive)


#include <iostream>
#include <vector>
using namespace std;

void addConstantToSubarrays(vector<int> &arr, const vector<vector<int>> &queries){
	int n = arr.size();
	for(int j=0; j<queries.size(); j++){
        int start = queries[j][0];
        int end = queries[j][1];
        int k = queries[j][2];
        arr[start]+=k;
        if(end<n-1)
            arr[end+1]-=k;
    }
    
    for(int i=1; i<n; i++){
        arr[i] = arr[i]+arr[i-1];
    }
}


int main() {
	int n = 10;
	vector<int> arr(n);
	vector<vector<int>> queries {{1, 5, 3},{4, 8, 7},{6, 9, 1}};
	addConstantToSubarrays(arr,queries);
	for(int i=0; i<n; i++){
		cout<<arr[i]<<" ";
	}
}
