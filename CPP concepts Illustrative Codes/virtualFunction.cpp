// CPP program to illustrate 
// concept of Virtual Functions 

#include <iostream> 
using namespace std; 

class base { 
public:
	string Name = "base";
	virtual void print(){ 
		cout << "print base class" << endl; 
	} 
	void show(){ 
		cout << "show base class" << endl; 
	}
	virtual void display(){
		cout<< "display base class" <<endl;
	}
}; 

class derived : public base { 
public: 
	derived(){Name = "derived";}
	void print() {								// override keyword is optional. We can also write " void print() override{ "
												// override keyword is added in c++11 for readablity 
		cout << "print derived class" << endl; 
	} 
	void show(){ 
		cout << "show derived class" << endl; 
	} 
}; 

int main() 
{ 
	base b;
	cout<<"b: "<<endl;
	b.print();
	b.show();
	b.display();

	base* bptr = new base; 
	cout<<"bptr: "<<endl;
	bptr->print(); 
  	bptr->show();
  	bptr->display();
  	
  	derived d;
	cout<<"d: "<<endl;
	cout<<d.Name<<endl;
  	d.print(); 
  	d.show();
	d.display(); 
	
	derived* dptr = new derived;
	cout<<"dptr: "<<endl;
	dptr->print();
  	dptr->show();
	dptr->display(); 
	
	bptr = &d;
	cout<<"bptr = &d : "<<endl;
	cout<<bptr->Name<<endl;
	bptr->print();     	// Virtual function: binded at run-time
	bptr->show();		// Non-virtual function: binded at compile-time 
	bptr->display();  	// Virtual function but not over-ridden in derived class
	
	b = d;
	cout<<"b=d :"<<endl;
	cout<<b.Name<<endl;
	b.print();
	b.show();
	b.display();
	
	
} 
