#include "Queue.cpp"
#include <iostream>

int main() {
  Queue<int> q(5);
  q.push(1);
  q.push(1);
  q.push(1);
  q.push(4);
  q.push(2);
  q.pop();
  q.pop();
  q.pop();
  q.push(5);
  q.push(1);

  for(int i = 0; i < 4; ++i)
    std::cout << "front = " << q.front() << " -- pop = " << q.pop() << std::endl;

  return 0;
}
