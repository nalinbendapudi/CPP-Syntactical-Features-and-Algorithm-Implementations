#include <iostream>
using namespace std;

class Shape{
	private:
		string name;
	public:
		float perimeter;
		float area;
		Shape(string s){
			name = s;
		}
		string getName(){
			return name;
		}
};

class Rectangle : public Shape{
	private:
		float length;
		float breadth;
	public:
		void setPerimeter(){
			perimeter = 2*(length+breadth);
		}
		void setArea(){
			area = length*breadth;
		}
		Rectangle(float l, float b, string n = "Rectangle") : Shape(n){
			length = l;
			breadth = b;
		}
};

class Square : private Shape{
	private:
		float side;
	public:
		void setPerimeter(){
			perimeter = 4*side;
		}
		void setArea(){
			area = side*side;
		}
		Square(float s,string n = "Square") : Shape(n){
			side = s;
		}
		string getName(){
			return Shape::getName();
		}
		float getPerimeter(){
			return perimeter;
		}
		float getArea(){
			return area;
		}
};

int main() {
	Rectangle r = Rectangle(3,5);
	r.setPerimeter();
	r.setArea();
	cout<<"name: "<<r.getName()<<endl;
	cout<<"perimater: "<<r.perimeter<<endl;
	cout<<"area: "<<r.area<<endl;
	
	Square s = Square(4);
	s.setPerimeter();
	s.setArea();
	cout<<"name: "<<s.getName()<<endl;
	cout<<"perimater: "<<s.getPerimeter()<<endl;
	cout<<"area: "<<s.getArea()<<endl;
	
	return 0;
}