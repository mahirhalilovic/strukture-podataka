#include <cstdlib>
#include <ctime>
#include <string>

class Zadatak {
  public:
    Zadatak() {
      srand(time(NULL));
      identifikator_ = rand();
    }

    Zadatak(std::string ime, std::string opis, short prioritet)
      : ime_{ime}, opis_{opis}, prioritet_{prioritet} {
        
        srand(time(NULL));
        identifikator_ = rand();
      }

    Zadatak(int id, std::string i, std::string o, short p, std::string s)
      : identifikator_{id}, ime_{i}, opis_{o}, prioritet_{p}, status_{s} {}

    int getID() const { return identifikator_; }
    std::string getIme() const { return ime_; }
    std::string getOpis() const { return opis_; }
    short getPrioritet() const { return prioritet_; }
    std::string getStatus() const { return status_; }
    void setIme(std::string ime) { ime_ = ime; }
    void setOpis(std::string opis) { opis_ = opis; }
    void setPrioritet(short prioritet) { prioritet_ = prioritet; }
    void setStatus(std::string s) { status_ = s; }

    bool operator<(Zadatak& other) { return getPrioritet() < other.getPrioritet(); }
    bool operator>(Zadatak& other) { return getPrioritet() > other.getPrioritet(); }

  private:
    int identifikator_;
    std::string ime_{""};
    std::string opis_{""};
    short prioritet_{1};
    std::string status_{"na cekanju"};
};

/*
 
  Jedan zadatak je opisan sa minimalno sljedecim informacijama

  0. Jedinstveni identifikator zadatka - random broj kojim će program referen-
cirati zadatak

  1. Kratko ime zadatka
  2. Opis zadatka (opis može biti prazan)
  3. Prioritet zadatka (1, 2 ili 3, gdje je 3 najveći prioritet)
  4. Status zadatka - na čekanju, u toku, ili završen
 
*/
