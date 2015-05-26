#ifndef EVENTSTORE_H
#define EVENTSTORE_H

// dummy StoreGate implementation

#include "ContainerType.h"
#include "ElementType.h"
struct EventStore{
  EventStore(){
    m_container.push_back(new ElementType("The first Feature"));
    m_container.push_back(new ElementType("The second Feature"));
  }
  ContainerType* getContainer(){
    return &m_container;
  }
  
  ContainerType m_container;

};
#endif