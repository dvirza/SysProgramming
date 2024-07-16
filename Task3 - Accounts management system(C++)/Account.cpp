/* Assignment C++: 2
   Author: Dvir Zaguri, ID: 315602284
		   Ben Haimoff, ID: 206563660
*/ 

#include "Account.h"

Account::Account(const string& number, const string& holder, double initialBalance)
    : accountNumber(number), accountHolderName(holder), balance(initialBalance) {}

double Account::getBalance() const {
    return balance;
}

ostream& operator<<(ostream& os, const Account& account) {
    os << "Account Number: " << account.accountNumber << endl;
    os << "Account Holder: " << account.accountHolderName << endl;
    os << "Balance: $" << account.getBalance() << endl;
    return os;
}
