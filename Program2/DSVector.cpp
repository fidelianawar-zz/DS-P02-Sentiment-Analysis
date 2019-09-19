#ifndef DSVECTOR
#define DSVECTOR

#include <iostream>
#include <cstring>
#include <DSVector.h>

template <typename T>
DSVector<T>::DSVector(){
    elements = nullptr;
}

template <typename T>
DSVector<T>::~DSVector(){
    if(elements){
        delete elements;
    }
}

template <typename T>
int DSVector<int>::getSize(){
    return elements.size();
}

template <typename T>
// append copy of passed element
void DSVector<T>::push(T const& elem) {
   elements.push_back(elem);
}

template <typename T>
T DSVector<T>::printVector(){

}

template <typename T>
int DSVector<T>::pop(){
   if (elements.empty()) {
      return 0;
   }
   // remove last element
   elements.pop_back();
   return 1;
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
