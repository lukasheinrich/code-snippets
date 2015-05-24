#include <iostream>

template<typename T>
struct Default;

// template<typename T>
// struct Default{
//   typedef double type;
// };

template<typename dummy, typename T>
struct latebind{
  typedef typename Default<T>::type type;
};

struct dummytype{};

template<typename U>
struct feature{

  template<typename dummy = dummytype>
  typename latebind<dummy,U>::type hello(){
    std::cout << "hello with dummy" << std::endl;
    return 2.3;
  }

  void say(){
    std::cout << "we don't now what Default<U> is" << std::endl;
  }
  
};

struct FeatureType{};

int main(){
  feature<FeatureType> f;
  f.say();
  
  // f.hello();
}