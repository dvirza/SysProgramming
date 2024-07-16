/* Assignment C++: 2
   Author: Dvir Zaguri, ID: 315602284
		   Ben Haimoff, ID: 206563660
*/ 

#include "SavingsAccount.h"
#include <cmath>
#include <iostream>

SavingsAccount::SavingsAccount(const string& number, const string& holder, double initialBalance, double annualRate)
    : Account(number, holder, initialBalance), annualInterestRate(annualRate), lastTransactionTime(std::chrono::steady_clock::now()) {}

void SavingsAccount::deposit(double amount) {
    updateInterest();
    balance += amount;
    lastTransactionTime = std::chrono::steady_clock::now();
    cout << "Deposit: $" << amount << "\n";
}

void SavingsAccount::withdraw(double amount) {
    updateInterest();
    if (balance >= amount) {
        balance -= amount;
        cout << "Withdrawn $" << amount << "\n";
    } else {
        cout << "Insufficient funds\n";
    }
    lastTransactionTime = std::chrono::steady_clock::now();
}

void SavingsAccount::updateInterest() {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::minutes>(now - lastTransactionTime).count();
    if (duration > 0) {
        double years = duration / (365.25 * 24 * 60);  // Convert minutes to years
        if (years > 0) {
            balance *= pow(1 + annualInterestRate, years);
            lastTransactionTime = now;
        }
    }
}

double SavingsAccount::getBalance() const {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::minutes>(now - lastTransactionTime).count();
    double currentBalance = balance;
    if (duration > 0) {
        double years = duration / (365.25 * 24 * 60);  // Convert minutes to years
        if (years > 0) {
            currentBalance *= pow(1 + annualInterestRate, years);
        }
    }
    return currentBalance;
}
