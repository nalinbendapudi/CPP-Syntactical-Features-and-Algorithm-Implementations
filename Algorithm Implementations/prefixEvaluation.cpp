#include <iostream>
#include <vector>
#include <string>
using namespace std;

int eval_list(vector<string> v);

int evaluate (string expr){
	vector<string> v;
	string s="";
    for(int i=0; i<expr.length();){
		if(expr[i]==' ' || expr[i]== '(' || expr[i]== ')'){
			v.push_back(s);
            s="";
		}
		while(expr[i]==' ' || expr[i]== '(' || expr[i]== ')'){
			i++;
		}
		s+=expr[i];
		i++;
	}
    v.push_back(s);
    // for(auto str:v){
    //     cout<<str<<endl;    
    // }
	return eval_list(v);
}
 
int eval_list(vector<string> v){
    stack <int> s;
    for(int i=v.size()-1; i>=0; i--){
        string str = v[i];
        if(isdigit(str[0])){
            s.push(stoi(str));
        }
        else if (str == "+"){
            int x1 = s.top();
            s.pop();
            int x2 = s.top();
            s.pop();
            s.push(x1+x2);
        }
        else if (str == "-"){
            int x1 = s.top();
            s.pop();
            int x2 = s.top();
            s.pop();
            s.push(x1-x2);
        }
        else if (str == "*"){
            int x1 = s.top();
            s.pop();
            int x2 = s.top();
            s.pop();
            s.push(x1*x2);
        }
        else if (str == "/"){
            int x1 = s.top();
            s.pop();
            int x2 = s.top();
            s.pop();
            s.push(x1/x2);
        }
    }
    return s.top();
}
 
int main() {
 
	string expr = "(- 14 (+ 6 4))";
	// string expr = "+ (- 12 4) 8";
    cout<<evaluate(expr);
	
 
	return 0;
}