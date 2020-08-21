#include<iostream>
#include<stdlib.h>		// required for malloc
using namespace std;

int main(){
	
	cout<<"\nMALLOC\n";
	//malloc is function
	
	int *iptr = (int*) malloc(sizeof(*iptr)) ;
	//malloc returns void* pointer which needs to be converted to int*
	
	*iptr = 32;
	cout<<iptr<<" "<<*iptr<<endl;
	
	int x = 3;
	iptr = &x;
	cout<<iptr<<" "<<*iptr<<endl;
	
	int n=5;
	int *iarrptr = (int*) malloc(n*sizeof(int));
	// declaring an array pointer using malloc
	while(--n)
		iarrptr[n] = n;
	for(int i=0; i<5; i++)
		cout<<iarrptr+i<<" "<<iarrptr[i]<<endl;
	
	
	cout<<"\nNEW\n";
	// new is an operator
		
	int *newptr1 = new int();	
	// new returns pointer according to specified data type 
	*newptr1 = 12;
	cout<<newptr1<<" "<<*newptr1<<endl;
	
	int *newptr2 = new int(13);
	// using new we can initialize the value at the pointer while declaring it
	cout<<newptr2<<" "<<*newptr2<<endl;
	
	int m = 5;
	int *newarrptr = new int[5];
	while(m--)
		newarrptr[m] = m*2;
	for(int i=0; i<5; i++)
		cout<<newarrptr+i<<" "<<newarrptr[i]<<endl;
	
	// We can also use new to specify which memory address to use
	int* xx = new int(3);
	cout<<*xx<<endl;
	int* yy = new(xx) int(4);
	cout<<*xx<<" "<<*yy<<endl;
	cout<< xx<<" "<<yy;
	
	return 0;
}