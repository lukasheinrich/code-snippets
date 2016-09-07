#include "header.h"
#include <iostream>



namespace nameit{
  typedef what<int> wint;
  template<>
  int wint::static_method(){
    std::cout << "hello world" << std::endl;
    return 12345;
  }
  namespace{
    struct loader {
      loader(){
        std::cout << "calling static method" << std::endl;
        std::cout << "number is: " << wint::static_method() << std::endl;
      }
    };
    loader s_loader;
  }
}
