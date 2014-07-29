#include <iostream>
struct Parent{
	Parent(int i){std::cout << "int" << std::endl;;}
	Parent(const char* c){std::cout << "const char" << std::endl;}
	Parent(double d){std::cout << "double" << std::endl;}
};

struct Derived : public Parent{
	using Parent::Parent;
	Derived(int i):Parent(i){
		std::cout << "my own int" << std::endl;
	}
};

int main(){
	Derived d1(2);
	Derived d2("hello");
	Derived d3(2.3);
	return 0;
}