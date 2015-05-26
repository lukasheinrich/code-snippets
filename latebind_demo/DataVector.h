#ifndef DATAVECTOR_H
#include <vector>

// dummy DataVector implementation

template<typename T>
struct DataVector : public std::vector<T*>{};
#endif