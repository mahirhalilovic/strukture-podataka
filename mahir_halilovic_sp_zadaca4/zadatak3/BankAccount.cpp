#include "BankAccount.hpp"
#include <iostream>

short BankAccount::printActions() {
  std::cout << std::string(50, '*') << std::endl;
  std::cout << "Actions: " << 
    "\n\t1. New transaction" << 
    "\n\t2. Apply transaction" <<
    "\n\t3. Pending transaction" <<
    "\n\t4. Discard pending transaction" <<
    "\n\t5. Balance" <<
    "\n\t6. Exit" <<
    "\nYour choice? ";

  short option;
  std::cin >> option;
  return option;
}

void BankAccount::newTransaction() {
  double am;
  std::string dt, tme;
  std::cout << "Amount: ";
  std::cin >> am;
  std::cout << "Date: ";
  std::cin >> dt;
  std::cout << "Time: ";
  std::cin >> tme;
  transactions_.push(Transaction{am, dt, tme});
}

void BankAccount::applyTransaction() {
  if(transactions_.empty()) std::cout << "No pending transaction!" << std::endl; // throw std::out_of_range{"No pending transactions!"};
  if(balance() + transactions_.front().amount_) balance_ += transactions_.pop().amount_;
  else std::cout << "Not enough funds in your account.";
}

void BankAccount::pendingTransaction() {
  if(transactions_.empty()) std::cout << "No pending transaction!" << std::endl; // throw std::out_of_range{"No pending transactions!"};

  std::cout << "Amount: " << transactions_.front().amount_ << std::endl;
  std::cout << "Date: " << transactions_.front().date_ << std::endl;
  std::cout << "Time: " << transactions_.front().time_ << std::endl;
}

void BankAccount::discardPendingTransaction() {
  if(transactions_.empty()) std::cout << "No pending transaction!" << std::endl; // throw std::out_of_range{"No pending transactions!"};
  transactions_.pop();
}

double BankAccount::balance() const { return balance_; }
