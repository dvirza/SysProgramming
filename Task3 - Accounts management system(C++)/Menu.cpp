/* Assignment C++: 2
   Author: Dvir Zaguri, ID: 315602284
		   Ben Haimoff, ID: 206563660
*/ 

#include "Menu.h"
#include <iostream>
#include <iomanip>
using namespace std;

Menu::Menu() : bankAccounts() {}

void Menu::mainMenu() {
    int choice;
    do {
        cout << "====== Main Menu ======\n"
             << "1 - Add a new account\n"
             << "2 - Deposit (index, amount)\n"
             << "3 - Withdraw (index, amount)\n"
             << "4 - Delete an account (index)\n"
             << "5 - Print details of all accounts\n"
             << "6 - Exit\n"
             << "=======================================\n"
             << "Enter your choice: ";
        cin >> choice;
        switch(choice) {
            case 1: addAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: deleteAccount(); break;
            case 5: printAccounts(); break;
            case 6: exitProgram(); break;
            default: cout << "Invalid choice!\n"; break;
        }
    } while(choice != 6);
}

void Menu::addAccount() {
    string number, holder, type;
    double initialBalance, rate, overdraft;

    cout << "Enter account number: ";
    cin >> number;
    cout << "Enter account holder name: ";
    cin >> holder;
    cout << "Enter initial balance: ";
    cin >> initialBalance;
    cout << "Enter account type (S for Savings, C for Checking): ";
    cin >> type;

    if (type == "S" || type == "s") {
        cout << "Enter annual interest rate: ";
        cin >> rate;
        bankAccounts.insert(new SavingsAccount(number, holder, initialBalance, rate));
        cout << "Account added successfully.\n";
    } else if (type == "C" || type == "c") {
        cout << "Enter overdraft limit: ";
        cin >> overdraft;
        bankAccounts.insert(new CheckingAccount(number, holder, initialBalance, overdraft));
        cout << "Account added successfully.\n";
    } else {
        cout << "Error: Invalid account type.\n";
    }
}

void Menu::deposit() {
    int index;
    double amount;
    cout << "Enter account index: ";
    cin >> index;
    if (index >= 0 && index < bankAccounts.getSize()) {
        cout << "Enter deposit amount: ";
        cin >> amount;
        bankAccounts[index]->deposit(amount);
        cout << *bankAccounts[index];
    } else {
        cout << "Error: Index out of range.\n";
    }
}

void Menu::withdraw() {
    int index;
    double amount;
    cout << "Enter account index: ";
    cin >> index;
    if (index >= 0 && index < bankAccounts.getSize()) {
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        bankAccounts[index]->withdraw(amount);
        cout << *bankAccounts[index];
    } else {
        cout << "Error: Index out of range.\n";
    }
}

void Menu::deleteAccount() {
    int index;
    cout << "Enter account index: ";
    cin >> index;
    if (index >= 0 && index < bankAccounts.getSize()) {
        delete bankAccounts.remove(index);
        cout << "Account deleted successfully.\n";
    } else {
        cout << "Error: Index out of range.\n";
    }
}

void Menu::printAccounts() {
    cout << "====== Account Details ======\n";
    for (int i = 0; i < bankAccounts.getSize(); ++i) {
        cout << "Array index " << i << ":\n";
        cout << *bankAccounts[i] << endl;
    }
}

void Menu::exitProgram() {
    for (int i = 0; i < bankAccounts.getSize(); ++i) {
        delete bankAccounts[i];
    }
    cout << "Exiting program...\n";
}
