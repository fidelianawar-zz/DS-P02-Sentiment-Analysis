#ifndef TEMPLATEVECTOR_H
#define TEMPLATEVECTOR_H

#include <iostream>
#include <cstring>

template <typename T>

class DSVector{
private:
    DSVector<T> elements;

public:
    DSVector();
    ~DSVector();

    void push(T const&);
    int pop();
    int getSize();
    int getCapacity();

    T insert(T obj);
    T top() const; //return top element
    T printVector();

    bool empty() const; //return true if empty

};

#endif // TEMPLATEVECTOR_H

