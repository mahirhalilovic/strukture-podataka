#pragma once
#include <string>
#include "User.hpp"

User::User(std::string i, std::string p, int id)
  : ime_{i}, prezime_{p}, id_{id} {}

int User::getID() const { return id_; }

std::string User::getInfo() const {
  std::string info = ime_;
  info += ' ';
  info += prezime_;
  info += ", ";
  info += std::to_string(id_);
  info += ", borrowed: ";
  info += borrowedBook_;

  return info;
}

bool User::didBorrow() const { return borrowed_; }
std::string User::book() const { return borrowedBook_; }

void User::borrow(std::string title) { borrowed_ = true; borrowedBook_ = title; }

void User::returned() { borrowed_ = false; borrowedBook_ = "None"; }
