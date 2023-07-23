#ifndef SET_TYPE
#define SET_TYPE

#include<string>
#include<iostream>
#include<forward_list>
#include<unordered_map>
using namespace std;

class IteratorOutOfBounds : exception {
public:
    string Msg() {
        return "Iterator is out of bounds.  Nothing left to iterate over.";
    }
};

const int DEFAULT_BUCKETS = 10;
const double DEFAULT_LOAD_FACTOR = 1.0;

template<class T>
class SetType
{
public:
    // Constructors

    /*
    * Function:
    * The default constructor that creates an empty SetType with the default number of buckets.
    *
    * Precondition:
    * No preconditions needed to invoke this default constructor.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions.
    * The default constructor creates an array of buckets using DEFAULT_BUCKETS as the length of the array
    * and sets the number of elements (numElems) to 0 along with currBucket and iterCount.
    * It also sets the maxLoad to the default load factor (DEFAULT_LOAD_FACTOR) as well as numBuckets to DEFAULT_BUCKETS.
    * Lastly, the iterator (bucketIter) is pointed to the beginning of the first bucket.
    */
    SetType();

    /*
    * Function:
    * The explicit default constructor that creates an empty SetType with a custom number of buckets.
    *
    * Precondition:
    * The number of buckets represented as an integer is required.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions.
    * This explicit constructor creates an array of buckets using numBucks as the length of the array
    * and sets the number of elements (numElems) to 0 along with currBucket and iterCount.
    * It also sets the maxLoad to the default load factor (DEFAULT_LOAD_FACTOR) as well as numBuckets to numBuckets.
    * Lastly, the iterator (bucketIter) is pointed to the beginning of the first bucket.
    */
    explicit SetType(int numBucks);

    /*
    * Function:
    * The second default constructor that creates a SetType by performing a deep copy of another SetType object.
    *
    * Precondition:
    * The reference of the other SetType object must be passed.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions.
    * This constructor merely calls copySet() to perform the deep copy to this object.
    */
    SetType(SetType& other);

    /*
    * Function:
    * The default destructor.
    *
    * Precondition:
    * No preconditions needed to invoke this destructor.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions.
    * This destructor deletes the entire array of buckets (this->buckets).
    */
    ~SetType();

    /*
    * Function:
    * Add an element into the array of buckets.
    *
    * Precondition:
    * The element to be inserted must be passed as elem.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions.
    * This function will add elem into the set if the set does not already contain the element. If the LoadFactor() is
    * greater than maxLoad, a rehash of the set will be performed and the number of buckets will be doubled.
    */
    void Add(T elem);

    /*
    * Function:
    * Remove an element from the array of buckets.
    *
    * Precondition:
    * The element to be removed must be passed as elem.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions.
    * This function will remove elem from the set if the set contains the element.
    */
    void Remove(T elem);

    /*
    * Function:
    * Check if an element exists in the array of buckets.
    *
    * Precondition:
    * The element to be removed must be passed as elem.
    *
    * Postcondition:
    * The function returns a boolean depending on the element's existence in the set. However, this function does not
    * throw exceptions.
    */
    bool Contains(T elem);

    /*
    * Function:
    * Remove all elements from each bucket in the set.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions.
    * Upon completion, the function iterates through each bucket and calls the forward_list clear() object.
    */
    void MakeEmpty();

    /*
    * Function:
    * Get the number of elements in the set.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function returns the number of elements (numElems) in the set as an integer. This function does not throw
    * exceptions.
    */
    int Size() const {
        return this->numElems;
    }

    /*
    * Function:
    * Get the load factor of the set.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function returns the load factor of the set as a double. The calculation is formulated as numElems/numBuckets.
    * This function does not throw exceptions.
    */
    double LoadFactor() const;

    /*
    * Function:
    * Set the maximum load factor of the set.
    *
    * Precondition:
    * The maximum load factor as a double must be passed as max.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions. The function set maxLoad to max as passed
    * except for when max is less than 0.1 where the function sets max to 0.1.
    */
    void SetMaxLoad(double max);

    /*
    * Function:
    * Rehash the current set to expand it.
    *
    * Precondition:
    * The new number of buckets to use when rehashing is required to be passed as newNumBuckets.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions. The function creates another set with the
    * specified number of buckets and then adds each element of the current set into it. Upon completion, the function
    * points the current set (*this) to the new rehashed set.
    */
    void Rehash(int newNumBuckets);

    /*
    * Function:
    * The += operator for an element. It's also considered to be the alternative way of adding an element into the set.
    *
    * Precondition:
    * The element to be added into the set must be passed as elem.
    *
    * Postcondition:
    * The function returns a SetType object but does not throw exceptions. The function returns the pointer to the
    * current object after calling Add() to add elem into the set.
    */
    SetType operator+(T elem);				      // Add

