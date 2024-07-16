#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <vector>
#include <iostream>
using namespace std;


class MyQueue {
private:
// queue class object is a integers vector type
    vector<int> queue;
    int maxQ;
public:
// function decleration as public 
    MyQueue(int maxQ);     
    bool enQueue(int val); 
    bool deQueue();
    bool isEmpty() const;
    int peek() const;
    friend ostream& operator<<(ostream& os, const MyQueue& queue);
};

#endif