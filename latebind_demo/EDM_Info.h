#ifndef EDMTYPEINFO_H
#define EDMTYPEINFO_H

// This is a dummy version of the Athena TypeMap code

// EDM_TypeInfo full header
struct ElementType;
struct ContainerType;


template<typename T>
struct Feature2Container;


template<>
struct Feature2Container<ElementType>{
  typedef ContainerType type;
};

template<>
struct Feature2Container<ContainerType>{
  typedef ContainerType type;
};

#define EDM_INFO_PRESENT ;

#endif