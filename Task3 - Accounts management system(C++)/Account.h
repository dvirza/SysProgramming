/* Assignment C++: 2
   Author: Dvir Zaguri, ID: 315602284
		   Ben Haimoff, ID: 206563660
*/ 

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
using namespace std;

class Account {
public:
    Account(const string& number, const string& holder, double initialBalance);
    virtual ~Account() = default;
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual double getBalance() const;
    friend ostream& operator<<(ostream& os, const Account& account);

protected:
    string accountNumber;
    string accountHolderName;
    double balance;
};

#endif
