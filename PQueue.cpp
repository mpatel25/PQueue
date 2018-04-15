#include "PQueue.h"

// Constructor for Priority Queue
PQueue::PQueue(unsigned size){
    // The array needs to be 1 element greater than the heap because
    //      the 0th element is extra for easy indexing. Therefore 
    //      the head of the heap is at index 1 instad of 0. 
    heap = new Element*[size+1];
    heap[0] = NULL;
    maxHeapSize = size;
    currentArraySize = 1;
    enqueueCount = 0;
}

// Constructor for each individual element in the heap.
PQueue::Element::Element(char d_in, unsigned p_in, unsigned e_in):
                data(d_in), priority(p_in), entryStamp(e_in){}

// To insert new char into the heap
// d_in: new data
// p_in: new priority
bool PQueue::enqueue (char d_in, unsigned p_in){
    // If the heap is full return false
    if (currentArraySize == (maxHeapSize+1)) return false;
    // Insert new element at the end of the heap
    // Use enqueue count as the entry stamp
    heap[currentArraySize] = new Element(d_in, p_in, enqueueCount);
    currentArraySize++;
    enqueueCount++;
    // Move the new element up to right location, according to the priority
    moveUp();
    // If enqueue count is max value (2^32-1 for 4byte integers) then
    //      restamp all the elements
    if (enqueueCount == ((unsigned)0-(unsigned)1)) restampElements();
    return true;
}

// To remove the character with the highest priority in the queue
// Out is where the return value is stored
bool PQueue::dequeue (char& out){
    // If the heap is empty return false
    if (currentArraySize == 1) return false; 
    // Output the Character with the highest priority and the highest priority
    //      is at the head of the heap
    out = heap[1]->data;
    // Delete the head and replace with lowest leaf in the heap
    delete heap[1];
    heap[1] = heap[currentArraySize-1];
    heap[currentArraySize-1] = NULL;
    currentArraySize--;
    // Move the top element down to right location, according to the priority
    moveDown();
    // If the heap is empty reset the enqueue count (optimization)
    if (currentArraySize == 1) enqueueCount=0;
    return true;
}

// To swap two elements in the heap
void PQueue::elementSwap(unsigned a, unsigned b){
    Element* temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

// Operator overloading to compare two elements with '<'
bool PQueue::Element::operator< (Element right){
    // Compare priorities
    if (this->priority > right.priority) return false;
    // If priorities are the same then compare entry stamps
    if (this->priority == right.priority &&
        // The earlier timestamp is given higher priority
        this->entryStamp <= right.entryStamp) return false;
    return true;
}

// To shift the new element up after it is inserted 
//      as the last element in the heap
void PQueue::moveUp(){
    unsigned current = currentArraySize-1;
    unsigned parent = current >> 1;
    // Shift up until the priority of the parent element is greater
    //      or the new element is at the top of the heap
    while(current > 1 && *heap[parent] < *heap[current]){
        elementSwap(parent, current);
        current = parent;
        parent >>= 1;
    }
}

// To shift down the last element after it moved to the top
// The is the post process of dequeueing
void PQueue::moveDown(){
    unsigned current = 1;
    unsigned leftChild = current << 1;
    unsigned rightChild = leftChild + 1;
    unsigned greaterChild;
    // Shift down until both children are than the parent
    // If swap is required, swap with the element with the higher priority
    while (leftChild < currentArraySize){
        greaterChild = leftChild;
        if (rightChild < currentArraySize &&
            *heap[leftChild] < *heap[rightChild])
            greaterChild = rightChild;
        if(*heap[current] < *heap[greaterChild]){
            elementSwap(greaterChild, current);
            current = greaterChild;
        }else{
            return;
        }
        leftChild = current << 1;
        rightChild = leftChild + 1;
    }
}

// Destructor for the Priority Queue
PQueue::~PQueue(){
    for (unsigned i = 1; i != currentArraySize; ++i){
        delete heap[i];
    }
    delete[] heap;
}

// To print the current heap to stdout (only for debugging)
void PQueue::debugPrint(){
    std::cout << '[';
    for (unsigned i = 1; i < currentArraySize; ++i){
        std::cout << heap[i]->data;
        if (i<(currentArraySize-1)) std::cout << ',';
    }        
    std::cout << ']' << std::endl;
}

// To restamp all the elements 
void PQueue::restampElements(){
    // New container to store entryStamp sorted elements
    Element** sortedForEntryStamp = new Element*[currentArraySize-1];
    // Copy all the elements from the heap
    for (unsigned i=1; i<currentArraySize; ++i)
        sortedForEntryStamp[i-1] = heap[i];
    // Radix sort all the elements for entry stamps
    radixSortForEntryStamp(sortedForEntryStamp, currentArraySize-1);
    // Restamp all the elements in order
    for (unsigned i=0; i<(currentArraySize-1); ++i)
        sortedForEntryStamp[i]->entryStamp = i;
    delete[] sortedForEntryStamp;
}

// Radix Sort for entry stamps
// Uses binary counting sort
void PQueue::radixSortForEntryStamp(Element** array, unsigned size){
    unsigned bitCount[2];
    // New container for sorted array;
    Element** sortedArray = new Element*[size];
    unsigned numBits = 8*sizeof(unsigned);
    // Perform binary counting sort for all 32 bits (if system uses 4byte 
    //      integers), starting with the LSB
    for (unsigned i=0; i<numBits; ++i){
        bitCount[0] = 0;
        bitCount[1] = 0;
        for (unsigned j=0; j<size; ++j)
            ++bitCount[((array[j]->entryStamp)>>i)&0x1];
        bitCount[1] += bitCount[0];
        for (unsigned j=size; j>0; --j) 
            sortedArray[--bitCount[((array[j-1]->entryStamp)>>i)&0x1]] =
            array[j-1];
        for (unsigned j=0; j<size; ++j) 
            array[j] = sortedArray[j];
    }
    delete[] sortedArray;
}

