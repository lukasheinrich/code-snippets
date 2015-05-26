#include <iostream>

#include "TrigDecisionTool.h"
#include "ContainerType.h"
#include "ElementType.h"
#include "EventStore.h"
#include "ElementLink.h"
#include "DataLink.h"

template<typename T>
void testElementFeature(const std::vector<Feature<T> >& featvec){
  std::cout << "::testing element feature" << std::endl;
  for(auto& feat : featvec){
    std::cout << "::::testing direct pointer access" << std::endl;
    feat->say_hello();

    std::cout << "::::testing cast-style link (ASG)" << std::endl;
    ElementLink<ContainerType> a_link = feat.link();
    a_link.say_something();
    a_link->say_hello();


    #ifdef ATHENA
    std::cout << "::::testing direct link with chain support (Athena)" << std::endl;
    feat.link().say_something();
    feat.link()->say_hello();
    #endif
  }
}

template<typename T>
void testContainerFeature(const std::vector<Feature<T> >& featvec){
  std::cout << "::testing container feature" << std::endl;
  for(auto& feat : featvec){
    std::cout << "::::testing direct pointer access" << std::endl;
    auto cont = feat.operator->();
    cont->say_hello();
    for(auto& element : *cont){
      element->say_hello();
    }
    
    std::cout << "::::testing cast-style link (ASG)" << std::endl;
    DataLink<ContainerType> a_link = feat.link();
    a_link.say_something();
    a_link->say_hello();
    
    #ifdef ATHENA
    std::cout << "::::testing direct link with chain support (Athena)" << std::endl;
    feat.link().say_something();
    feat.link()->say_hello();
    #endif
  }
}

int main(){
  EventStore evtStore;
  
  TrigDecisionTool tdt(&evtStore);
  
  std::cout << ":ELEMENT FEATURE TEST " << std::endl;
  testElementFeature(tdt.elementFeature<ContainerType>());
  std::cout << ":FLATTENED CONTAINER FEATURE TEST " << std::endl;
  testElementFeature(tdt.flattenedContainerFeature<ContainerType>());
  std::cout << ":CONTAINER FEATURE TEST " << std::endl;
  testContainerFeature(tdt.containerFeature<ContainerType>());
}