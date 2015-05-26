#ifndef FEATURE_H
#define FEATURE_H

#include "LinkHolder.h"
#include "LinkAdaptor.h"


// This is a Feature Class that is usable in both ASG and Athena
// no matter whether the EDM type information is present or not
// if requested in can provide link, but does not force
// inclusion of additional headers, if not requested.

template<typename U>
struct Feature{
  Feature(const U* feature, LinkHolderBase* link = 0):m_feature(feature), m_link(link){;}

  virtual ~Feature(){}

  template<typename _> using latelink = typename LinkType<_,U>::type;

  template<typename _ = dummytype>
  #ifdef EDM_INFO_PRESENT
  latelink<_>link() const {
    return LinkAdaptor<U>(m_link).directget();
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