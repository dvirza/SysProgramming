/* Assignment C++: 2
   Author: Dvir Zaguri, ID: 315602284
		   Ben Haimoff, ID: 206563660
*/ 

#ifndef MENU_H
#define MENU_H

#include "Array.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"

class Menu {
public:
    Menu();
    void mainMenu();
private:
    Array<Account*> bankAccounts;
    void addAccount();
    void deposit();
    void withdraw();
    void deleteAccount();
    void printAccounts();
    void exitProgram();
};

#endif
