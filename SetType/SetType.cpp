#include <string>
#include <iostream>
#include "SetType.h"

using namespace std;

template<class T>
SetType<T>::SetType() {
    // Create an array of forward_lists and initially set to an empty forward_list
    this->buckets = new forward_list<T>[DEFAULT_BUCKETS];

    // Point the iterator to the first bucket
    this->currBucket = 0;
    this->bucketIter = this->buckets[this->currBucket].begin();

    this->iterCount = 0;
    // Set the maxLoad to the default load factor
    SetMaxLoad(DEFAULT_LOAD_FACTOR);
    this->numBuckets = DEFAULT_BUCKETS;
    // Set the number of elements to 0
    this->numElems = 0;
}

template<class T>
SetType<T>::SetType(SetType &otherSet) {
    copySet(otherSet);
}

template<class T>
SetType<T>::~SetType() {
    delete [] this->buckets;
}


template<class T>
SetType<T> SetType<T>::operator+(T elem) {
    SetType<T> result;

    // The result is this set
    result = *this;
    // Find and remove the element from the set
    result.Add(elem);

    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(T elem) {
    SetType<T> result;

    // The result is this set
    result = *this;
    // Find and remove the element from the set
    result.Remove(elem);

    return result;
}

template<class T>
SetType<T> SetType<T>::operator+(SetType& otherSet) {
    SetType<T> result;

    // Reset the iterator for the for-loop
    ResetIterator();

    // Concat first set (this) into result set
    for (int i = 0; i < Size(); i++){
        // Get element
        T nextElem = GetNextItem();
        // Concat it
        result.Add(nextElem);
    }

    // Reset the iterator for the for-loop
    otherSet.ResetIterator();

    // Concat second set (otherSet) into result set
    for (int i = 0; i < otherSet.Size(); i++){
        // Get element

        T nextElem = otherSet.GetNextItem();

        // Concat it
        result.Add(nextElem);
    }

    return result;
}

template<class T>
SetType<T> SetType<T>::operator*(SetType& otherSet) {
    SetType<T> result;

    // Reset the iterator for the for-loop
    ResetIterator();

    for (int i = 0; i < Size(); i++){
        // Get element for comparison
        T nextElem = GetNextItem();

        // If the other set contains the element, then add it into the result set
        if (otherSet.Contains(nextElem)){
            result.Add(nextElem);
        }
    }

    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(SetType& otherSet) {
    SetType<T> result;

    // Reset the iterator for the for-loop
    ResetIterator();

    for (int i = 0; i < Size(); i++){
        // Get element for comparison
        T nextElem = GetNextItem();

        // If the other set does not contain the element, then add it into the result set
        if (!otherSet.Contains(nextElem)){
            result.Add(nextElem);
        }
    }

    return result;
}

template<class T>
T SetType<T>::GetNextItem() {

    if (this->iterCount == this->numElems)
        throw IteratorOutOfBounds();

    // Returns the current item and then move to the next item
    T item;

    // Find the first bucket that actually has something in it
    // while bucketIter is at end
    while (this->bucketIter == this->buckets[this->currBucket].end()){
        // set bucketIter to the next bucket and increment currBucket
        ++this->currBucket;
        this->bucketIter = this->buckets[this->currBucket].begin();

    }

    // Access the element through the iterator
    item = *this->bucketIter;

    // Bookkeeping
    ++this->iterCount;
    ++this->bucketIter;

    return item;
}

template<class T>
int SetType<T>::GetHashIndex(const T& key) {
    // This is done... No touching!
    unordered_map<T,T> mapper;
    typename unordered_map<T,T>::hasher hashFunction = mapper.hash_function();
    return static_cast<int>(hashFunction(key) % this->numBuckets);
}


template<class T>
void SetType<T>::SetMaxLoad(double max) {
    // This function is done
    if (max < 0.1)
        this->maxLoad = 0.1;
    else
        this->maxLoad = max;
}

template<class T>
SetType<T>& SetType<T>::operator=(SetType const &other) {

    if (this != &other)
        copySet(other);

    return *this;
}


template<class T>
void SetType<T>::Rehash(int newNumBuckets) {
    // Start with an empty set with the appropriate number of buckets
    SetType<T> rehashedSet(newNumBuckets);

    // Use the iterator to add all the elements from this to the rehashSet
    // But first, lets reset the iterator just in case
    ResetIterator();
    for (int i = 0; i < Size(); i++){
        rehashedSet.Add(GetNextItem());
    }

    *this = rehashedSet;
}

template<class T>
SetType<T>::SetType(int numBucks) {
    // This constructor should uses the numBucks to create the buckets
    this->buckets = new forward_list<T>[numBucks];

    // Point the iterator to the first bucket
    this->currBucket = 0;
    this->bucketIter = this->buckets[this->currBucket].begin();
    this->iterCount = 0;
    // Set the maxLoad to the default load factor
    SetMaxLoad(DEFAULT_LOAD_FACTOR);
    this->numBuckets = numBucks;
    // Set the number of elements to 0
    this->numElems = 0;
}

template<class T>
void SetType<T>::Add(T elem) {
    // If elem already exists in the list, then the set should not change.
    if (Contains(elem))
        return;

    // Figure out what bucket elem should be placed in
    int bucket = GetHashIndex(elem);

    // elem should be pushed to the front of the forward_list
    this->buckets[bucket].push_front(elem);

    //Bookkeeping
    ++this->numElems;

    // If the load factor is above the maxLoad, then the number of buckets needs to be doubled and Rehash should be
    // called.
    if (LoadFactor() > this->maxLoad)
        Rehash(this->numBuckets * 2);
}

template<class T>
void SetType<T>::Remove(T elem) {
    // If elem does not exist in the list, then the set should not change.
    if (Contains(elem)){
        // This function should use the GetHashIndex to figure out what bucket elem exists
        int bucket = GetHashIndex(elem);
        // Remove elem from the forward list.
        this->buckets[bucket].remove(elem);
        // Bookkeeping
        --this->numElems;
    }
}

template<class T>
bool SetType<T>::Contains(T elem) {
    int bucket = GetHashIndex(elem);

    typename forward_list<T>::iterator itr;

    for(itr = this->buckets[bucket].begin(); itr != this->buckets[bucket].end(); ++itr)
        if (*itr == elem)
            return true;

    // If elem isn't found, then return false
    return false;
}

template<class T>
void SetType<T>::MakeEmpty() {
    // This is done by clearing each bucket. Hint: Loop over the buckets.
    for (int i = 0; i < this->numBuckets; ++i)
        this->buckets[i].clear();

    // Reset number of elements
    this->numElems = 0;
}

template<class T>
double SetType<T>::LoadFactor() const {
    // This is total number of elements in the set divided by the total number of buckets.
    return (double)this->numElems / this->numBuckets;
}

template<class T>
void SetType<T>::ResetIterator() {
    // It should also set currBucket and iterCount appropriately.
    this->currBucket = 0;
    this->iterCount = 0;

    // Point the iterator to the beginning of the first bucket
    this->bucketIter = this->buckets[this->currBucket].begin();

}

template<class T>
void SetType<T>::copySet(const SetType &otherSet) {
    // The function should also copy over the appropriate private variables from otherSet to this.
    this->bucketIter = otherSet.bucketIter;
    this->currBucket = otherSet.currBucket;
    this->iterCount = otherSet.iterCount;
    // Set the maxLoad to the default load factor
    SetMaxLoad(otherSet.maxLoad);
    // Be sure that the number of buckets match.
    this->numBuckets = otherSet.numBuckets;
    // Use the public function Size() to get the private variable numElems
    this->numElems = otherSet.Size();

    // You will need to delete buckets and reallocate the correct number of buckets similar how you allocated the
    // buckets for the constructor.
    delete [] this->buckets;
    this->buckets = new forward_list<T>[this->numBuckets];

    // Be also sure to make this empty before copying the elements from otherSet
    MakeEmpty();

    // You will need to loop through each bucket and all the items within each bucket.
    for(int buckit = 0; buckit < otherSet.numBuckets; ++buckit){
        for (typename forward_list<T>::iterator item = otherSet.buckets[buckit].begin(); item != otherSet.buckets[buckit].end(); ++item){
            this->buckets[buckit].push_front(*item);
            // Bookkeeping
            ++this->numElems;
        }
    }

    // Reset Iterator
    ResetIterator();

}


