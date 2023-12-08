#pragma once
#include "../zadatak1/MojVektor.hpp"
#include "Book.cpp"
#include "User.cpp"

class Library{

  public:
    Library();

    void CreateUser();
    void BookAdd();
    void BookBorrow();
    void BookReturn();
    void BookSearchByTitle();
    void BookSearchByAuthor();
    void BookSearchByPublisher();
    void BookSearchByPublicationYear();

    void printUsers();
    void printBooks();
    void printLib();
    void help();
    std::string enterCommand();

  private:
    MojVektor<User> users_;
    MojVektor<Book> books_;
};
