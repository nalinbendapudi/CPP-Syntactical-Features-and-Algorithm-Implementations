// Implementation of 0-1 Knapsack Algorithm
/* Problem: Given n objects of specified weights[] and values[], we want to select <=n objects such that: 
	 1. their total weight is less than max_weight
	 2. the sum of their values is maximised
*/

#include<iostream>
#include<vector>

using namespace std;

double knapsack(double max_weight, double weights[], double values[], int n){
	
	// Dynamic Programming solution doesn't work for non-integer max_weight
	int W = (int)max_weight;
	
	vector<vector<double> > a(n+1,vector<double>(W+1));
	// a[i][j] is the max value we can obtain if we only consider objects {0,2,...i-1} and the sum of weights should be less than j
	
	for (int i=0; i<=n; i++)
		a[i][0] = 0;
	for (int j=0; j<=W; j++)
		a[0][j] = 0;
	for (int i=1; i<=n; i++){
		for (int j=1; j<=W; j++){
			if (weights[i-1]>j)
				a[i][j] = a[i-1][j];
			else
				a[i][j] = max( a[i-1][j], values[i-1] + a[i-1][j-weights[i-1]] );
		}
	}
	double maxVal = a[n][W];	
	
	cout<<"The following items are selected {weight,value}:\n";
	int j=W;
	for(int i=n; i>0 && maxVal>0; i--){
		if (a[i][j]==a[i-1][j])
			continue;
		else{
			cout<<"{"<<weights[i-1]<<", "<<values[i-1]<<"} ";
			j = j-weights[i-1];
			maxVal = maxVal-values[i-1];
		}
	}
		
	return a[n][W];
}

int main(){
	double weights[] = {12.3, 34.5, 98.6, 43.5, 23.0, 88.1 };
	double max_weight = 205.3; // Dynamic Programming solution doesn't work for non-integer max_weight. This will converted to int in the function	
	double values[] =  {10.6, 45.5, 67.3, 40.0, 10.2, 56.7 };
	int n = sizeof(values)/sizeof(values[0]);
	
	double max_value = knapsack(max_weight, weights,values,n);
	
	cout<<"\nMax Value: "<<max_value<<endl;
	
	return 0;
}
