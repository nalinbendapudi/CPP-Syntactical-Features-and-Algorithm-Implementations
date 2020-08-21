// CPP program to illustrate use of function pointers or function as variable

#include <iostream>
using namespace std;

int add5(int a){
	return a+5;
}

void forEach (int* a, int n, int(*func)(int) ){
	// This function applies the function 'func' to each element of array a
	for(int i=0; i<n; i++){
		a[i] = func(a[i]);
	}
}

int main() {
	
	int(*f)(int) = add5;	// f is a function stored as a variable
	//auto f = add5;		// This is also a possible way to define f
	cout<<f(12)<<endl;
	
	int a[]= {1,2,3,4};
	int n = 4;
	
	forEach(a,n,f);			// f is a variable. Hence can be passed tp another function
	
	for(int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
	
	return 0;
}