#ifndef LINKADAPTOR_H
#define LINKADAPTOR_H

#include "LinkHolder.h"

// The LinkAdaptor class basically just holds the typeless link
// pointer. some way or another it will get a call to get<T>
// where T will be the link type. i.e. DataLink<Container>
// or ElementLink<Container> with this we can cast down to
// LinkHolder<U,ContainerType> and get the link.

template<typename U>
struct LinkAdaptor{
  LinkAdaptor(LinkHolderBase* const link) : m_link(link){;}

  template<typename T>
  T get(){
    typedef LinkHolder<U,typename T::container_type> feat_link;    
    auto myself  = dynamic_cast<feat_link*>(m_link);
    if(!myself){
      std::cout << "WARNING: Cast failed;" << std::endl;
    }
    return *(myself->get());
  }
  template<typename T>
  operator T() {
    return get<T>();
  }
  LinkHolderBase* const m_link;
};
#endif