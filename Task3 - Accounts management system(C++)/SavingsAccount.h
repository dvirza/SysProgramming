/* Assignment C++: 2
   Author: Dvir Zaguri, ID: 315602284
		   Ben Haimoff, ID: 206563660
*/ 

#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"
#include <chrono>

class SavingsAccount : public Account {
public:
    SavingsAccount(const string& number, const string& holder, double initialBalance, double annualRate);
    void deposit(double amount) override;
    void withdraw(double amount) override;
    double getBalance() const override;

private:
    double annualInterestRate;
    std::chrono::steady_clock::time_point lastTransactionTime;
    void updateInterest();
};

#endif
