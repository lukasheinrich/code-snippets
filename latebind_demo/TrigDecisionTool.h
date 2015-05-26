#ifndef TRIGDECISIONTOOL_H
#define TRIGDECISIONTOOL_H
#include "Feature.h"
#include "EventStore.h"
#include "DummyFeatureStore.h"



#ifdef ATHENA
#include "EDM_Info.h"
#endif

template<typename T> struct strip_pointer;
template<typename T> struct strip_pointer<T*>{typedef T type;};
template<typename T> using ELEMENT_OF = typename strip_pointer<typename T::value_type>::type;


// This is a Dummy TDT implementation that just showcases
// the Feature access methods (actually from FeatureContainer)

struct EventStore;
struct TrigDecisionTool{
  
  TrigDecisionTool(EventStore* store):m_store(store){;}
  EventStore* m_store;

  #ifdef ATHENA
  template<typename FEATURE>
  std::vector<Feature<FEATURE> > get(){
    typedef typename Feature2Container<FEATURE>::type container_type;
    return newGet<FEATURE,FEATURE,container_type>();
  }
  #endif
  
  
  template<typename CONTAINER>
  std::vector<Feature<ELEMENT_OF<CONTAINER> > > elementFeature() const{
    return newGet<ELEMENT_OF<CONTAINER>,ELEMENT_OF<CONTAINER>,CONTAINER>();
  }
  
  template<typename CONTAINER>
  std::vector<Feature<CONTAINER> > containerFeature() const{
    return newGet<CONTAINER,CONTAINER,CONTAINER>();
  }
  
  template<typename CONTAINER>
  std::vector<Feature<ELEMENT_OF<CONTAINER> > > flattenedContainerFeature() const{
    return newGet<ELEMENT_OF<CONTAINER>,CONTAINER,CONTAINER>();
  }
   
private:
  template<typename REQUESTED,typename STORED, typename CONTAINER>
  std::vector<Feature<REQUESTED> > newGet() const;
  
};

template<typename REQUESTED, typename STORED, typename CONTAINER>
std::vector<Feature<REQUESTED> > TrigDecisionTool::newGet() const {
  auto result =  FeatureGetter<REQUESTED,STORED,CONTAINER>::getFeatures(m_store);
  return result;
}


#endif