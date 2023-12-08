#include <iostream>
#include "DoubleLinkedList.hpp"

int main(int argc, char* argv[]) {
  DoubleLinkedList<int> l;
  l.push_back(1);
  l.push_back(2);
  l.push_back(3);

  auto it = l.begin();
  DoubleLinkedList<int>::Iterator it2;

  std::cout << *it;
  ++it;
  std::cout << *it;
  ++it;
  std::cout << *it;
  ++it;
  std::cout << *(l.end());
 
  return 0;
}
