//
// Created by Varick Erickson 2/3/2021.
//

#ifndef CHUNKLIST_H
#define CHUNKLIST_H

#include <iostream>

using namespace std;

const int ARRAY_SIZE = 8;

// These error classes are done. No modifications are required.
// See ChunkList_driver.cpp for an example of how they are used.
class InvalidArrayLength : public std::exception {
public:
    string Msg() {
        return "Invalid array length used for constructor.";
    }
};

class IndexOutOfBounds : public std::exception {
public:
    string Msg() {
        return "Index is out of bounds";
    }
};

class IteratorOutOfBounds : public std::exception {
public:
    string Msg() {
        return "Iterator is out of bounds.  Nothing left to iterate over.";
    }
};

class EmptyList : public std::exception {
public:
    string Msg() {
        return "List is empty";
    }
};

// Put your pre/post conditions here.

template<class T>
class ChunkList {
public:
    // Constructors

    /*
    * Function:
    * The default constructor that creates an empty ChunkList.
    *
    * Precondition:
    * No preconditions needed to invoke this default constructor.
    *
    * Postcondition:
    * The function does not return anything. It initializes the head and tail to point to nullptr. It sets listLen and
    * numChunks to 0. These are used for bookkeeping. It finally "resets" the iterators used for GetNextItem() by
    * invoking ResetIterator().
    */
    ChunkList();

    /*
    * Function:
    * This is the second default constructor that creates a prefilled ChunkList.
    *
    * Precondition:
    * This function requires two parameters passed to function properly. It requires that an array of values be passed
    * as arr and the length of the array passed as arrLen.
    *
    * Postcondition:
    * The function does not return anything. It will however throw an exception if the length of the array passed is
    * equal to zero or less. Each array element passed through arr[] is appended into a newly created linked list.
    * Finally, it "resets" the iterator so that the head and tail properly point to the beginning and end of the new
    * linked list.
    */
    ChunkList(T arr[], int arrLen);

    // Deconstructor

    /*
    * Function:
    * This is the default destructor that deletes all nodes in a ChunkList.
    *
    * Precondition:
    * No preconditions needed to invoke this destructor.
    *
    * Postcondition:
    * The destructor does not return anything. The main job is to clean up and free memory by traversing through the
    * linked list and using delete to delete each node. It also resets the main private class variables.
    */
    ~ChunkList();

    // Add/remove elements

    /*
    * Function:
    * This functions "pushes" a value into the list.
    *
    * Precondition:
    * This function requires one parameter, referred to as value, passed to function properly.
    * This value will be appended into the list.
    *
    * Postcondition:
    * The function does not return anything nor will it throw an exception. Upon successful execution, this function
    * will "push" a value into the array of the last node. If the array of the last node has reached the maximum length
    * of ARRAY_SIZE, then the function will create a new node and pop it into the new node as the first element.
    * This function also keep track of the number of values popped into the list and the number of node created and
    * linked. These variables are referred to as iterNode and listLen.
    */
    void Append(T value);

    /*
    * Function:
    * This functions "pops" a value out of the list.
    *
    * Precondition:
    * This function requires one parameter, referred to as value, passed to function properly.
    * This value will be removed from the list. It also requires that the list not be empty.
    *
    * Postcondition:
    * The function throws an exception if the list is empty. Upon successful execution, this function
    * will "pop" a value out of the array that holds it. It will then shift the remaining array values upwards
    * preserving the order. Similarly, if a node is to be deleted, because it contains the value to be popped and no
    * other elements, the order of nodes after it are preserved.
    */
    void Remove(T value);

    // Stuff to find out about the ChunkList

    /*
    * Function:
    * This functions gets the length of ChunkList in terms of values.
    *
    * Precondition:
    * This function does not require any preconditions.
    *
    * Postcondition:
    * The function simply returns this->listLen from the object.
    */
    int GetLength();

    /*
    * Function:
    * This functions calculates the load factor of the ChunkList.
    *
    * Precondition:
    * This function does not require any preconditions.
    *
    * Postcondition:
    * The function throws an exception if the list is empty otherwise it returns a double using the following equation:
    * load factor = listLen/(total number of spots in the ChunkList).
    */
    double LoadFactor();

    /*
    * Function:
    * This functions checks if a value exists within the list.
    *
    * Precondition:
    * This function requires a parameter passed for the function to complete successfully. This should be the value to
    * check if the list contains it.
    *
    * Postcondition:
    * The function throws an exception if the list is empty otherwise it traverses through each node and each value in
    * values array. If the value is found, the function returns true otherwise it returns false.
    */
    bool Contains(T value);

    // Accessing elements

    /*
    * Function:
    * This functions gets the value stored at a specific position.
    *
    * Precondition:
    * This function requires a parameter passed for the function to complete successfully. This is an int denoting the
    * positions in which the function will remove from the list.
    *
    * Postcondition:
    * The function throws an exception if the list is empty otherwise it traverses through each node and each value in
    * values array until it reaches the i position after which it will return the value in that position. The function
    * will also throw an exception if the position, i, is out of boundary. That is if i is greater than the number of
    * values in the list (listLen) or a negative value.
    */
    T GetIndex(int i);

    /*
    * Function:
    * This functions prints out the linked list to aid in visualizing it graphically.
    *
    * Precondition:
    * This function does not require any preconditions.
    *
    * Postcondition:
    * The function does not throw exceptions. After successful execution, the function will print out to stdout basic
    * details of each node such as the length of the node, the number of chunks, the node position, and each value of
    * the values array
    */
    void PrintList();

    /*
    * Function:
    * This functions resets the node and array position for GetNextItem().
    *
    * Precondition:
    * This function does not require any preconditions.
    *
    * Postcondition:
    * After successful execution, this function will reset iterNode to the head and arrPos to 0. No exceptions are thrown
    * by this function.
    */
    void ResetIterator();

    /*
    * Function:
    * This functions gets the next value of the linked list.
    *
    * Precondition:
    * This function requires that iterNode and arrPos be properly initiated. This is done by calling ResetIterator()
    * or by the two constructors.
    *
    * Postcondition:
    * This function will throw "Iterator is out of bounds.  Nothing left to iterate over." exception if it has reached
    * the nullptr. Otherwise, it returns back the next value in the array while also jumping to the next node as
    * needed. This function also modifies the private class members iterNode and arrPos to keep track upon each call to
    * the function.
    */
    T GetNextItem();

    /*
    * Function:
    * This functions checks if the list is empty.
    *
    * Precondition:
    * This function does not require any preconditions.
    *
    * Postcondition:
    * After successful execution, this function will return true if the length of the list (listLen) is 0, otherwise it
    * will return false.
    */
    bool IsEmpty();
private:

    // Note we did not need to make this a template
    // since this struct is part of a template class.
    struct Node {
        Node* next;
        int len;
        T values[ARRAY_SIZE];
    };

    Node* head;
    Node* tail;

    // iterator
    Node* iterNode;     // What node are we currently on?
    int arrPos;         // Within the node, what element are we looking at?

    int listLen;        // Total elements
    int numChunks;      // Total chunks/nodes
};

#include "ChunkList.cpp"

#endif //CHUNKLIST_H
