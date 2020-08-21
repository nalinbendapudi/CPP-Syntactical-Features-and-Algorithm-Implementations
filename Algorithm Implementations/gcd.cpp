#include <iostream>
using namespace std;

int gcd (int a, int b){
	int r = a%b;
	while (r!=0){
		a = b;
		b = r;
		r = a % b;
	}
	return b;
}

int gcdRec (int a, int b){
	if (b==0)
		return a;
	return gcdRec(b,a%b);
}

int main() {
	int a = 30, b=75;
	cout<<gcd(a,b)<<endl;
	cout<<gcdRec(a,b)<<endl;
	return 0;
}