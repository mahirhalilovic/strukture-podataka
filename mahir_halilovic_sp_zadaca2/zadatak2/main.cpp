#include <iostream>
#include <vector>
#include <string>

#include "Library.cpp"

int main() {

  Library lib;
  std::string option;

  while(1) {
    option = lib.enterCommand();

    if(option == "CreateUser") {
      lib.CreateUser();
    } else if(option == "BookAdd") {
      lib.BookAdd();
    } else if(option == "BookBorrow") {
      lib.BookBorrow();
    } else if(option == "BookReturn") {
      lib.BookReturn();
    } else if(option == "BookSearchByTitle") {
      lib.BookSearchByTitle();
    } else if(option == "BookSearchByAuthor") {
      lib.BookSearchByAuthor();
    } else if(option == "BookSearchByPublisher") {
      lib.BookSearchByPublisher();
    } else if(option == "BookSearchByPublicationYear") {
      lib.BookSearchByPublicationYear();
    } else if(option == "Help") {
      lib.help();
    } else if(option == "Exit") {
      break;
    } else if(option == "PrintUsers") {
      lib.printUsers();
    } else if(option == "PrintBooks") {
      lib.printBooks();
    } else { std::cout << "Invalid command. Please try again.\n"; }
  }

  return 0;
}
