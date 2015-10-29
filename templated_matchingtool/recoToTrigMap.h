#ifndef RECOTOTRIGMAP_H
#define RECOTOTRIGMAP_H
namespace Registry{
  template<typename T> struct typeMap;
  template<> struct typeMap<typeA>{typedef trigA type;};
  template<> struct typeMap<typeB>{typedef trigB type;};
  template<> struct typeMap<typeC>{typedef trigC type;};
};
#endif