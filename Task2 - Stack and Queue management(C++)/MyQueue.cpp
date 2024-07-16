/* Assignment C++: 1
   Author: Dvir Zaguri, ID: 315602284
           Ben Haimoff, ID: 206563660

                    This program was written by us and only by us.
Every attempt to copy the code or part of it, will consider as theft and will handle accordingly
*/

#include "MyQueue.h"

MyQueue::MyQueue(int maxQ) : maxQ(maxQ) {}

bool MyQueue::enQueue(int val) {

/*       emQueue function: if the Queue length isnt at a maximal length, 
            push to the end of the queue element with value 'val'            */

    if (queue.size() < maxQ) {
        queue.push_back(val);
        return true;
    }
    return false;
}

bool MyQueue::deQueue() {
/*      deQueue function: if the queue isnt empty, erase the first object in the queue.
            return true if the queue wasnt empty before dequeue, else return false      */
    if (!isEmpty()) {
        queue.erase(queue.begin());
        return true;
    }
    return false;
}

bool MyQueue::isEmpty() const { 
// std::vector function on a queue, empty is a inlibrary function that checks if the queue vector is empty
    return queue.empty(); 
}

int MyQueue::peek() const {
    /*               peek function: return the first in queue object 'front' 
                    using built in vector library 'front' method.           */
    if (isEmpty()) return -1;
    return queue.front();
}

ostream& operator<<(ostream& os, const MyQueue& queue) {
    /* '<<' operator overload:
    returns all the objects in the queue, 
    chain them together with a " " between each 2 of them and return
    the resul as a ostream value */
    for (int val : queue.queue) {
        os << val << " ";
    }
    return os;
}