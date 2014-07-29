/*
	just a small demonstration of the new C++ feature of automatically inheriting all ctors
	from a base class. The use case is that if Base has many ctors whose signature you want
	to duplicate in the derived class (and just let that use the base ctor) you can just use
	the declaration using Base::Base
	compile using: g++ -o inheritctor inheritctor.cxx --std=c++11
	expected output is:
	>int
	>my own int 
	>const char
	>double
	
	if you want to override one of the signatures (e.g. do some additional stuff in the derived initialization)
	you can just define such a ctor and the overloading will select the derived ctor first. (here: the int ctor)
*/


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