// Count number of continous sub-arrays whose sum is K
// This is same as counting number of pairs of elements with a difference of K 
//  ... in the cumulative sum array.
// We store the cumulative sums in a hash map.

#include<iostream>
#include<vector>
#include<unordered_map> // Use g++ -std=c++11 to run this file
using namespace std;

int subArraySum(vector<int>v , int k){
	int subArrayCount = 0;
	int cumulativeSum = 0;
	unordered_map<int,int> cumSumCounts;
	cumSumCounts.insert(make_pair(0,1));
	
	for(int i=0; i<v.size(); i++){
		cumulativeSum+=v[i];
		subArrayCount+= cumSumCounts[cumulativeSum-k];
		cumSumCounts[cumulativeSum]++;
	}
	
	return subArrayCount;
}

int main(){
	vector<int> vect{2,-1,3,1,2,-1,2,-2};
	int k =2;
	int countSubArray = subArraySum(vect,k);
	cout<<countSubArray<<endl;
	
	return 0;
}