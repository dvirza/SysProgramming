#ifndef STACK_H
#define STACK_H

#include "StackNode.h"
#include <iostream> // Ensure inclusion of the iostream header
using namespace std;


class Stack {
private:
    StackNode* top;
public:
    Stack(); 
    ~Stack();
    void push(int data);
    void pop();
    bool isEmpty() const;
    int peek() const;
    friend Stack operator+(const Stack& s1, const Stack& s2);
    friend ostream& operator<<(ostream& os, const Stack& stack);
};

#endif
