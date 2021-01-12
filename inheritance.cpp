class Base{
	public:
		int n=3;
	private:
		int m=5;
};

class Derived: public Base{
	private:
		int p=6;
	public:
		int q=n;
		//int q2 = m; // m (private of Parent is not accessible here at all)
		int r=p;
};


class Derived2: private Base{
	private:
		int p=6;
	public:
		int q=n;
		//int q2 = m; // m (private of Parent is not accessible here at all)
		int r=p;
};

#include <iostream>
using namespace std;

int main() {
	Base b;
	//cout<<b.n<<endl;
	
	Derived d;
	cout<<d.q<<endl;
	cout<<d.r<<endl;
	cout<<d.n<<endl;   // n is public in Parent and publicly inherited
	//cout<<d.m<<endl; // m (private of Parent is not accessible here at all)
	
	Derived2 d2;
	cout<<d2.q<<endl;
	cout<<d2.r<<endl;
	//cout<<d2.n<<endl; // n is public in Parent but privately inherited
	
	return 0;
}