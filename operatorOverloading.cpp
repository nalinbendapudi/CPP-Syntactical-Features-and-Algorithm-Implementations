#include<iostream>

using namespace std;

struct Complex{
	double real, imag;
	
	Complex(double r, double i) : real(r), imag(i) {} // Using member initialization list
	
	Complex operator+(const Complex& other) const {
		return Complex(real+other.real,imag+other.imag);
	}
};

ostream& operator<<(ostream& stream, const Complex& c){
	stream <<c.real<<"+"<<c.imag<<"i"<<endl; 
}

int main(){
	
	Complex c1(1,2);
	Complex c2(20,30);
	Complex c3 = c1+c2;
	cout<<c3;
	
	return 0;
}