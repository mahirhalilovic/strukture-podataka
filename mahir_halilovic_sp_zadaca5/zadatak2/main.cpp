#include "map.hpp"

int main() {
  Map<int, int> mapa;

  mapa.insert(5, 10);
  mapa.insert(3, 6);
  mapa.insert(4, 8);
  mapa.insert(1, 2);
  mapa.insert(2, 4);
  mapa.insert(10, 20);
  mapa.insert(8, 16);
  mapa.insert(9, 18);
  mapa.print();
  std::cout << mapa.size() << std::endl;
  mapa.erase(5);
  std::cout << mapa.size() << std::endl;

  mapa.print();

  std::cout << mapa.at(9) << std::endl;
  try{
    mapa.at(100);
  } catch(std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  if(!mapa.find(50)) std::cout << "Nema elementa" << std::endl;

  mapa[12] = 24;
  mapa.print();

  return 0;
}
