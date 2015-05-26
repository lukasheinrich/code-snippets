#ifndef ELEMENTLINK_H
#define ELEMENTLINK_H

// dummy ElementLink implementation

template<typename Container>
struct ElementLink{
  typedef Container container_type;
  typedef typename Container::size_type index_type;
  typedef typename Container::const_reference element_type;
  ElementLink(const Container& container, index_type index)
    : m_container(container), m_index(index){;}

  element_type operator->(){
    return m_container.at(m_index);
  }

  void say_something(){
    std::cout << "hello I'm an element link" << std::endl;
  }

  const Container& m_container;
  index_type m_index;
};
#endif