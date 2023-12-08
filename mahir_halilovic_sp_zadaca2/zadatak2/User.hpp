#pragma once
#include <string>
#include "Book.cpp"

class User{

  public:
    User() = default;
    User(std::string i, std::string p, int id);

    int getID() const;
    std::string getInfo() const;
    bool didBorrow() const;
    std::string book() const;

    void borrow(std::string);
    void returned();

  private:
    std::string ime_;
    std::string prezime_;
    int id_;
    bool borrowed_{false};
    std::string borrowedBook_{"None"};
};