    /*
    * Function:
    * The -= operator for an element. It's also considered to be the alternative way of removing an element from a set.
    *
    * Precondition:
    * The element to be removed from the set must be passed as elem.
    *
    * Postcondition:
    * The function returns a SetType object but does not throw exceptions. The function returns the pointer to the
    * current object after calling Remove() to remove elem from the set.
    */
    SetType operator-(T elem);				      // Remove

    /*
    * Function:
    * The += operator for sets. It's also considered to be the alternative way of concatenating elements from one set to
    * the other.
    *
    * Precondition:
    * The set to be added must be passed as otherSet.
    *
    * Postcondition:
    * The function returns a SetType object but does not throw exceptions. The function returns the SetType object
    * after iterating through the current set (this) and otherSet to add all elements into one resulting set.
    */
    SetType operator+(SetType& otherSet);         // Union

    /*
    * Function:
    * The -= operator for sets. It's also considered to be the alternative way of differentiating the current
    * set (this) and the otherSet.
    *
    * Precondition:
    * The set to be differentiated must be passed as otherSet.
    *
    * Postcondition:
    * The function returns a SetType object but does not throw exceptions. The function returns the SetType object
    * after iterating through the otherSet checking if the otherSet does not contain the elements of this set. Those
    * elements are added into the resulting set.
    */
    SetType operator-(SetType& otherSet);         // Difference

    /*
    * Function:
    * The *= operator for sets. It's also considered to be the alternative way of intersecting the current set (this)
    * and the otherSet.
    *
    * Precondition:
    * The set to be intersected must be passed as otherSet.
    *
    * Postcondition:
    * The function returns a SetType object but does not throw exceptions. The function returns the SetType object
    * after iterating through the otherSet checking if the otherSet contains the elements of this set. Those
    * elements are added into the resulting set.
    */
    SetType operator*(SetType& otherSet);         // Intersection

    /*
    * Function:
    * The = operator for sets. It's also considered to be the alternative way of performing a deep copy of the
    * current set (this).
    *
    * Precondition:
    * The set to be copied onto this must be passed as otherSet.
    *
    * Postcondition:
    * The function returns a SetType object but does not throw exceptions. The function returns the SetType object
    * after calling copySet() if and only if the current set doesn't equal to the other set.
    */
    SetType& operator=(SetType const& otherSet);  // Assignment (does deep copy)

    /*
    * Function:
    * Reset the iterator.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions. Upon completion, the function set
    * currBucket and iterCount to 0. bucketIter is also set to point to the first element of the first bucket.
    */
    void ResetIterator();	// Reset iterator

    /*
    * Function:
    * Get the next element from the array of buckets.
    *
    * Precondition:
    * No preconditions needed to invoke this function.
    *
    * Postcondition:
    * The function returns the next item of the set. This function can also throw an
    * "Iterator is out of bounds.  Nothing left to iterate over." exception when calling this function once to many
    * times. ResetIterator() should be used to freshly iterate through the set.
    */
    T GetNextItem();

private:
    forward_list<T>* buckets;	// An array of forward_list's
                                // (each index is a forward_list)

    int numBuckets;     // total number of buckets

    /*
    * Function:
    * Get the index (bucket number) of where to add or remove an element from.
    *
    * Precondition:
    * The element in question is required to be passed as key.
    *
    * Postcondition:
    * The function returns an integer denoting the bucket where the key should reside in or which bucket it exists in.
    * This function not throw exceptions.
    */
    int GetHashIndex(const T& key);    // Gets the hash index given the elem

    int numElems;       // total number of elements

    double maxLoad;     // load factor of the Set

    // This function is used by the
    // copy constructor and the assignment operator.

    /*
    * Function:
    * The internal/private function responsible for performing the deep copy of otherSet onto this set.
    *
    * Precondition:
    * The set to be copied onto this is required to be passed as otherSet.
    *
    * Postcondition:
    * The function does not return anything nor does it throw exceptions. All private variables from the otherSet are
    * copied into this set including the elements. Before coping each element from the otherSet, this function
    * deleted the buckets array and reallocates a new array equal to the size of otherSet's.
    */
    void copySet(const SetType& otherSet);

    // Iterator variables
    int currBucket;											// What bucket is the iterator on?
    int iterCount;                                          // What element are we on?
    mutable typename forward_list<T>::iterator bucketIter;	// The iterator of the current bucket

    // Any other private functions and variables you want/need
};

#include "SetType.cpp"

#endif