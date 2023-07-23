//
// Your code here
//

#include "ChunkList.h"

template <class T>
ChunkList<T>::ChunkList()
{
    // The basics
    this->head = nullptr;
    this->tail = nullptr;
    this->listLen = 0;
    this->numChunks = 0;
    ResetIterator();
}

template <class T>
ChunkList<T>::ChunkList(T arr[], int arrLen){
    //  If arrLen is an invalid array length, you should throw a InvalidArrayLength ()
    if (arrLen <= 0)
        throw InvalidArrayLength();

    // The basics
    this->head = nullptr;
    this->tail = nullptr;
    this->listLen = 0;
    this->numChunks = 0;

    for (int i = 0; i < arrLen; i++)
        Append(arr[i]);

    ResetIterator();
}

template <class T>
ChunkList<T>::~ChunkList(){
    Node* currNode = this->head;

    // Traverse through every node and delete them
    while (currNode != nullptr){
        Node* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }

    // Back to the basics
    this->head = nullptr;
    this->tail = nullptr;
    this->iterNode = nullptr;
    this->arrPos = 0;
    this->listLen = 0;
    this->numChunks = 0;
}

template<class T>
void ChunkList<T>::Append(T value){
    if (this->head == nullptr or (this->listLen % ARRAY_SIZE) == 0 ) {
        // Create a new node and place the value into it.
        Node *newNode = new Node;
        // Append value onto the first element of the array
        newNode->values[0] = value;
        // Bookkeeping
        newNode->next = nullptr;
        newNode->len = 1;
        this->listLen++;
        this->numChunks++;

        if (this->head == nullptr) {
            // The current node is the first and last one
            this->head = newNode;
            this->tail = newNode;
        } else {
            // Update the pointer to the next node accordingly
            this->tail->next = newNode;
            this->tail = this->tail->next;
        }

    } else {
        // The last node has space in values[ARRAY_SIZE]
        // Insert value into the array of the last node.
        this->tail->values[this->tail->len] = value;
        // Bookkeeping
        this->tail->len++;
        this->listLen++;
    }
}

template<class T>
void ChunkList<T>::Remove(T value){
    // Trying to remove something from an empty list? Not happening.
    if (IsEmpty())
        throw EmptyList();

    Node* currNode = this->head;
    Node* prevNode = nullptr;

    while (currNode != nullptr){
        for (int i = 0; i < currNode->len; i++)
        {
            if (currNode->values[i] == value)
            {
                // Delete the node if the node containing the value has a values array length of 1 and is the
                // first node (head)
                if (currNode == this->head and currNode->len == 1){
                    if (this->head != nullptr){
                        Node* temp = this->head;
                        this->head = this->head->next;
                        free(temp);
                    }

                    // Bookkeeping
                    this->listLen--;
                    this->numChunks--;
                    return;
                }
                // Delete the node in between the head and tail only if the one and only element in the values array
                // matches, the length of values array must be 1
                if (currNode != this->head and currNode != this->tail and currNode->len == 1)
                {
                    prevNode->next = currNode->next;
                    free(currNode);

                    //Bookkeeping
                    this->listLen--;
                    this->numChunks--;
                    return;
                }

                // Delete the node if the node containing the value has a values array length of 1 and is the
                // last node (tail)
                if (currNode == this->tail and currNode->len == 1){
                    if (this->head != nullptr)
                    {
                        // If the last node happens to be the first node (head), delete it and point the head to NULL
                        if (this->head->next == nullptr){
                            // Bookkeeping
                            this->listLen--;
                            this->numChunks--;

                            this->head = nullptr;
                            return;
                        } else {
                            // Else traverse to the second to last node, hence temp->next->next.
                            Node* temp = this->head;
                            while (temp->next->next != nullptr){
                                temp = temp->next;
                            }
                            // Make a copy of the second to last node
                            Node* lastNode = temp->next;
                            // Assign next of the second to last node to point to null
                            temp->next = nullptr;
                            // Delete the last node
                            free(lastNode);
                            //Bookkeeping
                            this->listLen--;
                            this->numChunks--;
                            return;
                        }
                    }

                }

                // If the element holding the value to be deleted is not the last element of the array,
                // then delete it and shift everything up to preserve the order of the list
                if (i != (currNode->len - 1)){
                    for (int j = i; j < currNode->len; j++)
                    {
                        currNode->values[j] = currNode->values[j + 1];
                    }
                    // Null out the last element because we removed one value and shifted everything up
                    currNode->values[currNode->len - 1] = '\0';
                    // Bookkeeping
                    this->listLen--;
                    currNode->len--;

                    // This function should find the first instance of value and remove it
                    return;
                }

                // Null the value if it's the last element of the array but only if other elements exist in the array.
                if (i == (currNode->len - 1) and currNode->len != 1){
                    currNode->values[currNode->len - 1] = '\0';
                    // Bookkeeping
                    this->listLen--;
                    currNode->len--;

                    // This function should find the first instance of value and remove it
                    return;
                }
            }
        }
        prevNode = currNode;
        currNode = currNode->next;
    }
}

