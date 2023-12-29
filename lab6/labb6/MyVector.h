// MyVector template file
#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"
#include <iostream>

using namespace std;

template <typename T>
class MyVector
{

public:

    unsigned size()const;

    //Create a new MyVector
    MyVector();

    //MyVectror destructor
    ~MyVector();

    //myVector copyconstructor
    MyVector(const MyVector& other);

    //myVector operator assignment
    MyVector& operator =(const MyVector& other);

    //Add something to the back of a myVector
    void push_back(const T&);

    //Removes the last element
    void pop_back();

    //Returns the element on index
    T& operator[](unsigned i);

    const T& operator[](unsigned i)const;

    //Check if the myVector is empty
    bool empty()const;

    //Returns the first element
    T* begin();

    //Returns the last element
    T* end();

    //Resets the myVector
    void clear();


private:
    unsigned capacity;
    unsigned numberOfElements;
    T* storage;

};

template<typename T>
MyVector<T>::MyVector(){
    capacity = 1;
    numberOfElements = 0;
    storage = new T[capacity];
}

template<typename T>
MyVector<T>::~MyVector(){
   delete[] storage;
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other){
    delete[] storage;
    capacity = other.capacity;
    numberOfElements = other.numberOfElements;
    storage = new T[capacity];
    for(int i = 0; i < numberOfElements; i++){
        storage[i] = other.storage[i];
    }
}

template<typename T>
MyVector<T>& MyVector<T>::operator =(const MyVector& other){
    if(!(&other == this)){
        delete [] storage;
        capacity = other.capacity;
        storage = new T[capacity];
        numberOfElements = other.numberOfElements;
        for(int i = 0; i < numberOfElements; i++){
            storage[i] = other.storage[i];
        }
    }
    return *this;
}



template<typename T>
void MyVector<T>::push_back(const T& e){
    if(capacity > numberOfElements){
        storage[numberOfElements] = e;
    }
    else{
        capacity = 2 * capacity;
        T* temp = new T[capacity];
        for(int i = 0; i < numberOfElements; i++){
            temp[i] = storage[i];
        }
        temp[numberOfElements] = e;
        delete[] storage;
        storage = temp;
    }
    numberOfElements++;
}

template<typename T>
void MyVector<T>::pop_back(){
    if(numberOfElements > 0){
        numberOfElements--;
    }
    if(capacity/2 > numberOfElements){
        capacity = capacity/2;
        T* temp = new T[capacity];
        for(int i = 0; i < numberOfElements; i++){
            temp[i] = storage[i];
        }
        delete[] storage;
        storage = temp;
    }
}

template<typename T>
T& MyVector<T>::operator[](unsigned i){
        return storage[i];
}

template<typename T>
const T& MyVector<T>::operator[](unsigned i)const{
        return storage[i];
}

template<typename T>
bool MyVector<T>::empty()const{
    return numberOfElements == 0;
}

template<typename T>
void MyVector<T>::clear(){
    delete[] storage;
    capacity = 1;
    numberOfElements = 0;
    storage = new T[capacity];
}

template<typename T>
unsigned MyVector<T>::size()const{
    return numberOfElements;
}

template<typename T>
T* MyVector<T>::begin(){
    T temp = storage[0];
    return &temp;
}

template<typename T>
T* MyVector<T>::end(){
    T temp = storage[numberOfElements];
    return &temp;
}

#endif // MY_VECTOR_H
