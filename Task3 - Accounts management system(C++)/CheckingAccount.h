/* Assignment C++: 2
   Author: Dvir Zaguri, ID: 315602284
		   Ben Haimoff, ID: 206563660
*/ 

#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

class CheckingAccount : public Account {
public:
    CheckingAccount(const string& number, const string& holder, double initialBalance, double overdraft);
    void deposit(double amount) override;
    void withdraw(double amount) override;

private:
    double overdraftLimit;
};

#endif
