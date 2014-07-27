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