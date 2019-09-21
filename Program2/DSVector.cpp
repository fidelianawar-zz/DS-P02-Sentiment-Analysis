#ifndef DSVECTOR
#define DSVECTOR

#include <iostream>
#include <cstring>
#include <DSVector.h>

template<class T>
DSVector<T>::DSVector() {
    elements = nullptr;
    capacity = 0;
    vectorSize = 0;
    buffer = 0;
}

template <typename T>
DSVector<T>::~DSVector(){
    if(elements){
        delete elements;
    }
}

template <typename T>
int DSVector<T>::getSize(){
    return elements.size();
}

template<class T>
int DSVector<T>::getCapacity() const {
    return capacity;
}

// Assignment operator
template <typename T>
DSVector<T>& DSVector<T>::operator=(DSVector<T> other){
    swap(*this,other);
    return *this;
}

template <typename T>
// append copy of passed element
void DSVector<T>::push(T const& elem) {
    elements.push_back(elem);
}

template <typename T>
bool DSVector<T>::empty(){
    return elements.getSize()==0;
}


template <typename T>
T* DSVector<T>::printVector(){
    return elements;
}

template<typename T>
void DSVector<T>::pop_back() {
    if (vectorSize > 0)
        vectorSize--;
}

template <typename T>
T DSVector<T>::top () const {
    if (elements.empty()) {
        //throw out_of_range("Stack<>::top(): empty stack");
    }

    // return copy of last element
    return elements.back();
}

#endif
