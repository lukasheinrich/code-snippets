#include <iostream>

/*
snippet shows how we can use function signatures as types to instantiate template. This came
up when I looked into the SEAL Reflex PluginService

*/

template<typename T>
struct factory_with_sig{
	T* member;
};



struct object{
	object(int i,double d){m_int = i;m_double = d;}
	static object* create(int i,double d){return new object(i,d);} //factory method
	int m_int;
	double m_double;
};



void func(int i,double d){
	std::cout << "hello there " << i << " and " << d << std::endl;
}

int main(){
	factory_with_sig<object* (int, double)> f;
	f.member = &object::create;


	object* o = f.member(2,3.14);
	
	std::cout << o->m_int << std::endl;
	std::cout << o->m_double << std::endl;
	return 0;
}