// A singleton class is a class which has only one object
// An example of such a class is the random number generator class


#include<iostream>

using namespace std;

class Singleton{
public:
	Singleton (const Singleton&) = delete;	// We delete the copy constructor so that no one can make objects
											// by copying the instance generated by the Get function
	
	static Singleton& Get(){	// This returns a reference to the only object
		return s_Instance;
	}
	
	float Function(){	// some member function
		return m_Member;	// (for a random number generator class, this could be a random gernerator function)
	}	
	
private:
	Singleton(){}	// We keep the constructor in private so that it's inaccessible 
					// and no one can declare more objects
	
	float m_Member = 0.0f;	// some member value 
							// (for a random number generator class, this could be a seed value)
	
	static Singleton s_Instance;	// This is the only object of this function
};

Singleton Singleton::s_Instance;

int main(){
	
	float f = Singleton::Get().Function();	// This is the only way to access this class
	cout<<f<<endl;
	
	// Singleton s; // This is invalid since constructor is private
	
	// Singleton s = Singleton::Get();	// This is invalid since copy constructor is deleted
	
	Singleton& s = Singleton::Get(); 	// This is allowed since we are just creating another reference
	cout<<s.Function()<<endl;
	
	return 0;
}