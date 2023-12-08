#include "BankAccount.cpp"

int main() {
  BankAccount bank;

  while(1) {
    bool ex = false;
    switch(bank.printActions()) {
      case 1:
        bank.newTransaction();
        break;
      case 2:
        bank.applyTransaction();
        break;
      case 3:
        bank.pendingTransaction();
        break;
      case 4:
        bank.discardPendingTransaction();
        break;
      case 5:
        std::cout << "Balance: " << bank.balance() << std::endl;
        break;
      case 6:
        ex = true;
        break;
      default:
        std::cout << "Invalid option!" << std::endl;
        break;
    }

    if(ex) break;
  }

  return 0;
}