template<class T>
int ChunkList<T>::GetLength(){
    return this->listLen;
}

template<class T>
double ChunkList<T>::LoadFactor(){
    if (IsEmpty())
        throw EmptyList();
    return ((double)this->listLen / double(ARRAY_SIZE * this->numChunks));
}

template<class T>
bool ChunkList<T>::Contains(T value){
    if (IsEmpty())
        throw EmptyList();

    // Start at head and go to tail
    Node* currNode = this->head;

    while(currNode != nullptr)
    {
        // Traverse all values in the chunk/currNode
        for (int i = 0; i < currNode->len; i++){
            if (currNode->values[i] == value){
                return true;
            }
        }

        // Move along
        currNode = currNode->next;
    }
    // Return false by default
    return false;
}


template<class T>
T ChunkList<T>::GetIndex(int i){
    // This function should throw an EmptyList() error if the list is empty
    if (IsEmpty())
        throw EmptyList();

    // It should also throw an IndexOutOfBounds() error if you provide a bad index
    if (i > this->listLen || i < 0)
        throw IndexOutOfBounds();

    Node* currNode = this->head;
    while (currNode != nullptr){
        if (i < currNode->len){
            return currNode->values[i];
        }
        i = i - currNode->len;
        currNode = currNode->next;
    }
    // We should never reach this point. But if we do, then return something.
    return 0;
}

template<class T>
void ChunkList<T>::PrintList(){
    Node* currNode = this->head;
    int node_count = 0;
    while(currNode != nullptr)
    {
        cout << "Node# " << node_count << " (len: " << currNode->len << ")" << endl;
        for (int i = 0; i < currNode->len; i++){
            cout << "[" << i << "] = " << currNode->values[i] << endl;
        }
        currNode = currNode->next;
        node_count++;
    }
    cout << "this->listLen = " << this->listLen << endl;
    cout << "this->numChunks = " << this->numChunks << endl << endl << endl;
}

template<class T>
void ChunkList<T>::ResetIterator(){
    this->iterNode = this->head;
    this->arrPos = 0;
}

template<class T>
T ChunkList<T>::GetNextItem(){
    // Check if it is out of bound
    if (this->iterNode == nullptr)
        throw IteratorOutOfBounds();

    // Make a copy of the current iterNode and array position
    Node* copyNode = this->iterNode;
    int tempPos = this->arrPos;

    // If the array position is within the bounds of the values array, then return the value
    if (tempPos < copyNode->len) {
        // Bookkeeping
        this->arrPos++;
        // We use tempPos because we have return here but also need to increment arrPos and that wouldn't be possible
        // without incrementing before returning.
        return copyNode->values[tempPos];
    }else{
        // If arrPos is greater than the length of the values array, set it to 1 because we will return the 0 position
        // here and position 1 will be used for the next time GetNextItem() is called.
        this->arrPos = 1;

        // Reset the index position used to return to 0
        tempPos = 0;

        // Move forward onto the next node but check if it's NULL
        if (this->iterNode->next != nullptr)
            this->iterNode = this->iterNode->next;
        else
            throw IteratorOutOfBounds();

        return this->iterNode->values[tempPos];
    }
}

template<class T>
bool ChunkList<T>::IsEmpty(){
    return (this->listLen == 0);
}
