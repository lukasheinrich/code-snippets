#include <iostream>
#include <vector>

template<typename... TUPLE> struct from_pack{
  template<typename T, int the_index = sizeof...(TUPLE)-1> struct locate {
    static const int value = std::is_same<T,typename std::tuple_element<the_index,std::tuple<TUPLE...> >::type>::value ? 
      the_index : locate<T,the_index-1>::value;
  };
  template<typename T> struct locate<T,0> {
  static const int value = std::is_same<T,typename std::tuple_element<0,std::tuple<TUPLE...> >::type>::value ? 
    0 : -1;
  };
};

template<bool first, bool... bools> 
struct all_true{ static const bool value = first && all_true<bools...>::value; };

template<bool first>  struct all_true<first>{ static const bool value = first; };


template<typename... TYPES> 
struct all_same{
  typedef typename std::tuple_element<0,std::tuple<TYPES...> >::type first_type;
  static const bool value = all_true<std::is_same<TYPES,first_type>::value...>::value;
};

//from http://stackoverflow.com/questions/7858817/unpacking-a-tuple-to-call-a-matching-function-pointer
template<int ...>
struct seq{};

template<int N, int ...S>
struct gens : gens<N-1, N-1, S...> { };

template<int ...S>
struct gens<0, S...> {
  typedef seq<S...> type;
};

template<typename... ARGS> struct constructible{
  constructible(ARGS... a) : args(a...){}
  
  typedef typename gens<sizeof...(ARGS)>::type indices;
  
  template<typename T, typename... TYPES> using init_possible = std::integral_constant<bool,
    std::is_constructible<T,std::initializer_list< typename std::tuple_element<0,std::tuple<TYPES...> >::type > >::value &&
      all_same<TYPES...>::value
      >;
    
  template<typename T, typename... TYPES> using ctor_possible = std::is_constructible<T,ARGS...>;
  template<typename T, typename... TYPES> using possible = std::integral_constant<bool,init_possible<T,TYPES...>::value || ctor_possible<T,TYPES...>::value>;

  template<typename T>
  typename std::enable_if<possible<T,ARGS...>::value>::type set_if(T& t, bool& did_set) const {
    did_set = true;
    now<T>(t,indices());
  }

  template<typename T>
  typename std::enable_if<!possible<T,ARGS...>::value>::type set_if(T& t,bool&) const {}

  template<typename T,int... indices>
  void now(T& t, seq<indices...>) const {
    t = T{std::get<indices>(args)...};
  };

  std::tuple<ARGS...> args;
};

template<typename T> struct identity {typedef T type;};

template<typename TUPLE> struct test_t;
template<typename... TYPES>
struct test_t<std::tuple<TYPES...> > : public std::tuple<TYPES...>{
  typedef std::tuple<TYPES...> tuple_type;
  template<typename... X>
  test_t(X... x) : m_index(-1){
    constructible<X...> ctohelper(x...);
    std::make_tuple(([&](){
      constexpr int idx = from_pack<TYPES...>::template locate<TYPES>::value;
      bool did_set = false;
      ctohelper.template set_if(std::get<idx>(*this),did_set);
      if(did_set) m_index = idx;
    }(),0)...);
  }
  int m_index;
};

template<typename TUPLE> struct combine;
template<typename... TYPES> struct combine<std::tuple<TYPES...> >{
  typedef std::tuple<TYPES...> tuple_type;
  static tuple_type doit(std::initializer_list<test_t<tuple_type> > list){
    tuple_type tuple;
    for(auto x : list){
      std::make_tuple(([&](){
        constexpr int idx = from_pack<TYPES...>::template locate<TYPES>::value;
        if(idx == x.m_index){
          std::get<idx>(tuple) = std::get<idx>(x);
        }
      }(),0)...);
    }
    return tuple;
  }
};

template<typename TUPLE>
struct nice{
  nice(std::initializer_list<test_t<TUPLE> > list):tuple(combine<TUPLE>::doit(list)){}
  TUPLE tuple;
};


struct typeA{};
struct typeB{};
struct typeC{};


template<typename T> using metric_t  = std::pair<std::function<void (double*,T*)>,double>;

void function_one(nice<std::tuple<metric_t<typeA>,metric_t<typeB>,metric_t<typeC> > > n){
  std::cout << "calling function" << std::endl;
  std::get<0>(n.tuple).first(0,0);
  std::cout << "cut0 " << std::get<0>(n.tuple).second << std::endl;
  std::get<2>(n.tuple).first(0,0);
  std::cout << "cut2 " << std::get<2>(n.tuple).second << std::endl;
}


void function_two(
  nice<std::tuple<std::initializer_list<typeA>,
                  std::initializer_list<typeB>,
                  std::initializer_list<typeC> > > n){
  std::cout << "calling function" << std::endl;

  std::cout << "size A: " << std::get<0>(n.tuple).size() << std::endl;
  std::cout << "size B: " << std::get<1>(n.tuple).size() << std::endl;
  std::cout << "size C: " << std::get<2>(n.tuple).size() << std::endl;


}



int main(){
  
  auto x = [](double*,typeA*)->void{
    std::cout << "calling with typeA" << std::endl;
  };
  auto y = [](double*,typeB*)->void{
    std::cout << "calling with typeB" << std::endl;
  };
  auto z = [](double*,typeC*)->void{
    std::cout << "calling with typeC" << std::endl;
  };

  typeA a1,a2;
  typeB b1,b2;
  typeC c1;
  
  std::cout << "__________________________________" << std::endl;
  function_one({{x,1.3},{z,3.141}});
  std::cout << "__________________________________" << std::endl;
  
  std::cout << "__________________________________" << std::endl;
  function_two({{a1,a2},{c1}});
  std::cout << "__________________________________" << std::endl;
}  