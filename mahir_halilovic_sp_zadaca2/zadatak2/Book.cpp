#pragma once
#include <string>
#include <iostream>
#include "Book.hpp"

Book::Book(std::string n, std::string a, std::string i, int g, int b)
  : naslov_{n}, autor_{a}, izdavac_{i}, godinaIzdavanja_{g}, brojPrimjeraka_{b}, maxBrojPrimjeraka_{b} {}

std::string Book::getTitle() const { return naslov_; }
std::string Book::getAuthor() const { return autor_; }
std::string Book::getPublisher() const { return izdavac_; }
int Book::getPublicationYear() const { return godinaIzdavanja_; }
int Book::getNumberOfCopies() const { return brojPrimjeraka_; }

void Book::borrow() {
  if(brojPrimjeraka_) {
    --brojPrimjeraka_;
    
    std::cout << "Book borrowed.\n";
  } else
    std::cout << "Book is not available.\n";
}

void Book::bookReturn() {
  if(brojPrimjeraka_ < maxBrojPrimjeraka_) {
    ++brojPrimjeraka_;
    std::cout << "Book successfully returned.\n";
  } else {
    std::cout << "Book doesn't belong to this library.\n";
  }
}

void Book::printBook() {
  std::string m(50, '-');
  std::cout << m << "\nTitle: " << naslov_ << "\nAuthor: " << autor_ << "\nPublisher: " << izdavac_;
  std::cout << "\nPublication year: " << godinaIzdavanja_ << "\nNumber of copies: " << brojPrimjeraka_ << '\n' << m << '\n';
}
