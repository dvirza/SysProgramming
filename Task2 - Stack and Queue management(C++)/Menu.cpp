/* Assignment C++: 1
   Author: Dvir Zaguri, ID: 315602284
           Ben Haimoff, ID: 206563660

                    This program was written by us and only by us.
Every attempt to copy the code or part of it, will consider as theft and will handle accordingly
*/ 

#include "Menu.h"
#include <iostream>

using namespace std;

Menu::Menu() : queue(10) {}

void Menu::mainMenu() { // Starting Main Menu FLOW:
    int choice;
    do {
        cout << "Main Menu:\n1. Stack Menu\n2. Queue Menu\n3. Exit\n";
        cin >> choice;
        switch (choice) { // Menu Navigation
            case 1:
            stackMenu(); // Navigate to stack menu
            break;

            case 2:
            queueMenu(); // Navigate to Queue menu
            break;

            case 3:
            cout << "Goodbye\n"; // Quit program
            break;

            default: // For every input other than 1/2/3
            cout << "Invalid choice\n";
        }
    } while (choice != 3);
}

void Menu::stackMenu() { // Stack Management Options 
    int choice, value;
    do {
        cout << "Stack Menu:\n1. Push\n2. Pop\n3. IsEmpty\n4. Peek\n5. Print Stack\n6. Exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
            cout << "Enter value to push: ";
            cin >> value;
            stack.push(value); // Push value by value to stack node data
            break;

            case 2:
            stack.pop(); //  Remove TOS and redefine TOS in linked list.
            break;

            case 3:
            cout << (stack.isEmpty() ? "Stack is empty" : "Stack is not empty") << endl; // Is there are pushed things that never popped?
            break;

            case 4:
            cout << "Top element: " << stack.peek() << endl; // If stack is not empty return TOS, else return INT_MIN 
            break;

            case 5:
            cout << stack << endl; // Print stack
            break;

            default:
            cout << "Invalid choice\n";
        }
    } while (choice != 6);
}

void Menu::queueMenu() { // Queue Management Options
    int choice, value;
    do {
        cout << "Queue Menu:\n1. EnQueue\n2. DeQueue\n3. IsEmpty\n4. Peek\n5. Print Queue\n6. Exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value to enqueue: "; // Insert new element at the end of the queue
                cin >> value; // Enter value for the element
                if (!queue.enQueue(value)) {
/*              enQueue() returns 'true' after successful insertion, else returns 'false', 
                print a feedback to the user for unsuccesfull insertion                             */
                    cout << "Queue is full\n"; 
                }
                break;
            case 2:
                if (!queue.deQueue()) {
/*              deQueue() returns 'true' after successful removing element from queue,  
                else returns 'false', print a feedback to the user for unsuccesfull removing        */
                    cout << "Queue is empty\n";
                }
            break;

            case 3:
            //if queue function executed on current queue to check if it empty and print relevant string
                cout << (queue.isEmpty() ? "Queue is empty" : "Queue is not empty") << endl;
            break;

            case 4:
            // prints the first element in the queue
                cout << "Front element: " << queue.peek() << endl;
            break;

            default:
            cout << "Invalid choice\n";
        }
    } while (choice != 6);
}
