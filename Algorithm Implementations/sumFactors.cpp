#include <iostream>
#include<math.h>
using namespace std;

int sumFactors(int num){
	int prod = 1;
	for (int i=2; i<=sqrt(num);i++){
		int sum = 1;
		while(num%i==0){
			num/=i;
			sum=sum*i+1;
		}
		prod*=sum;
	}
	if(num>1)
		prod*=(num+1);
	return prod;
}

int main() {
	for (int i =1; i<=9; i++){
		cout<<sumFactors(i)<<endl;
	}
	return 0;
}