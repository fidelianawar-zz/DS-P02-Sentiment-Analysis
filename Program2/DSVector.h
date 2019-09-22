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

    void at(int i);

    int getSize();
    int getCapacity() const;

    DSVector<T>& operator=(DSVector x);
    bool empty();//return true if empty

    void push_back(T const&);
    void pop_back();

    bool binarySearch(T variableElement);
    void quickSort(DSVector<T> a, int b, int c);
    void clear();

    T insert(T obj);
    T* printVector();


};

#endif // TEMPLATEVECTOR_H

