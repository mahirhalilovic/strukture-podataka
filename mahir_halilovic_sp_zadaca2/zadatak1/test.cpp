#include <iostream>
#include "MojVektor.hpp"

int main() {

  MojVektor<int> v{4, 5, 6};
  std::cout << "capacity before push back: " << v.capacity() << std::endl;
  v.push_back(7);

  for(auto k : v)
    std::cout << k << ' ';
  std::cout << " capacity: " << v.capacity();

  return 0;
}
