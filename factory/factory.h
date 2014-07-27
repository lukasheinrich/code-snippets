#ifndef factory_h
#define factory_h
#include <string>
#include <map>
#include <iostream>


//this class is the interface that all factories for concrete implementations need to adhere to
template<typename INTERFACE>
struct ifactory{
	virtual INTERFACE* create() = 0; //signature of ctor determines this
};

//concrete factories can just be built from this template
template<typename IMPL,typename INTERFACE>
struct factory : public ifactory<INTERFACE> {
	virtual INTERFACE* create(){//signature of ctor determines this
		return new IMPL();
	};
};

//this is the singleton class that manages all implementations for a given interface.
//it holds a map: string->concrete factory as ifactory
//to which we can add and retrieve.
template<typename INTERFACE>
struct interfacefactory{
	static interfacefactory& instance(){
		static interfacefactory<INTERFACE> instance;
		return instance;
	}
	void add(const std::string& impl,ifactory<INTERFACE>* fac){implmap[impl] = fac;}
	INTERFACE* create(const std::string& impl){//signature of ctor determines this
		auto i = implmap.find(impl);
		if(i!=implmap.end()){return implmap[impl]->create();}
		std::cout << "implementation " << impl << " not found" << std::endl;
		return 0;
	}
private:
	std::map<std::string,ifactory<INTERFACE>* > implmap;
};

//this is the usual ctor as lib-loading time run execution trick. we use it to register a implementation with the 
//implementation manager
template<typename IMPL,typename INTERFACE>
struct register_impl{
	register_impl(const std::string impl){
		interfacefactory<INTERFACE>::instance().add(impl,new factory<IMPL,INTERFACE>);
	}
};

//just a helper macro to make registering impl easier. 
#define reg(impl,interface) static register_impl<impl,interface> s_reg_##impl(#impl)

#endif