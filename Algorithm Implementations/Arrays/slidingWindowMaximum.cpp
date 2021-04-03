#include <iostream>
#include <deque> 
using namespace std;

// Given an n-element array. Output an array containing maximums of k-elem subarrays. Out size should be n-k+1

void printKMax(int arr[], int n, int k){
	deque <int> q;
    int i;
    
    for(i=0; i<k; i++){
        while(!q.empty() && arr[i]>arr[q.back()]){
            q.pop_back();
        }
        q.push_back(i);
    }

    for(;i<n;i++){
        cout<<arr[q.front()]<<" ";
        if(!q.empty() && q.front()<=i-k){
            q.pop_front();
        }
        while(!q.empty() && arr[i]>arr[q.back()]){
            q.pop_back();
        }
        q.push_back(i);
    }
  
    cout<<arr[q.front()]<<endl;
}

int main(){
  
	int k = 3;
	int n = 9;
	int arr[n] = {23, 43, 32, 45, 41, 39, 21, 22, 50};
	// int arr[n] = {23, 13, 32, 25, 41, 39, 21, 22, 50};
    printKMax(arr, n, k);
  	return 0;
}