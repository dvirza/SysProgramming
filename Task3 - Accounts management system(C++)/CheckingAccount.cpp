/* Assignment C++: 2
   Author: Dvir Zaguri, ID: 315602284
		   Ben Haimoff, ID: 206563660
*/ 

#include "CheckingAccount.h"

CheckingAccount::CheckingAccount(const string& number, const string& holder, double initialBalance, double overdraft)
    : Account(number, holder, initialBalance), overdraftLimit(overdraft) {}

void CheckingAccount::deposit(double amount) {
    balance += amount;
}

void CheckingAccount::withdraw(double amount) {
    if (balance + overdraftLimit >= amount) {
        balance -= amount;
    } else {
        cout << "Overdraft limit exceeded\n";
    }
}
