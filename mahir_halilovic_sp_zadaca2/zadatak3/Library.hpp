#pragma once
#include <vector>
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
    std::vector<User> users_;
    std::vector<Book> books_;
};
