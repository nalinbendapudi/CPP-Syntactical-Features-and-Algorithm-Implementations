#include<iostream>
using namespace std;

template<class myType>   // myType is a generic datatype
class myClass{
	myType values [2];
public:
	myClass(myType firstValue, myType secondValue){	// constructor for myClass
		values[0] = firstValue;
		values[1] = secondValue;
	}
	
	myType maxValue(){
		myType max = values[0]>values[1] ? values[0] : values[1];
		return max;
	}
	
	bool compareWithFirst(myType arg);
	
};

template<class myType>
bool myClass<myType> :: compareWithFirst(myType arg){
	if(arg == values[0])
		return true;
	else
		return false;
}

int main(){
	
	myClass<int> myObject(3,5);
	int max = myObject.maxValue();
	cout<<max<<endl;
	bool isEqualWithFirst = myObject.compareWithFirst(3);
	cout<<isEqualWithFirst<<endl;
	
	return 0;
}
