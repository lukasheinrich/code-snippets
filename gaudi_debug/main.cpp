#include  <dlfcn.h>
int main(){
    dlopen("header.so",RTLD_NOW);
}
