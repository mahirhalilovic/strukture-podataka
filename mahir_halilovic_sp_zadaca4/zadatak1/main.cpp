#include "PostfixCalc.cpp"

int main() {
  PostfixCalc calc;
  std::string k;

  while(std::getline(std::cin, k)) {
    std::cout << " >>  " << calc.parse(k) << std::endl;
  }

  return 0;
}
