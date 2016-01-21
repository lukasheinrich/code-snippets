#include "MyClass.h"
#include <iostream>
ClassImp(MyClass)

MyClass::MyClass()
{
    std::cout << "hello" << std::endl;
}

MyClass::~MyClass()
{
}