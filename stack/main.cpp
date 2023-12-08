#include "Stack.hpp"
#include <iostream>

int main() {
  myStack<int> ms;

  ms.push(3);
  ms.push(2);
  ms.push(1);
  std::cout << ms.top();
  ms.pop();
  std::cout << ms.top();
  ms.pop();
  std::cout << ms.top();
  ms.pop();

  return 0;
}
