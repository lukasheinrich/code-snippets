#ifndef LINKADAPTOR_H
#define LINKADAPTOR_H

#include "LinkHolder.h"

// The LinkAdaptor class basically deals with the Athena/ASG ambiguity
// in the Athena case we have the full EDM type information so we
// can deduce what the link type should be. While in the ASG case
// we use a trick to deduce it via a template parameter to the 
// function-style casting operator

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