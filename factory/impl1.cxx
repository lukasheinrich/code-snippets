#include "interface.h"
#include "factory.h"
#include <iostream>

//one imlpementation
struct impl1 : public interface{
	virtual ~impl1(){
	}
	virtual void execute(){
		std::cout << "hello from impl1" << std::endl;
	}
};
//register it!
reg(impl1,interface);


//another implementation	
struct impl2 : public interface{
	virtual ~impl2(){
	}
	virtual void execute(){
		std::cout << "hello from impl2" << std::endl;
	}
};
//register it too!
reg(impl2,interface);