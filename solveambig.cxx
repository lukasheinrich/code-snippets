#include <iostream>

//solving ambiguity in multiple inheritance with 'using'

class base1{
public:
	void say(){
		std::cout << "base1" << std::endl;
	}
};

class base2{
public:
	void say(){
		std::cout << "base2" << std::endl;
	}
};

class derived : public base1,public base2{
public:
	using base2::say;
	void doit(){
		std::cout << "doing it" << std::endl;
		say();
	}
	
};



int main(){

	derived d;
	d.doit();

	return 0;
}