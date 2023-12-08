#include "../zadatak4/Queue.cpp"

class BankAccount {
  private:
    struct Transaction {
      double amount_;
      std::string date_;
      std::string time_;
    };
    double balance_;
    Queue<Transaction> transactions_;

  public:
    void newTransaction();
    void applyTransaction();
    void pendingTransaction();
    void discardPendingTransaction();
    double balance() const;
    short printActions();
};
