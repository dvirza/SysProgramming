#ifndef MENU_H
#define MENU_H

#include "Stack.h"
#include "MyQueue.h"

class Menu {
private:
    Stack stack;
    MyQueue queue;
public:
    Menu();
    void mainMenu();
    void stackMenu();
    void queueMenu();
};

#endif
