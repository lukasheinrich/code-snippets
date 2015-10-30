#ifndef MAPOVERRIDE_H
#define MAPOVERRIDE_H

#include "recoToTrigMap.h"

template<template <typename> class MAP, typename T>
struct map_supports{
  typedef char yes; typedef char no[2];
  template<typename C> static  yes& test(typename MAP<C>::type*);
  template<typename C> static no&  test(...); 
  static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
};

template <template<typename> class MAPONE,template<typename> class MAPTWO> struct map_override{
  template<typename T>
  static typename std::enable_if<map_supports<MAPONE,T>::value,MAPONE<T> >::type test();
  template<typename T>
  static typename std::enable_if<!map_supports<MAPONE,T>::value && map_supports<MAPTWO,T>::value,MAPTWO<T> >::type test();
  template<typename T> struct map{
    typedef decltype(test<T>()) mapper;
    typedef typename mapper::type type;
    static std::string label(){return mapper::label();}
  };
};

template<template <typename> class OVERRIDE>
map_override<OVERRIDE,Registry::typeMap> make_override(){return map_override<OVERRIDE,Registry::typeMap>();}

#endif