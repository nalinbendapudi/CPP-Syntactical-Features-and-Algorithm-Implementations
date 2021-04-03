#include <iostream>
#include <vector> 
using namespace std;

// Given an array, find the largest sub-array sum 
// Array can contain negative numbers (otherwise largest subarray sum is equal to array sum)

int largestSubarraySum (const vector<int> &v){
    int sum = 0, maxSum = 0;
    for(int i=0; i<v.size(); i++){
        if(v[i]>0){
            sum+=v[i];
        }
        else{
            if(maxSum<sum)
                maxSum = sum;
            sum+=v[i];
            if(sum<0){
                sum=0;
            }
        }
    }
    if(maxSum < sum)
        maxSum = sum;
    
    return maxSum;
}

int main() {
    vector<int> v= {-2,-3,4,-1,-2,1,5,-3};
    cout<< largestSubarraySum(v);
}