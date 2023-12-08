#include "todo.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

std::string ime, opis;
int id;
short prioritet;

TODO& TODO::loadTasks() {
  loadNaCekanju();
  loadZapoceti();
  loadZavrseni();

  return *this;
}

// void TODO::loadNaCekanju() {
//   std::fstream file("na_cekanju.txt");
//   if(!file) throw std::runtime_error{"Fajl ne postoji."};
//
//   std::string line, ime, opis;
//   int id;
//   short prior;
//   while(std::getline(file, line)) {
//     file >> id;
//     std::getline(file, ime);
//     std::getline(file, opis);
//     file >> prior;
//
//     na_cekanju.push_back(Zadatak(id, ime, opis, prior, "na cekanju"));
//   }
// }
//
// void TODO::loadZapoceti() {
//   std::ifstream file("u_toku.txt");
//   if(!file) throw std::runtime_error{"Fajl ne postoji."};
//
//   std::string line, ime, opis;
//   int id;
//   short prior;
//   while(std::getline(file, line)) {
//     file >> id;
//     std::getline(file, ime);
//     std::getline(file, opis);
//     file >> prior;
//
//     u_toku.push_back(Zadatak(id, ime, opis, prior, "u toku"));
//   }
// }
//
// void TODO::loadZavrseni() {
//   std::ifstream file("zavrseni.txt");
//   if(!file) throw std::runtime_error{"Fajl ne postoji."};
//
//   std::string line, ime, opis;
//   int id;
//   short prior;
//   while(std::getline(file, line)) {
//     file >> id;
//     std::getline(file, ime);
//     std::getline(file, opis);
//     file >> prior;
//
//     zavrseni.push_back(Zadatak(id, ime, opis, prior, "zavrsen"));
//   }
// }



std::ostream& operator<<(std::ostream& out, const Zadatak& z) {
  return out << z.getIme() << '\n' << z.getOpis() << '\n' << z.getID() << ' ' << z.getPrioritet() << '\n';
}

std::istream& operator>>(std::istream& ins, Zadatak& z) {
  std::getline(ins, ime);
  std::getline(ins, opis);
  ins >> id >> prioritet;
  ins.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return ins;
}

void TODO::loadNaCekanju() {
  std::ifstream f("na_cekanju.txt");
  Zadatak z;
  while(f >> z) na_cekanju.push_back(Zadatak(id, ime, opis, prioritet, "na cekanju"));
  f.close();
}

void TODO::loadZapoceti() {
  std::ifstream f("zapoceti.txt");
  Zadatak z;
  while(f >> z) u_toku.push_back(Zadatak(id, ime, opis, prioritet, "u toku"));
  f.close();
}

void TODO::loadZavrseni() {
  std::ifstream f("zavrseni.txt");
  Zadatak z;
  while(f >> z) zavrseni.push_back(Zadatak(id, ime, opis, prioritet, "zavrsen"));
  f.close();
}

TODO& TODO::saveTasks() {
  saveNaCekanju();
  saveZapoceti();
  saveZavrseni();
  return *this;
}

void TODO::saveNaCekanju() {
  std::ofstream f("na_cekanju.txt");
  for(const Zadatak& z : na_cekanju) f << z;
  f.close();
}

void TODO::saveZapoceti() {
  std::ofstream f("zapoceti.txt");
  for(const Zadatak& z : u_toku) f << z;
  f.close();
}

void TODO::saveZavrseni() {
  std::ofstream f("zavrseni.txt");
  for(const Zadatak& z : zavrseni) f << z;
  f.close();
}

int TODO::opcije() {
  int izbor;
  std::cout << "Moguce opcije: \n";
  std::cout << "\t0. Izlaz\n";
  std::cout << "\t1. Dodaj novi zadatak\n";
  std::cout << "\t2. Prikazi sve zadatke\n";
  std::cout << "\t3. Prikazi zadatke na cekanju\n";
  std::cout << "\t4. Prikazi zapocete zadatke\n";
  std::cout << "\t5. Prikazi zavrsene zadatke\n";
  std::cout << "\t6. Zapocni zadatak\n";
  std::cout << "\t7. Zavrsi zadatak\n";
  std::cout << "\t8. Ukloni zadatak\n";
  std::cout << "\t9. Izmijeni postojeci zadatak\n";
  std::cout << "Izbor: ";
  std::cin >> izbor;
  std::cin.ignore();
  std::cout << '\n';
  return izbor;
}

