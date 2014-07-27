/*

this explores the possibility to use SFINAE to create classes that have have an optional base class.
one problem here is to select code branches that operates on e.g. members of that optional base on the ground
of whether or not that base actually exists. 

several ways to statically check the existence of members are also shown
*/

#include <iostream>
#include <type_traits>

template<typename T> struct has_member{
	struct GuaranteedMember{int member;};
	struct Derived : T,GuaranteedMember{};
	template<typename X, X> struct TypeAndValue;	
	template<typename C> //if this instantiation works, it means no member is present
	constexpr static bool f(TypeAndValue<int GuaranteedMember::*,&C::member>*){return false;}
	template<typename C>
	constexpr static bool f(...){return true;}
	static const bool value = f<Derived>(0);
};

struct HasNoMember{
	void dummy();
};

struct MemberBase{
	MemberBase(){member = 3;}
	int member;
	void auxfunc(){
		member = 3;
		std::cout << member << std::endl;
	}
};

struct HasMember : MemberBase{
};

#define ONLYIFMEMBER(return_type,name,signature) \
template<typename C> \
typename std::enable_if<!has_member<C>::value,return_type>::type call_this(signature){;}\
template<typename C> \
typename std::enable_if<has_member<C>::value,return_type>::type call_this(signature)
 
template<typename T> struct CommonBase;
template<typename T>
struct CommonBase : T{
	typedef CommonBase<T> mytype;
	ONLYIFMEMBER(void,call_this,int i = 3){
		std::cout << "setting the member yo: " << i << std::endl;
		this->member = 3;
	}

	void commonFunc(){
		int context = 2;
		std::cout << "am I inheriting a member? " << (has_member<T>::value ? "yes":"no") << std::endl;
		std::cout << "context is: " << context << std::endl;
		call_this<mytype>();
	}
};


int main(){
	CommonBase<HasMember> c1;
	c1.commonFunc();

	CommonBase<HasNoMember> c2;
	c2.commonFunc();
}