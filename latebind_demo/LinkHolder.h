#ifndef LINKHOLDER_H
#define LINKHOLDER_H

// The LinkHolder class just holds either ElementLinks or DataLinks

#include "ElementLink.h"
#include "DataLink.h"
#include <memory>

template<typename U, typename C>
struct LinkType;

template<typename U, typename C>
struct LinkType{ typedef ElementLink<C> type; };

template<typename C> struct LinkType<C,C>{ typedef DataLink<C> type; };

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
struct LinkHolder :
  public std::shared_ptr<typename LinkType<U,C>::type>,
  public LinkHolderBase {
  typedef typename LinkType<U,C>::type link_type;
  LinkHolder(link_type* p) : std::shared_ptr<link_type>(p){;}
};


#endif