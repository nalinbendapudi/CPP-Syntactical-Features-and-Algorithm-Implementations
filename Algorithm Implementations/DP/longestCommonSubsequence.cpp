#include <bits/stdc++.h>

using namespace std;

vector<int> longestCommonSubsequence(vector<int> a, vector<int> b) {

    int n = a.size(), m = b.size();
    vector<vector<int>> matrix (n+1, vector<int> (m+1,0));
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(a[i-1] == b[j-1]){
                matrix[i][j] = 1 + matrix[i-1][j-1];
            }
            else{
                matrix[i][j] = max(matrix[i-1][j] , matrix[i][j-1]);
            }
        }
    }
    
    int longestLength = matrix[n][m];
    cout<<"length of lcs: "<< longestLength<<endl;
    
    int i=n, j=m;
    stack<int> s;
    while(s.size() < longestLength){
        if(a[i-1] == b[j-1]){
            s.push(a[i-1]);
            i--; j--;
        }
        else{
            if(matrix[i-1][j] > matrix[i][j-1]){
                i--;
            }
            else{
                j--;
            }    
        }
    }
    
    vector<int> seq;
    while(!s.empty()){
        seq.push_back(s.top());
        s.pop();
    }
    
    return seq;
}

int main(){
  
	vector<int> a = {1,2,3,4,5};
	vector<int> b = {2,3,5,6};
	
	vector<int> lcs = longestCommonSubsequence(a,b);
	cout<<"lcs: ";
    for(int i=0; i<lcs.size(); i++)
        cout<<lcs[i]<<" ";
	return 0;
}