TODO& TODO::dodaj_novi() {
  std::string ime, opis;
  short prioritet;

  std::cout << "Unesite kratko ime zadatka: ";
  std::getline(std::cin, ime);
  std::cout << "Unesite opis zadatka: ";
  std::getline(std::cin, opis);
  std::cout << "Unesite prioritet zadatka(1, 2, 3): ";
  std::cin >> prioritet;
  std::cin.ignore();
  
  na_cekanju.push_back(Zadatak(ime, opis, prioritet));
  return *this;
}

TODO& TODO::zapocni() {
  if(!na_cekanju.size()) {
    std::cout << "Nema zadataka na cekanju!\n";
    return *this;
  }

  prikazi_na_cekanju();

  int id;
  std::cout << "Unesite identifikator zadatka koji zelite zapoceti: ";
  std::cin >> id;

  auto it = std::find_if(na_cekanju.begin(), na_cekanju.end(), [&id](const Zadatak& zad){ return zad.getID() == id; });
  if(it != na_cekanju.end()) {
    it->setStatus("u toku");
    u_toku.push_back(*it);
    na_cekanju.erase(it);
    return *this;
  }
    
  std::cout << "Pogresan identifikator!\n";
  return *this;
}

TODO& TODO::zavrsi() {
  if(!u_toku.size()) {
    std::cout << "Nema zapocetih zadataka!\n";
    return *this;
  }
  
  prikazi_u_toku();

  int id;
  std::cout << "Unesite identifikator zadatka koji zelite zavrsiti: ";
  std::cin >> id;

  auto it = std::find_if(u_toku.begin(), u_toku.end(), [&id](const Zadatak& zad){ return zad.getID() == id; });
  if(it != u_toku.end()) {
    it->setStatus("zavrsen");
    zavrseni.push_back(*it);
    u_toku.erase(it);
    return *this;
  }
    
  std::cout << "Pogresan identifikator!\n";
  return *this;
}

TODO& TODO::ukloni() {
  if(!zavrseni.size()) {
    std::cout << "Nema zavrsenih zadataka!\n";
    return *this;
  }

  prikazi_zavrseni();

  int id;
  std::cout << "Unesite identifikator zadatka koji zelite ukloniti: ";
  std::cin >> id;

  auto it = std::find_if(zavrseni.begin(), zavrseni.end(), [&id](const Zadatak& zad){ return zad.getID() == id; });
  if(it != zavrseni.end()) {
    zavrseni.erase(it);
    return *this;
  }
    
  std::cout << "Pogresan identifikator!\n";
  return *this;
}

void TODO::izmijeni_postojeci() {
  int izbor;
  
  std::cout << "Unesite vrstu zadatka koji zelite izmijeniti:\n\t1. na cekanju\n\t2. u toku\n\t3. zavrseni\nIzbor: ";
  std::cin >> izbor;

  if(izbor == 1) izmijeni_na_cekanju();
  else if(izbor == 2) izmijeni_u_toku();
  else if(izbor == 3) izmijeni_zavrseni();
  else std::cout << "Pogresan unos!";
}

TODO& TODO::izmijeni_na_cekanju() {
  int id;

  prikazi_na_cekanju();

  std::cout << "Unesite identifikator zadatka koji zelite izmijeniti: ";
  std::cin >> id;

  auto it = std::find_if(na_cekanju.begin(), na_cekanju.end(), [&id](const Zadatak& zad){ return zad.getID() == id; });
  if(it != na_cekanju.end()) {
    std::string ime, opis;
    short prioritet;

    std::cin.ignore();
    std::cout << "Unesite kratko ime zadatka: ";
    std::getline(std::cin, ime);
    std::cout << "Unesite opis zadatka: ";
    std::getline(std::cin, opis);
    std::cout << "Unesite prioritet zadatka(1, 2, 3): ";
    std::cin >> prioritet;
    it->setIme(ime);
    it->setOpis(opis);
    it->setPrioritet(prioritet);

    return *this;
  }

  std::cout << "Pogresan identifikator!";
  return *this;
}

