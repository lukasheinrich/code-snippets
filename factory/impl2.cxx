#include "interface.h"
#include "factory.h"
#include <iostream>

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