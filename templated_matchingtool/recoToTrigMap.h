#ifndef RECOTOTRIGMAP_H
#define RECOTOTRIGMAP_H
namespace Registry{
  template<typename T> struct typeMap;
  template<> struct typeMap<typeA>{
    typedef trigA type;
    static std::string label(){return "defaultLabelA";};
  };
  template<> struct typeMap<typeB>{
    typedef trigB type;
    static std::string label(){return "defaultLabelB";};
  };
  template<> struct typeMap<typeC>{
    typedef trigC type;
    static std::string label(){return "defaultLabelC";};
  };
};
#endif