// Given coin denominations: c[0],c[1], ....c[n-1]. We have infinte number of coins of each denomination
// Find number of ways to get change for W amount of money

#include <iostream>
#include <vector>
using namespace std;


long long getWays(const int &W, const vector<long long> &c) {
    int N = c.size(); 
    long long numberOfWays[N+1][W+1];
    
    // numberOfWays[i][j] represents number of ways to provide j units only using
    // coins of units: c[0],c[1],c[2],...c[i-1]
    
    for (int i=0; i<=N; i++){    
        for (int j=0; j<=W; j++)
            numberOfWays[i][j] = 0;
    }

    for(int i=1; i<=N; i++){
        if(c[i-1]<=W)
            numberOfWays[i][c[i-1]] = 1;
    }
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=W; j++){
            if(c[i-1]>j)
                numberOfWays[i][j]+= numberOfWays[i-1][j];
            else{
                numberOfWays[i][j]+= (numberOfWays[i-1][j] + numberOfWays[i][j-c[i-1]]);
            }
        }
    }
    
    
    return numberOfWays[N][W];
}

int main() {
	int W = 10;
	vector<long long> c{2, 5, 3, 6};
	cout<< getWays(W,c);
}