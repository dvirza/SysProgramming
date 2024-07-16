/* Assignment C++: 2
   Author: Dvir Zaguri, ID: 315602284
		   Ben Haimoff, ID: 206563660
*/ 

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

template <typename T>
class Array {
public:
    Array();
    ~Array();
    void insert(T element);
    T remove(int index);
    int getSize() const;
    T& operator[](int index);
    template <typename U>
    friend ostream& operator<<(ostream& os, const Array<U>& array);

private:
    int size;
    T* elements;
};

template <typename T>
Array<T>::Array() : size(0), elements(nullptr) {}

template <typename T>
Array<T>::~Array() {
    delete[] elements;
}

template <typename T>
void Array<T>::insert(T element) {
    T* newElements = new T[size + 1];
    for (int i = 0; i < size; ++i) {
        newElements[i] = elements[i];
    }
    newElements[size] = element;
    delete[] elements;
    elements = newElements;
    ++size;
}

template <typename T>
T Array<T>::remove(int index) {
    T removedElement = elements[index];
    T* newElements = new T[size - 1];
    for (int i = 0, j = 0; i < size; ++i) {
        if (i != index) {
            newElements[j++] = elements[i];
        }
    }
    delete[] elements;
    elements = newElements;
    --size;
    return removedElement;
}

template <typename T>
int Array<T>::getSize() const {
    return size;
}

template <typename T>
T& Array<T>::operator[](int index) {
    return elements[index];
}

template <typename U>
ostream& operator<<(ostream& os, const Array<U>& array) {
    for (int i = 0; i < array.size; ++i) {
        os << *array.elements[i] << endl;
    }
    return os;
}

#endif
