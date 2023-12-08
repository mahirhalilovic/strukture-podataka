#include <string>
#include <iostream>
#include <algorithm>
#include "../zadatak1/MojVektor.hpp"
#include "Library.hpp"

void Library::help() {
  std::string m(50, '-');
  std::string j(50, '=');
  std::cout << m << "\nList of commands:\n" << j << '\n';
  std::cout << "CreateUser \nBookAdd \nBookBorrow \nBookReturn \n"
               "BookSearchByTitle \nBookSearchByAuthor \n"
               "BookSearchByPublisher \nBookSearchByPublicationYear \n";
  std::cout << "Help \nExit \n" << m << '\n';
}

void Library::printLib() {
  std::string jed(50, '=');
  std::cout << jed << std::endl;
  std::cout << "University of Tuzla\nFaculty of Electrical Engineering\n\n";
  std::cout << "Library application\nVersion: April 2023.\n" << jed << std::endl;

  help();
}

std::string Library::enterCommand() {
  std::string t(50, '.');
  std::string temp;
  std::cout << t << "\nEnter command: ";
  std::cin >> temp;
  std::cout << t << '\n';

  return temp;
}

Library::Library() { printLib(); }

void Library::printUsers() {
  std::string m(50, '-');
  std::cout << "Library users:\n" << m << '\n';
  for(auto k : users_)
    std::cout << k.getInfo() << std::endl;
  std::cout << m << std::endl;
}

void Library::printBooks() {
  std::cout << "Books in library:\n";
  for(auto k : books_)
    k.printBook();
}

void Library::CreateUser() {
  std::string name, surname;
  int id;
  
  std::cout << "First name: ";
  std::cin >> name;
  std::cout << "Last name: ";
  std::cin >> surname;
  std::cout << "User ID: ";
  std::cin >> id;

  auto it = std::find_if(users_.begin(), users_.end(), [&id](const User &obj) {return obj.getID() == id;});
  if(it == users_.end()) {
    users_.push_back(User(name, surname, id));
  } else {
    std::cout << "User with id {" << id << "} already exists!\n";
    return;
  }

  std::cout << "User created successfully.\n";
}

void Library::BookAdd() {
  std::string t, a, p;
  int py, n;

  std::cin.ignore();
  std::cout << "Title: ";
  std::getline(std::cin, t); 
  std::cout << "Author: ";
  std::getline(std::cin, a);
  std::cout << "Publisher: ";
  std::getline(std::cin, p);
  std::cout << "Publication year: ";
  std::cin >> py;
  std::cout << "Number of copies: ";
  std::cin >> n;

  auto it = std::find_if(books_.begin(), books_.end(), [&t](const Book &obj){ return obj.getTitle() == t; });

  if(it == books_.end()) {
    books_.push_back(Book(t, a, p, py, n));
    std::cout << "Book added successfully.\n";
  } else {
    std::cout << "That book already exists!\n";
  }
}

void Library::BookBorrow() {
  int id;
  std::string title;

  std::cout << "User ID: ";
  std::cin >> id;
  auto it = std::find_if(users_.begin(), users_.end(), [&id](const User &obj){ return obj.getID() == id; });
  if(it == users_.end()) {
    std::cout << "User doesn't exist!\n";
  } else if(it->didBorrow()) {
      std::cout << "User already borrowed book!\n";
  } else {
    std::cin.ignore();
    std::cout << "Book title: ";
    std::getline(std::cin, title);

    auto it2 = std::find_if(books_.begin(), books_.end(), [&title](const Book &obj){ return obj.getTitle() == title; });
    if(it2 != books_.end()) {
      it2->borrow();
      it->borrow(title);
    }  else
      std::cout << "Book doesn't exist!\n";
  }
}

void Library::BookReturn() {
  int id;
  std::string title;

  std::cout << "User ID: ";
  std::cin >> id;
  auto it = std::find_if(users_.begin(), users_.end(), [&id](const User &obj){ return obj.getID() == id; });
  if(it == users_.end()) {
    std::cout << "User doesn't exist!\n";
  } else {
    std::cout << "Book title: ";
    std::cin >> title;

    auto it2 = std::find_if(books_.begin(), books_.end(), [&title](const Book &obj){ return obj.getTitle() == title; });
    if(it2 != books_.end()) {
      if(it->book() == title) {
        it->returned();
        it2->bookReturn();
      } else {
        std::cout << "This user didn't borrow this book.\n";
      }
    }
    else
      std::cout << "Book doesn't belong to this library!\n";
  }
}

void Library::BookSearchByTitle() {
  std::string title;
  std::cin.ignore();
  std::cout << "Title: ";
  std::getline(std::cin, title);

  auto it = std::find_if(books_.begin(), books_.end(), [&title](const Book &obj){ return obj.getTitle() == title; });

  if(it == books_.end()) {
    std::cout << "This library doesn't have this book.\n";
  } else {
    std::cout << "Found book: \n";
    it->printBook();
  }
}

void Library::BookSearchByAuthor() {
  std::string author;
  std::cin.ignore();
  std::cout << "Author: ";
  std::getline(std::cin, author);
  MojVektor<int> indices;
  
  for(auto it = books_.begin(); it != books_.end(); ++it) {
    if(it->getAuthor() == author) {
      indices.push_back(it - books_.begin());
    }
  }

  if(indices.size() == 0) {
    std::cout << "There are no books from this author.\n";
  } else {
    std::cout << "Found books: \n";
    for(int i = 0; i < indices.size(); ++i) {
      books_[indices[i]].printBook();
    }
  }
}

void Library::BookSearchByPublisher() {
  std::string publisher;
  std::cin.ignore();
  std::cout << "Publisher: ";
  std::getline(std::cin, publisher);
  MojVektor<int> indices;
  
  for(auto it = books_.begin(); it != books_.end(); ++it) {
    if(it->getPublisher() == publisher) {
      indices.push_back(it - books_.begin());
    }
  }

  if(indices.size() == 0) {
    std::cout << "There are no books from this publisher.\n";
  } else {
    std::cout << "Found books: \n";
    for(int i = 0; i < indices.size(); ++i) {
      books_[indices[i]].printBook();
    }
  }
}

void Library::BookSearchByPublicationYear() {
  int year;
  std::cout << "Publication year: ";
  std::cin >> year;
  MojVektor<int> indices;
  
  for(auto it = books_.begin(); it != books_.end(); ++it) {
    if(it->getPublicationYear() == year) {
      indices.push_back(it - books_.begin());
    }
  }

  if(indices.size() == 0) {
    std::cout << "There are no books published that year.\n";
  } else {
    std::cout << "Found books: \n";
    for(int i = 0; i < indices.size(); ++i) {
      books_[indices[i]].printBook();
    }
  }
}
