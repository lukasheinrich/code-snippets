#include <iostream>
#include <vector>
#include <tuple>


template<int i>
struct the_index{
  static const int value = i;
};

// template<typename TUPLE1, typename TUPLE2>
// struct typed_cat{
//   typedef decltype(std::tuple_cat(std::declval<TUPLE1>(),std::declval<TUPLE2>())) type;
// };


template<typename... TUPLES>
struct typed_cat{
  typedef decltype(std::tuple_cat(std::declval<TUPLES>()...)) type;
};

template<int max, int min = 0>
struct indexslice{
  typedef typename indexslice<max-1,min>::indices lower;
  static const lower ilower;
  static const std::tuple<the_index<max> >imax;
  typedef decltype(std::tuple_cat(ilower,imax)) indices;
};
template<int min>
struct indexslice<min,min>{
  typedef std::tuple<the_index<min> > indices;
};

template<typename TUPLE, typename INDEXTUPLE> struct pick_slice;
template<typename TUPLE, typename... TYPES> struct pick_slice<TUPLE,std::tuple<TYPES...> >{
  typedef std::tuple<typename std::tuple_element<TYPES::value,TUPLE>::type...> typeslice;
};

template<typename FIRST, typename SECOND>
struct combo{
  typedef std::tuple<std::tuple<FIRST,SECOND>,std::tuple<SECOND,FIRST> > combos;
};

template<int index, typename ELEMENT, typename TUPLE>
struct the_insert;

template<typename TUPLE, typename ELEMENT, int... insertions>
struct all_insertions{
  typedef std::tuple<the_insert<insertions,ELEMENT,TUPLE>...> type;
};

template<typename ELEMENT,typename TUPLE,int... indices> 
struct to_intpack{
  typedef all_insertions<TUPLE,ELEMENT,indices...> allin ;
};

template<typename ELEMENT,typename TUPLE,typename... TYPES> struct to_pack;
template<typename ELEMENT,typename TUPLE,typename... TYPES> struct to_pack<ELEMENT,TUPLE,std::tuple<TYPES...> >{
  typedef to_intpack<ELEMENT,TUPLE,TYPES::value...> intpack;
};

template<typename ELEMENT,typename TUPLE>
struct combinatorics{
  typedef typename to_pack<ELEMENT,TUPLE,typename indexslice<std::tuple_size<TUPLE>::value,0>::indices>::intpack intpack;
  typedef typename intpack::allin::type insertions;
};

//-------------

template<int index, typename ELEMENT, typename TUPLE, bool istop> struct top_inserter;
template<int index, typename ELEMENT, typename TUPLE> struct top_inserter<index,ELEMENT,TUPLE,true>{
  typedef TUPLE begin;
  typedef int end;
  typedef typename typed_cat<begin,std::tuple<ELEMENT> >::type type;
};
template<int index, typename ELEMENT, typename TUPLE> struct top_inserter<index,ELEMENT,TUPLE,false>{
  static const int maxsize = std::tuple_size<TUPLE>::value;
  typedef typename pick_slice<TUPLE,typename indexslice<index-1,0>::indices>::typeslice begin;
  typedef typename pick_slice<TUPLE,typename indexslice<maxsize-1,index>::indices>::typeslice end;
  typedef typename typed_cat<begin,std::tuple<ELEMENT> >::type begin_plus_element;
  typedef typename typed_cat<begin_plus_element,end>::type type;
};

//-------------

template<int index,typename ELEMENT, typename TUPLE>
struct the_insert{
  static const int maxsize = std::tuple_size<TUPLE>::value;
  typedef typename top_inserter<index,ELEMENT,TUPLE,index==maxsize>::begin begin;
  typedef typename top_inserter<index,ELEMENT,TUPLE,index==maxsize>::end end;
  typedef typename top_inserter<index,ELEMENT,TUPLE,index==maxsize>::type type;
};

template<typename ELEMENT, typename TUPLE>
struct the_insert<0,ELEMENT,TUPLE>{
  typedef int begin;
  typedef TUPLE end;
  typedef typename typed_cat<std::tuple<ELEMENT>,end>::type type;
};

//-------------

template<typename INSERTTUPLE> struct execute_insert;
template<typename... TYPES> struct execute_insert<std::tuple<TYPES...> >{
  typedef std::tuple<typename TYPES::type...> type;
};

//-------------

struct typeA{};
struct typeB{};
struct typeC{};
struct typeD{};
struct typeE{};
struct typeF{};
struct typeG{};
struct toInsert{};


//-------------

template<typename ELEMENT, typename COMBOTUPLE> struct execute_all_combos;
template<typename ELEMENT, typename... COMBOS> struct execute_all_combos<ELEMENT,std::tuple<COMBOS...> >{
  typedef typename typed_cat<typename execute_insert<typename combinatorics<ELEMENT,COMBOS>::insertions>::type...>::type combos;
};

template<typename FIRST, typename... REST>
struct allcombos{
  typedef typename allcombos<REST...>::type restcombos;
  typedef typename execute_all_combos<FIRST,restcombos>::combos type;
};

template<typename LAST>
struct allcombos<LAST>{
  typedef std::tuple<std::tuple<LAST> > type;
};

template<typename... TYPES> struct MULTIIFACE{
  virtual void hello(TYPES...) = 0;
};

template<typename T> struct TYPEDIFACE;

template<typename... TYPES> struct TYPEDIFACE<std::tuple<TYPES...> > : public MULTIIFACE<TYPES...>{
};

struct Useit {
  Useit(MULTIIFACE<typeB,typeC>& tool) : m_tool(tool) {
  }
  MULTIIFACE<typeB,typeC>& m_tool;
};


template<typename T> struct TYPEDIMPL;

template<typename... TYPES> struct TYPEDIMPL<std::tuple<TYPES...> > : public TYPEDIFACE<std::tuple<TYPES...> > {
 void hello(TYPES...){
   std::cout << "hello " << typeid(std::tuple<TYPES...>).name() << std::endl;
 }
};

template<typename COMBOTUPLE> struct IMPLEMENTATION;

template<typename... TYPES>
struct IMPLEMENTATION<std::tuple<TYPES...> > : public TYPEDIMPL<TYPES>... {
};

template<typename... TYPES>
struct MULTIIMP : public IMPLEMENTATION<typename allcombos<TYPES...>::type> {
};


int main(){
  // std::cout << "combos" << std::endl;
  typedef allcombos<typeA,typeB,typeC,typeD,typeE,typeF>::type threeway_combos;
  std::cout << std::tuple_size<threeway_combos>::value << std::endl;

  std::cout << typeid(allcombos<typeA,typeB>::type).name() << std::endl;
  std::cout << typeid(allcombos<typeA,typeB,typeC>::type).name() << std::endl;

  MULTIIMP<typeC,typeB> imp1;
  MULTIIMP<typeB,typeC> imp2;

  MULTIIFACE<typeC,typeB>& tbCB = imp1;
  tbCB.hello(typeC(),typeB());
  tbCB = imp2;
  tbCB.hello(typeC(),typeB());

  MULTIIFACE<typeB,typeC>& tbBC = imp1;
  tbBC.hello(typeB(),typeC());

  tbBC = imp2;
  tbBC.hello(typeB(),typeC());

  Useit bla(imp1);

  return 0;
}