#include "interface.h"
#include "factory.h"

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
	auto m = interfacefactory<interface>::instance();
	interface* i1 = m.create("impl1");
	if(i1) i1->execute();

	interface* i2 = m.create("impl2");
	if(i2) i2->execute();

	interface* i3 = m.create("impl3");
	if(i3) i3->execute();


	return 0;
}