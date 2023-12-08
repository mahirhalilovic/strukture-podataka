#include "todo.cpp"
#include <iostream>

int main() {
  TODO lista;

  lista.loadTasks();
  lista.prikazi_sve();
  lista.zapocni();
  lista.saveTasks();

  return 0;
}
