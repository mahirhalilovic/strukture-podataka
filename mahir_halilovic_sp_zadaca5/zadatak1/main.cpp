#include "heap.hpp"

int main() {
  Heap<int> heap;

  try{
    heap.max();
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  heap.insert(22);
  heap.insert(19);
  heap.insert(17);
  heap.insert(19);
  heap.insert(14);
  heap.insert(10);
  heap.insert(6);
  heap.insert(2);
  heap.insert(9);
  heap.insert(4);
  heap.insert(13);

  std::cout << heap;

  heap.insert(21);

  std::cout << heap;
  std::cout << heap.removeMax() << std::endl;
  std::cout << heap;

  return 0;
}
