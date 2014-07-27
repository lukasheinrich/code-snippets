#include <iostream>

/*
snippet shows how we can use function signatures as types to instantiate template. This came
up when I looked into the SEAL Reflex PluginService

*/

//this just declares the class
template<typename T>
struct factory;

//now we specialice so we get access to the ctor types
template<typename R>
struct factory<R (void)>{
	R (*member)(void);
};

template<typename R,typename A1>
struct factory<R (A1)>{
	R (*member)(void);
};

template<typename T> struct pointer2type;
template<typename T> struct pointer2type<T*>{typedef T type;};

template<typename R,typename A1, typename A2>
struct factory<R (A1,A2)>{
	R (*member)(A1,A2);
	static R Func(A1 a1,A2 a2){return new typename pointer2type<R>::type(a1,a2);}
};

struct object{
	object(int i,double d){m_int = i;m_double = d;}
	int m_int;
	double m_double;
};


int main(){
	factory<object* (int, double)> f;

	f.member = &factory<object* (int, double)>::Func;

	object* o = f.Func(2,3.14);
	
	std::cout << o->m_int << std::endl;
	std::cout << o->m_double << std::endl;
	return 0;
}