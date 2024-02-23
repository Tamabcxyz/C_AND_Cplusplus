/**
 * redefine method of base class in derived class
 */
/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java,
PHP, Ruby, Perl, C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C,
Assembly, HTML, CSS, JS, SQLite, Prolog. Code, Compile, Run and Debug online
from anywhere in world.

*******************************************************************************/
#include <iostream>

using namespace std;
class Account {
  friend std::ostream &operator<<(std::ostream &os, const Account &account);

protected:
  double balance;

public:
  Account() : balance{0} {
    std::cout << "default constructor Account call" << std::endl;
  }
  Account(double x) : balance{x} {
    std::cout << "constructor Account with arg call" << std::endl;
  }
  ~Account() { std::cout << "destructor Account call" << std::endl; }
  void deposit(double amount) { balance += amount; }
  void withdraw(double amount) {
    if (balance - amount >= 0) {
      balance -= amount;
    } else {
      std::cout << "insufficient funds" << std::endl;
    }
  }
};
std::ostream &operator<<(std::ostream &os, const Account &account) {
  os << "Account balance: " << account.balance;
  return os;
}

class Saving_Account : public Account {
  friend std::ostream &operator<<(std::ostream &os, const Saving_Account &sa);

protected:
  double int_rate;

public:
  Saving_Account() : Account{}, int_rate{0} {
    std::cout << "default constructor Saving_Account call" << std::endl;
  }
  Saving_Account(double x, double y) : Account{x}, int_rate{y} {
    std::cout << "constructor Saving_Account with arg call" << std::endl;
  }
  ~Saving_Account() {
    std::cout << "destructor Saving_Account call" << std::endl;
  }
  void deposit(double amount) {
    amount = amount + (amount * int_rate / 100);
    Account::deposit(amount);
  }
};

std::ostream &operator<<(std::ostream &os, const Saving_Account &account) {
  os << "Saving_Account balance: " << account.balance
     << " inherest rate: " << account.int_rate;
  return os;
}

int main() {
  cout << "================Account class================\n";
  Account a1{1000.0};
  cout << a1 << std::endl;
  a1.deposit(500.0);
  cout << a1 << std::endl;
  a1.withdraw(500.0);
  cout << a1 << std::endl;

  cout << "================Saving_Account class================\n";
  Saving_Account a2{2000.0, 5.0};
  cout << a2 << std::endl;
  a2.deposit(1000.0);
  cout << a2 << std::endl;
  a2.withdraw(500.0); // if child class not implement parent class will be call
  cout << a2 << std::endl;

  return 0;
}