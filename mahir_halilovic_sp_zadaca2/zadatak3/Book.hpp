#pragma once
#include <string>

class Book{

  public:
    Book(std::string, std::string, std::string, int, int);

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getPublicationYear() const;
    int getNumberOfCopies() const;

    void borrow();
    void bookReturn();
    void printBook();

  private:
    std::string naslov_;
    std::string autor_;
    std::string izdavac_;
    int godinaIzdavanja_;
    int brojPrimjeraka_;
    int maxBrojPrimjeraka_;
};
