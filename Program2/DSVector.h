#ifndef TEMPLATEVECTOR_H
#define TEMPLATEVECTOR_H

#include <iostream>
#include <cstring>
#include <DSString.h>

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

    DSVector<T>& operator=(DSVector x);
    bool empty();//return true if empty

    void push_back(T const&);
    void deleteRepeated();
    void pop_back();

    bool binarySearch(T variableElement);
    void quickSort(int b, int c);
    void clear();

    T insert(T obj);
    T* printVector();


};

template<typename T>
DSVector<T>::DSVector() {
    capacity = 0;
    elements = new T[capacity];
    vectorSize = 0;
}
template <typename T>
DSVector<T>::~DSVector(){
    delete[] elements;
}

template <typename T>
int DSVector<T>::getSize(){
    return vectorSize;
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
bool DSVector<T>::empty(){
    return vectorSize==0;
}

template <typename T>
// append copy of passed element
void DSVector<T>::push_back(T const& elem) {
    if(vectorSize >= capacity){
        capacity += 10;
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

template <typename T>
T DSVector<T>::at(int index){
    if(index < 0 || index >= vectorSize){
        cerr << "not a valid index to access";
        exit(1);
    }
    return elements[index];
}

template <typename T>
// delete repeated elements
void DSVector<T>::deleteRepeated() {
    T* temp = new T[capacity];
    int counter = 0;
    int counter_size = 0;
    for(int i = 0; i < vectorSize; i++){
        if(!(elements[i] == elements[i+1])){
            temp[counter] = elements[i];
            counter++;
            counter_size++;
        }
    }
    delete [] elements;
    elements = temp;
    vectorSize = counter_size;

}

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

template <typename T>
bool DSVector<T>::binarySearch(T var){
    int low = 0;
    int high = vectorSize;

    while(low <= high){

        int middleIndex = (high - low)/2;

        if(elements[middleIndex] == var){
            return elements[middleIndex];
            return true;
        }

        elseif(elements[middleIndex] > var);{
            high = middleIndex - 1;
        }

        elseif(elements[middleIndex] < var);{
            low = middleIndex + 1;
        }
    }
    return false;
}

template <typename T>
T* DSVector<T>::printVector(){
    for(int i = 0; i < vectorSize; i++){
        cout << elements[i] << " ";
    }
    cout << endl;
}

template<typename T>
void DSVector<T>::pop_back() {
    if (vectorSize > 0)
        vectorSize--;
}

#endif // TEMPLATEVECTOR_H

