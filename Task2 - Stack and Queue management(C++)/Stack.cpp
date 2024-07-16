/* Assignment C++: 1
   Author: Dvir Zaguri, ID: 315602284
           Ben Haimoff, ID: 206563660

                    This program was written by us and only by us.
Every attempt to copy the code or part of it, will consider as theft and will handle accordingly
*/ 

#include "Stack.h"
#include <climits>

Stack::Stack() : top(NULL) {} // choosing default constructor 

Stack::~Stack() {             // and distructor
    while (!isEmpty()) pop();
}

void Stack::push(int data) { 
    /* Push function: receives data by value and initiating a new stack node, declare its data
    as the value (from argument) and updating top of stack by using a pointer to it */
    StackNode* newNode = new StackNode(data);
    newNode->next = top;
    top = newNode;
}

void Stack::pop() {
    /* Pop function: If stack is not empty, the function defining a pointer to current top, declaring the next 
    node as TOS and releasing current TOS */
    if (isEmpty()) {
        cout << "Stack is empty" << endl;
        return;
    }
    StackNode* temp = top;
    top = top->next;
    delete temp;
}

bool Stack::isEmpty() const {
    // Is Empty function: returns top of stack status, is it a NULL ? 
    return top == NULL;
}

int Stack::peek() const {
    // peek function: if the stack is empty returns INT_MIN, else return TOS.
    if (isEmpty()) return INT_MIN;
    return top->data;
}

Stack operator+(const Stack& s1, const Stack& s2) {

    /* '+' Operator Overload: 
    1.Create a new stack object
    2.pointing 'current' to operand 1 TOS
    3.while operand 1 ->next != NULL (not empty):
    push operand 1 nodes by the same order
    4.pointing 'current' to operand 2 TOS
    5.while operand 2 ->next != NULL:
    push operand 1 nodes by the same order 
    6.return the new stack with s2 above s1 
    
    denote: s1 and s2 sent by const ref as it gives the operator only minimal required access
    and returning the new variable as it happens in casual '+' objects operations. */

    Stack newStack;
    StackNode* current = s1.top;
    while (current) {
        newStack.push(current->data);
        current = current->next;
    }
    current = s2.top;
    while (current) {
        newStack.push(current->data);
        current = current->next;
    }
    return newStack;
}

ostream& operator<<(ostream& os, const Stack& stack) {

    /* '<<' Operator Overload:
    1.pointing operand TOS
    2.while there are next node initialized to currnt node:
    print its data and a " " char after it
    3.return the ostream object to allow chaining to allow its printing 
    
    denote: the stack is ofc received by const ref as there no allowance 
    for any change in the data but reading it. */

    StackNode* current = stack.top;
    while (current) {
        os << current->data << " ";
        current = current->next;
    }
    return os;
}