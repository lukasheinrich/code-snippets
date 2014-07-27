#include <iostream>

/*
snippet shows how we can use function signatures as types to instantiate template. This came
up when I looked into the SEAL Reflex PluginService

*/

template<typename T> struct pointer2type;
template<typename T> struct pointer2type<T*>{typedef T type;};


//this just declares the class
template<typename SIG> struct IFactory;
//this just declares the class
template<typename SIG,typename IMPL> struct Factory;

//now we specialice so we get access to the ctor types
template<typename R>
struct IFactory<R (void)>{virtual R create() = 0;};
template<typename R,typename IMPL>
struct Factory<R (void),IMPL> : public IFactory<R (void)>{
	virtual R create(void){return new IMPL();}
};

template<typename R,typename A1>
struct IFactory<R (A1)>{virtual R create(A1) = 0;};
template<typename R,typename A1,typename IMPL>
struct Factory<R (A1),IMPL> : public IFactory<R (A1)>{
	virtual R create(A1 a1){return new IMPL(a1);}
};

template<typename R,typename A1, typename A2>
struct IFactory<R (A1,A2)>{virtual R create(A1,A2) = 0;};
template<typename R,typename A1, typename A2,typename IMPL>
struct Factory<R (A1,A2),IMPL> : public IFactory<R (A1,A2)>{
	virtual R create(A1 a1,A2 a2){return new IMPL(a1,a2);}
};

struct interface{
	virtual void execute() = 0;
};

struct object : public interface {
	object(int i,double d){m_int = i;m_double = d;}
	virtual void execute(){
		std::cout << this->m_int << std::endl;
		std::cout << this->m_double << std::endl;		
	}
	int m_int;
	double m_double;
};

struct object2 : public interface {
	object2(){}
	virtual void execute(){
		std::cout << "no args" << std::endl;	
	}
};



int main(){
	IFactory<interface* (int,double)>* f1 = new Factory<interface* (int,double),object>();
	IFactory<interface* (void)>* f2 = new Factory<interface* (void),object2>();

	interface* o1 = f1->create(2,3.14);
	o1->execute();
	interface* o2 = f2->create();
	o2->execute();


	return 0;
}