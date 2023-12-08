#include "Queue.hpp"
#include <iostream>

int main() {
  Queue<int> q;

  q.enqueue(1).enqueue(2).enqueue(3);

  std::cout << q.top();
  q.dequeue();
  std::cout << q.top();
  q.dequeue();
  std::cout << q.top();

  return 0;
}
