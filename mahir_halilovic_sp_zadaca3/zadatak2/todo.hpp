#include "Zadatak.hpp"
#include "../zadatak1/DoubleLinkedList.hpp"

class TODO{
  public:
    TODO() = default;

    TODO& loadTasks();
    void loadNaCekanju();
    void loadZapoceti();
    void loadZavrseni();
    TODO& saveTasks();
    void saveNaCekanju();
    void saveZapoceti();
    void saveZavrseni();

    int opcije();

    TODO& dodaj_novi();
    TODO& zapocni();
    TODO& zavrsi();
    TODO& ukloni();
    void izmijeni_postojeci();
    TODO& izmijeni_na_cekanju();
    TODO& izmijeni_u_toku();
    TODO& izmijeni_zavrseni();
    
    void prikazi_na_cekanju();
    void prikazi_u_toku();
    void prikazi_zavrseni();
    void prikazi_sve();

  private:
    DoubleLinkedList<Zadatak> na_cekanju;
    DoubleLinkedList<Zadatak> u_toku;
    DoubleLinkedList<Zadatak> zavrseni;
};
