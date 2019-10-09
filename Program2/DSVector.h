#ifndef TEMPLATEVECTOR_H
#define TEMPLATEVECTOR_H

#include <iostream>
#include <cstring>
#include <DSString.h>
#include <vector>

using namespace std;

template <typename T>
class DSVector{
private:
    T* elements;
    int vectorSize;
    int capacity;

public:
    DSVector();
    ~DSVector();

    T at(int i);

    int getSize();
    int getCapacity() const;

    DSVector<T>& operator=(DSVector<T> x);
    void deleteElements();
    bool empty();
    void push_back(T const&);
    void deleteRepeated();
    void pop_back();

    bool binarySearch(T variableElement);
    void quickSort(int b, int c);


    T insert(T obj);
    T* printVector();


};

template<typename T>
DSVector<T>::DSVector() {
    capacity = 10;
    elements = new T[capacity];
    vectorSize = 0;
}

//destrcutor
template <typename T>
DSVector<T>::~DSVector(){
    delete[] elements;
}

//obtain size of vector
template <typename T>
int DSVector<T>::getSize(){
    return vectorSize;
}

template<typename T>
int DSVector<T>::getCapacity() const {
    return capacity;
}

//delete contents of vector
template<typename T>
void DSVector<T>::deleteElements(){
    delete [] elements;
    capacity = 10;
    T* temp = new T[capacity];
    vectorSize = 0;
    elements = temp;
}

//equals operator for vector
template<typename T>
DSVector<T>& DSVector<T>::operator=(const DSVector<T> b)
{
    // Test for self-copy
    if(this != &b)
    {
        // If not a self-copy, implement the following
        vectorSize = b.vectorSize;
        capacity = b.capacity;
        delete [] elements;
        elements = new T[vectorSize];
        for(int i = 0; i < b.vectorSize;i++)
        {
            elements[i] = b.elements[i];
        }
    }
    return *this;
}


template <typename T>
bool DSVector<T>::empty(){
    return vectorSize==0;
}

//append copy of passed element to vector
template <typename T>
void DSVector<T>::push_back(T const& elem) {
    if(vectorSize >= capacity){

        //double capacity
        capacity *= 2;
        T* temp = new T[capacity];
        for(int i = 0; i < vectorSize; i++){
            temp[i] = elements[i];
        }
        delete [] elements;
        elements = temp;

    }
    elements[vectorSize] = elem;
    vectorSize++;
}

//access index of element in vector
template <typename T>
T DSVector<T>::at(int index){
    if(index < 0 || index >= vectorSize){
        cerr << "not a valid index to access";
        exit(1);
    }
    return elements[index];
}

// delete repeated elements
template <typename T>
void DSVector<T>::deleteRepeated() {
    T* temp = new T[capacity];
    int counter = 0;
    int counter_size = 0;

    for(int i = 0; i < vectorSize; i++){
        if(vectorSize == 1)
        {
            return;
            break;
        }
        if(i == vectorSize-1){
            if((elements[i] == elements[i-1]))
            {
                break;
                return;
            }
            else{
                temp[counter] = elements[i];
                counter_size++;
                break;
                return;
            }
        }
        if(!(elements[i] == elements[i+1])){
            temp[counter] = elements[i];
            counter++;
            counter_size++;
        }
        else if((elements[i] == elements[i+1])){
        }
    }
    delete [] elements;
    elements = temp;
    vectorSize = counter_size;

}

//quicksort elements of vector
template <typename T>
void DSVector<T>::quickSort(int left, int right) {
      int i = left, j = right;
      DSString temp;

      DSString pivot = elements[((left+right)/2)];

      while (i <= j) {
            while (elements[i] < pivot){
                  i++;
            }
            while (pivot < elements[j]){
                  j--;
            }
            if (i <= j) {
                  temp = elements[i];
                  elements[i] = elements[j];
                  elements[j] = temp;
                  i++;
                  j--;
            }
      }

      if (left < j)
            quickSort(left, j);
      if (i < right)
            quickSort(i, right);
}

//perform binary search on sorted vector
template <typename T>
bool DSVector<T>::binarySearch(T var){
    int low = 0;
    int high = vectorSize-1;

    while(low <= high){

        int middleIndex = (high + low)/2;

        if(elements[middleIndex] == var){
            return true;
        }

        else if(elements[middleIndex] > var){
            high = middleIndex - 1;
        }

        else if(elements[middleIndex] < var){
            low = middleIndex + 1;
        }
    }
    return false;
}

//print elements of vector
template <typename T>
T* DSVector<T>::printVector(){
    for(int i = 0; i < vectorSize; i++){
        cout << elements[i] << " ";
    }
    cout << endl;
}

//remove last element
template<typename T>
void DSVector<T>::pop_back() {
    if (vectorSize > 0)
        vectorSize--;
}

#endif // TEMPLATEVECTOR_H

