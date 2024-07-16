#ifndef STACKNODE_H
#define STACKNODE_H

#include <iostream> 
class Stack;

class StackNode {
private:
    int data;
    StackNode* next;
public:
    StackNode(int data);
    friend class Stack;
    friend Stack operator+(const Stack& s1, const Stack& s2); //granting access to Stack class
    friend std::ostream& operator<<(std::ostream& os, const Stack& stack); //
};

#endif
