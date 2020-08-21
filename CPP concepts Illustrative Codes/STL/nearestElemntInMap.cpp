#include <iostream>
#include <map>
using namespace std;

// Function takes 2 arguments: a map<T1,T2> m , and a value d of type T1. (T1 should be a numeric type with comparator '<' pre-defined)
// Function returns value (type T2) of the map element whose key is nearest/closest to d
template <typename T1, typename T2>
T2 nearestInMap (map<T1,T2> m, T1 d){
	auto i = m.upper_bound(d);
	auto j=i;
	i--;
	if (j==m.end())
		return i->second;
	if (j==m.begin())
		return j->second;
	return (j->first - d) < (d - i->first) ? j->second : i->second;
}

 
int main() {
 
	map <double,int> m;
	m.insert({23.1,0});
	m.insert({12.2,1});
	m.insert({56.2,2});
	m.insert({45.3,3});
	m.insert({37.4,4});
	m.insert({26.3,5});
 
	cout<< nearestInMap(m,11.0) <<endl;
	cout<< nearestInMap(m,22.0) <<endl;
	cout<< nearestInMap(m,24.3) <<endl;
	cout<< nearestInMap(m,32.2) <<endl;
	cout<< nearestInMap(m,42.1) <<endl;
	cout<< nearestInMap(m,52.1) <<endl;
	cout<< nearestInMap(m,62.7) <<endl;
 
	return 0;
}