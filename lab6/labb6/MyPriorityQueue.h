//MyPriorityQueue template

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyVector.h"
#include "MyException.h"


template <typename T, typename C>
class MyPriorityQueue
{
    MyVector<T> vector_array;
    C strictly_larger_operator;

public:
    //MyPriorityQueue constructor
    MyPriorityQueue();

    //MyPriorityQueue destructor
    ~MyPriorityQueue();

    //Insert a value into the queue
    void push(const T& t);

    //Get the top element of the queue
    T top()const;

    //Remove the element with the highest priority
    void pop();

    //Check if the queue is empty
    bool empty()const;

    //Returns the size of the queue
    unsigned size() const;

private:
    //Return the parent of a node
    int parent(int r);

    //Return the left child of a node
    int leftChild(int r);

    //Return the right child of a node
    int rightChild(int r);

    //Return the left sibling of a node
    int leftSibling(int r);

    //Return the right sibling of a node
    int rightSibling(int r);

    //Check if a node is a leaf
    bool isLeaf(int r);
};


template <typename T, typename C>
MyPriorityQueue<T,C>::MyPriorityQueue(){
}


template <typename T, typename C>
MyPriorityQueue<T,C>::~MyPriorityQueue(){
}


template <typename T, typename C>
void MyPriorityQueue<T,C>::push(const T& t){

    vector_array.push_back(t);
    bool done = false;
    int index = vector_array.size() - 1;
    while(!done){
        if(index > 0){
            if(strictly_larger_operator(vector_array[parent(index)], vector_array[index])){
                swap(vector_array[index], vector_array[parent(index)]);
                index = parent(index);
            }
            else{
                done = true;
            }
        }
        else{
            done = true;
        }
    }
}

template <typename T, typename C>
T MyPriorityQueue<T,C>::top()const{
    if(!vector_array.empty()){
        return vector_array[0];
    }
}

template <typename T, typename C>
void MyPriorityQueue<T,C>::pop(){
    bool done = false;
    int index = 0;
    swap(vector_array[0], vector_array[vector_array.size() - 1]);
    vector_array.pop_back();
    while(!done){
        done = true;
        if(!isLeaf(index)){
            if((strictly_larger_operator(vector_array[rightChild(index)], vector_array[leftChild(index)]))){
                if((strictly_larger_operator(vector_array[index], vector_array[leftChild(index)]))){
                    swap(vector_array[leftChild(index)], vector_array[index]);
                    index = leftChild(index);
                    done = false;
                }
            }
            else{
                if((strictly_larger_operator(vector_array[index], vector_array[rightChild(index)]) && rightChild(index) != false)){ //Could have only one child
                    swap(vector_array[rightChild(index)], vector_array[index]);
                    index = rightChild(index);
                    done = false;
                }
            }
        }
    }

}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::empty()const{
    return vector_array.empty();
}

template <typename T, typename C>
unsigned MyPriorityQueue<T,C>::size()const{
    return vector_array.size();
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::parent(int r){
    if(r != 0){
        return (r - 1)/2;
    }
    else{
        return false;
    }
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::leftChild(int r){
    if(2*r + 1 < vector_array.size()){
        return 2*r + 1;
    }
    else{
        return false;
    }
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::rightChild(int r){
    if(2*r + 2 < vector_array.size()){
        return 2*r + 2;
    }
    else{
        return false;
    }
}


template <typename T, typename C>
int MyPriorityQueue<T,C>::leftSibling(int r){
    if(r%2 == 0 && r != 0){
        return r - 1;
    }
    else{
        return false;
    }
}

template <typename T, typename C>
int MyPriorityQueue<T,C>::rightSibling(int r){
    if(r%2 != 0 && r + 1 < vector_array.size()){
        return r + 1;
    }
    else{
        return false;
    }
}

template <typename T, typename C>
bool MyPriorityQueue<T,C>::isLeaf(int r){
    return r >= (vector_array.size()/2) && r < vector_array.size();
}
#endif // MY_PRIORITY_QUEUE_H

