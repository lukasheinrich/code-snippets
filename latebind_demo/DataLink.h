#ifndef DATALINK_H
#define DATALINK_H

// dummy DataLink implementation

template<typename Container>
struct DataLink{
  typedef Container container_type;

  DataLink(const Container& c):m_data(c){;}

  const Container* operator->(){
    return &m_data;
  }

  void say_something(){
    std::cout << "hello I'm an data link" << std::endl;
  }
  
  const Container& m_data;
};

#endif