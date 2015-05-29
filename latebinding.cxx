#include <iostream>
//forward declare the map (no definition!)
template<typename T>
struct TypeMap;

//the late resolution mechanism
template<typename T,typename _>
struct lateresolve{
  typedef typename TypeMap<T>::type type;
};

template<typename U>
struct feature{
  template<typename _> using return_type = typename lateresolve<U,_>::type;
  template<typename _ = struct _>
  return_type<_> hello(){
    std::cout << "resolved type!" << std::endl;
    return return_type<_>();
  }
};

struct FeatureType{};
// struct ContainerType;
// template<typename T>
// struct TypeMap{
//   typedef ContainerType type;
// };
// struct ContainerType{ void say(){std::cout<<"container!"<<std::endl;}};

int main(){
  feature<FeatureType> f;
  // f.hello().say();
}