TODO& TODO::izmijeni_u_toku() {
  int id;

  prikazi_u_toku();

  std::cout << "Unesite identifikator zadatka koji zelite izmijeniti: ";
  std::cin >> id;

  auto it = std::find_if(u_toku.begin(), u_toku.end(), [&id](const Zadatak& zad){ return zad.getID() == id; });
  if(it != u_toku.end()) {
    std::string ime, opis;
    short prioritet;

    std::cin.ignore();
    std::cout << "Unesite kratko ime zadatka: ";
    std::getline(std::cin, ime);
    std::cout << "Unesite opis zadatka: ";
    std::getline(std::cin, opis);
    std::cout << "Unesite prioritet zadatka(1, 2, 3): ";
    std::cin >> prioritet;
    it->setIme(ime);
    it->setOpis(opis);
    it->setPrioritet(prioritet);

    return *this;
  }

  std::cout << "Pogresan identifikator!";
  return *this;
}

TODO& TODO::izmijeni_zavrseni() {
  int id;

  prikazi_zavrseni();

  std::cout << "Unesite identifikator zadatka koji zelite izmijeniti: ";
  std::cin >> id;

  auto it = std::find_if(zavrseni.begin(), zavrseni.end(), [&id](const Zadatak& zad){ return zad.getID() == id; });
  if(it != zavrseni.end()) {
    u_toku.erase(it);
    std::string ime, opis;
    short prioritet;

    std::cin.ignore();
    std::cout << "Unesite kratko ime zadatka: ";
    std::getline(std::cin, ime);
    std::cout << "Unesite opis zadatka: ";
    std::getline(std::cin, opis);
    std::cout << "Unesite prioritet zadatka(1, 2, 3): ";
    std::cin >> prioritet;

    u_toku.push_back(Zadatak(ime, opis, prioritet));
    return *this;
  }

  std::cout << "Pogresan identifikator!";
  return *this;
}

void TODO::prikazi_na_cekanju() {
  std::string j(30, '=');
  std::cout << j << "\nZadaci na cekanju: \n\n";

  auto temp_lista = na_cekanju;
  temp_lista.sort();
  auto it = temp_lista.begin();

  while(it != temp_lista.end()) {
    std::cout << "ID: " << it->getID();
    std::cout << "\nIme: " << it->getIme();
    std::cout << "\nOpis: " << it->getOpis();
    std::cout << "\nPrioritet: " << it->getPrioritet();

    std::cout << '\n' << j << '\n';
    ++it;
  }

  if(!na_cekanju.size()) std::cout << j << '\n';
}

void TODO::prikazi_u_toku() {
  std::string j(30, '=');
  std::cout << j << "\nZapoceti zadaci: \n\n";

  auto it = u_toku.begin();

  while(it != u_toku.end()) {
    std::cout << "ID: " << it->getID();
    std::cout << "\nIme: " << it->getIme();
    std::cout << "\nOpis: " << it->getOpis();
    std::cout << "\nPrioritet: " << it->getPrioritet();

    std::cout << '\n' << j << '\n';
    ++it;
  }

  if(!u_toku.size()) std::cout << j << '\n';
}

void TODO::prikazi_zavrseni() {
  std::string j(30, '=');
  std::cout << j << "\nZavrseni zadaci: \n\n";

  auto it = zavrseni.begin();

  while(it != zavrseni.end()) {
    std::cout << "ID: " << it->getID();
    std::cout << "\nIme: " << it->getIme();
    std::cout << "\nOpis: " << it->getOpis();
    std::cout << "\nPrioritet: " << it->getPrioritet();

    std::cout << '\n' << j << '\n';
    ++it;
  }

  if(!zavrseni.size()) std::cout << j << '\n';
}

void TODO::prikazi_sve() {
  prikazi_na_cekanju();
  prikazi_u_toku();
  prikazi_zavrseni();
}
