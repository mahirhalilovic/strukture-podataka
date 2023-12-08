#include "todo.cpp"
#include <iostream>

int main() {
  TODO todo;
  todo.loadTasks();

  while(1) {
    int izbor = todo.opcije();
    switch(izbor) {
      case 0:
        break;
      case 1:
        todo.dodaj_novi();
        break;
      case 2:
        todo.prikazi_sve();
        break;
      case 3:
        todo.prikazi_na_cekanju();
        break;
      case 4:
        todo.prikazi_u_toku();
        break;
      case 5:
        todo.prikazi_zavrseni();
        break;
      case 6:
        todo.zapocni();
        break;
      case 7:
        todo.zavrsi();
        break;
      case 8:
        todo.ukloni();
        break;
      case 9:
        todo.izmijeni_postojeci();
        break;
      default:
        std::cout << "Pogresan unos!\n";
        break;
    }

    if(!izbor) break;
  }

  todo.saveTasks();

  return 0;
}
