#ifndef CONTAINERTYPE_H
#define CONTAINERTYPE_H

//This header is just some ContainerType, a la xAOD::TrigElectronContainer

#include "DataVector.h"
#include "ElementType.h"

struct ContainerType : public DataVector<ElementType>{
  void say_hello() const{
    std::cout << "hello i'm a container" << std::endl; 
  }
};
#endif