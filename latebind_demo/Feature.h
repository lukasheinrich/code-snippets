#ifndef FEATURE_H
#define FEATURE_H

#include "LinkHolder.h"
#include "LinkAdaptor.h"

// The LinkType helper meta function returns the link type
// If a type is given explicitly (this is the ASG case) as 
// its first argument this is just taken right away. 
// If the first arguemnt is 'dummytype' (ATHENA case)
// we resolve the linktype through the type map.

//forward declare Feature2Container meta-function in case header is not included
template<typename F>
struct Feature2Container;

#ifdef ATHENA
#include "EDM_Info.h"
#endif

template<typename ExplicitLink, typename T>
struct LinkType{
  // if explicit link type is given, run with it.
  typedef ExplicitLink type;
};

template<typename T>
struct LinkType<struct _,T>{
  // if explicit link is dummytype, we can try to see if
  // EDM info is available
  typedef typename Feature2Container<T>::type container_type;
  typedef typename GetLinkType<T,container_type>::type type;
};

// This is a Feature Class that is usable in both ASG and Athena
// no matter whether the EDM type information is present or not
// if requested in can provide link, but does not force
// inclusion of additional headers, if not requested.

template<typename U>
struct Feature{
  Feature(const U* feature, LinkHolderBase* link = 0):m_feature(feature), m_link(link){;}

  virtual ~Feature(){}

  template<typename _> using latelink = typename LinkType<_,U>::type;

  template<typename _ = struct _>
  #ifdef EDM_INFO_PRESENT
  latelink<_> link() const {
    return LinkAdaptor<U>(m_link).template get<latelink<_> >();
  #else
  LinkAdaptor<U> link() const {
    return LinkAdaptor<U>(m_link);
  #endif
  }

  const U* operator->() const {return m_feature;}
  
  LinkHolderBase* const m_link;
  
  const U* m_feature;
};

#endif