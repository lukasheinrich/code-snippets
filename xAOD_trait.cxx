#include <vector>
#include <iostream>
#include <memory>

//
// just a small snippet to check if a type is xAOD
//

namespace SG{struct AuxElement;struct AuxContainerBase;}

template<typename T> struct strip_ptr{typedef T type;};
template<typename T> struct strip_ptr<T*>{typedef T type;};

namespace xAOD{
	template<typename T>
	struct isxAOD{
		template<typename C>
		constexpr static typename std::enable_if<std::is_base_of<SG::AuxElement,typename strip_ptr<typename C::value_type>::type>::value,bool>::type isxAODVector(C*){return true;}
		template<typename C>
		constexpr static bool isxAODVector(...){return false;}
		template<typename C>
		constexpr static typename std::enable_if<std::is_base_of<SG::AuxContainerBase,C>::value,bool>::type isAuxVector(C*){return true;}
		template<typename C>
		constexpr static bool isAuxVector(...){return false;}
		static const bool value = isxAODVector<T>(0) || isAuxVector<T>(0);
	};
}

template<typename T>
struct TrigSerializeConverter{
	static const bool isxAOD = xAOD::isxAOD<T>::value;
	TrigSerializeConverter(){
		std::cout << "constructing a converter for " << typeid(T).name() << ". is it xAOD? " << (isxAOD ? "yes" : "no") << std::endl;
	}

};

//test types, the check should work for all kinds of inheritance cases
namespace SG{struct AuxElement{}; struct AuxContainerBase{};}
struct element : public SG::AuxElement{};
typedef std::vector<element*> xAODContainer;
struct fancyvec : public std::vector<element*>{};
typedef std::vector<double> noxAODContainer;
struct xAODAux : public SG::AuxContainerBase{};
struct anotherAux : public SG::AuxContainerBase{};
struct nonAux{};

int main(){
	TrigSerializeConverter<xAODContainer> t1;	//yes
	TrigSerializeConverter<fancyvec> t2;	    //yes
	TrigSerializeConverter<noxAODContainer> t3;	//no

	TrigSerializeConverter<xAODAux> t4;         //yes
	TrigSerializeConverter<anotherAux> t5;      //yes
	TrigSerializeConverter<nonAux> t6;          //no
}