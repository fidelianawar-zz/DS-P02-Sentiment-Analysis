#ifndef TEMPLATEVECTOR_H
#define TEMPLATEVECTOR_H

#include <iostream>
#include <cstring>

template <typename T>

class DSVector{
private:
    DSVector<T> elements;
    int vectorSize;
    int capacity;
    T* buffer;

public:



    DSVector();
    ~DSVector();

    int getSize();
    int getCapacity() const;

    DSVector<T>& operator=(DSVector x);
    bool empty();//return true if empty

    void push(T const&);
    void pop_back();

    int getCapacity();

    T insert(T obj);
    T top() const; //return top element
    T* printVector();


};

#endif // TEMPLATEVECTOR_H

