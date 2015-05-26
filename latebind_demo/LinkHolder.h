#ifndef LINKHOLDER_H
#define LINKHOLDER_H

// The LinkHolder_with_link class just holds either ElementLinks or DataLinks

#include "ElementLink.h"
#include "DataLink.h"

template<typename U, typename C>
struct GetLinkType;

template<typename U, typename C>
struct GetLinkType{
  typedef ElementLink<C> type;
};

template<typename C>
struct GetLinkType<C,C>{
  typedef DataLink<C> type;
};

// LinkHolderBase is just a type agnostic
// base class for LinkHolder_with_Link
// so we can treat ElementLinks/DataLinks
// uniformly. Maybe we can use Boost.Any here?

struct LinkHolderBase{
  virtual ~LinkHolderBase(){}
};

// simple class to hold a ptr to 
// an element link or data link
template<typename U,typename C>
struct LinkHolder_with_Link : public LinkHolderBase{
  typedef typename GetLinkType<U,C>::type link_type;

  LinkHolder_with_Link(link_type* link) : m_link(link) {;}

  link_type* getlink(){
    return m_link;
  }

  link_type* m_link;
};


#endif