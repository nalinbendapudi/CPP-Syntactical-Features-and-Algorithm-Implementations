#include <iostream>
using namespace std;

int main() {
	int x = 10;
	
	cout<<"\nREFERENCES\n";
	// & operator is used for two things:
	// 1. To declare a reference variable
	// 2. To reference (i.e. getting the address where a variable is stored)
	
	int &c = x;      // c is just a reference to x
	cout<<c<<endl;   // c has the same value as x
	cout<<&c<<endl;  // address of c is same as address of x
	x++;
	cout<<c<<endl;		 // c changes with x
	
	//int &d = &x;   // &x is an address and need to be stored in a pointer variable. 
					 // &d is not a pointer variable.
	
	int &j = x;		// We can create multiple references to the same variable
	
	// int &g;  	// Invalid. Uninitialized reference can't be declared
	
	
	cout<<"\nPOINTERS\n";
	// * operator is used for two things:
	// 1. To declare a pointer variable
	// 2. To de-reference (i.e. getting the value stored at an address pointer)
	
	//int a = &x;      // invalid.Address can't be stored in normal variable
	
	int *b = &x;       // valid. address of x stored in pointer variable b
	cout<<b<<endl;     // outputs address of x
	cout<<*b<<endl;    // outputs value of x
	//cout<<*x<<endl;  // x is a not a pointer. Hence can't be dereferenced
	
	int e = *b;		 // e is initialized to value as that stored at b
	x++;			 // but e doesn't change with x
	cout<<*b<<" "<<e<<endl; 
	*b = *b+1;
	cout<<*b<<" "<<e<<endl; 
	
	int *i = b;		// We can create multiple pointers to the same address
	
	int *f;			//	A pointer can be declared but not initialized
	
	// Incrementing pointers
	cout<<"\nIncrementing pointers\n";
	
	int* h = &x;	// pointer can be declared by int* h or int *h
	*h = *h+1;      // increments value of variable stored at h
	cout<<h<<" "<<x<<endl;
	(*h)++;         // increments value of variable stored at h
	cout<<h<<" "<<x<<endl;
	
	++*h;			// this also increments value stored at h
					// pre-increment and *, both have same precedence and expression is evaluated right to left
	cout<<h<<" "<<x<<endl;
	
	*++h;			// this increments the pointer to the next address
					//Both have same precedence but this time increment is done first since expression is evaluated from right to left
	cout<<h<<" "<<x<<endl;
	cout<<*h<<endl; // there is some random value at the new address now
	
	int *k = &x;
	*k++;			// this increments the pointer to the next address
					// post-increment has higher precedence than *
	cout<<k<<" "<<x<<endl;
	cout<<*k<<endl; // there is some random value at the new address now
	
	int *p = &x;
	p++;			//	p++ is same as *p++
	cout<<p<<" "<<*p<<endl;
	
	// Pointers in Arrays
	cout<<"\nPointers in Arrays\n";
	
	int arr[] = {1,10,100,1000};
	cout<<arr<<" "<<&arr[0]<<endl;  // array name is the address of the zeroth element of the array
	cout<<*arr<<" "<<arr[0]<<endl;
	cout<<*(arr+2)<<" "<<arr[2]<<endl;
	cout<<*arr+2<<endl;
	
	cout<<sizeof(arr)<<endl;	//no of elements in array X size of single element
	int *ptr = arr;
	cout<<sizeof(ptr)<<endl;   // size of pointer to the zeroth element. 
							   // Addresses are usually stored in 8 bytes
	// Note: when arr is passed as an argument to a function, actually just the pointer to the 
	// 0th element is passed. Hence if you do sizeof(arr) inside a function, you'll get 8 bytes
	
	cout<<"\nPointers and Constants\n";
	//Pointers and Constants
	const int y = 10;
	int *q = &x;
	//int *r = &y; // Invalid. const int address needs to be stored in const int* variable
	const int *r = &y;
	
	++*q;		 // increments value of x
	cout<<q<<" "<<*q<<endl;
	// ++*r;	 // can't increment y as it is const
	
	*q++;		// increments q
	cout<<q<<" "<<*q<<endl;
	*r++;		// increments r to next address 
				// This can be done as r is not a const variable. It's just a pointer to a const variable
	cout<<r<<" "<<*r<<endl;
	
	int* const s = &x;  // This is a const pointer
	++*s;			    // The value at s is not constant. Hence that can be incremented
	//*s++;			    // This is not allowed as pointer is const		
	
	
	
	return 0;
}