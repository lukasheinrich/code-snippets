#include "interface.h"
#include "factory.h"

#include <dlfcn.h>

//as we can see we are only including the interface and the factory headers
//we don't need to include any headers for the concrete implementation
//it is enough that those are linked against by the compiler
//this is the main advantage we wanted to demonstrate!

//I also liked to write-ups and code found here
//http://mass-communicating.com/code/2013/05/01/generic_factories_cpp.html
//https://gist.github.com/pkrusche/5501253

//now this only is a factory for a given interface that has a given ctor signature
//what would now be the next step would be to have a manager for arbitrary signatures

int main(){
	dlopen("./libimpl1.so", RTLD_NOW);
	dlopen("./libimpl2.so", RTLD_NOW);
	auto m = interfacefactory<interface>::instance();
	for(auto i : {"impl1","impl2","impl3"}){
		auto impl = m.create(i);
		if(impl) impl->execute();		
	}
	return 0;
}