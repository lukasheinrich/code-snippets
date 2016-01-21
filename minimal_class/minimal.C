#include "MyClass.h"
void minimal(){
    gSystem->Load("libMyClass.so");
    MyClass* mC = new MyClass();
}