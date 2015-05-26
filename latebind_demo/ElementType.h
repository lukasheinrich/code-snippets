#ifndef ELEMENT_TYPE
#define ELEMENT_TYPE

// dummy element type implementatino (e.b. xADO::TrigElectron)

struct ElementType{
  ElementType(const std::string& name):m_name(name){;}
  void say_hello() const {
    std::cout << "hello i'm an element and my name is: " << m_name << std::endl; 
  }
  std::string m_name;
};

#endif