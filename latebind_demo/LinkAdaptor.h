#ifndef LINKADAPTOR_H
#define LINKADAPTOR_H


#include "LinkHolder.h"

//forward declare Feature2Container meta-function in case header is not included
template<typename F>
struct Feature2Container;

#ifdef ATHENA
#include "EDM_Info.h"
#endif

// The LinkType helper meta function returns the link type
// If a type is given explicitly (this is the ASG case) as 
// its first argument this is just taken right away. 
// If the first arguemnt is 'dummytype' (ATHENA case)
// we resolve the linktype through the type map.

struct dummytype{};
template<typename ExplicitLink, typename T>
struct LinkType{
  // if explicit link type is given, run with it.
  typedef ExplicitLink type;
};

template<typename T>
struct LinkType<dummytype,T>{
  // if explicit link is dummytype, we can try to see if
  // EDM info is available
  typedef typename Feature2Container<T>::type container_type;
  typedef typename GetLinkType<T,container_type>::type type;
};


// The LinkAdaptor class basically deals with the Athena/ASG ambiguity
// in the Athena case we have the full EDM type information so we
// can deduce what the link type should be. While in the ASG case
// we use a trick to deduce it via a template parameter to the 
// function-style casting operator

template<typename U>
struct LinkAdaptor{
  LinkAdaptor(LinkHolderBase* const  link) : m_link(link){;}

  template<typename _> using latelink = typename LinkType<_,U>::type;

  template<typename T>
  T get(){
    typedef LinkHolder_with_Link<U,typename latelink<T>::container_type> feat_link;    
    auto myself  = dynamic_cast<feat_link*>(m_link);
    if(!myself){
      std::cout << "WARNING: Cast failed;" << std::endl;
    }
    T the_link = *(myself->getlink());
    return the_link;    
  }
  
  template<typename T>
  operator T(){
    return get<T>();
  }
  
  template<typename _ = dummytype>
  latelink<_> directget(){
    return get<latelink<_> >();
  }

  LinkHolderBase* const m_link;
};
#endif