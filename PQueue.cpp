#include "PQueue.h"

PQueue::PQueue(unsigned size){
    heap = new Element*[size+1];
    heap[0] = NULL;
    maxHeapSize = size;
    currentArraySize = 1;
    enqueueCount = 0;
}

PQueue::Element::Element(char d_in, unsigned p_in, unsigned e_in):
                data(d_in), priority(p_in), entryStamp(e_in){}

bool PQueue::enqueue (char d_in, unsigned p_in){
    if (currentArraySize == (maxHeapSize+1)) return false;
    heap[currentArraySize] = new Element(d_in, p_in, enqueueCount);
    currentArraySize++;
    enqueueCount++;
    moveUp();
    if (enqueueCount == 0xFFFFFFFF) restampElements();
    return true;
}

bool PQueue::dequeue (char& out){
    if (currentArraySize == 1) return false; 
    out = heap[1]->data;
    delete heap[1];
    heap[1] = heap[currentArraySize-1];
    heap[currentArraySize-1] = NULL;
    currentArraySize--;
    moveDown();
    if (currentArraySize == 1) enqueueCount=0;
    return true;
}

void PQueue::elementSwap(unsigned a, unsigned b){
    Element* temp;
    temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

bool PQueue::Element::operator< (Element right){
    if (this->priority > right.priority) return false;
    if (this->priority == right.priority &&
        this->entryStamp <= right.entryStamp) return false;
    return true;
}

void PQueue::moveUp(){
    unsigned current = currentArraySize-1;
    unsigned parent = current >> 1;
    while(current > 1 && *heap[parent] < *heap[current]){
        elementSwap(parent, current);
        current = parent;
        parent >>= 1;
    }
}

void PQueue::moveDown(){
    unsigned current = 1;
    unsigned leftChild = current << 1;
    unsigned rightChild = leftChild + 1;
    unsigned greaterChild;
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

PQueue::~PQueue(){
    for (unsigned i = 1; i != currentArraySize; ++i){
        delete heap[i];
    }
    delete[] heap;
}

void PQueue::debugPrint(){
    std::cout << '[';
    for (unsigned i = 1; i != currentArraySize; ++i){
        std::cout << heap[i]->data << ',';
    }        
    std::cout << ']' << std::endl;
}

void PQueue::restampElements(){
    Element** sortedForEntryStamp = new Element*[currentArraySize-1];
    for (unsigned i=1; i<currentArraySize; ++i)
        sortedForEntryStamp[i-1] = heap[i];
    radixSortForEntryStamp(sortedForEntryStamp, currentArraySize-1);
    for (unsigned i=0; i<(currentArraySize-1); ++i)
        sortedForEntryStamp[i]->entryStamp = i;
}

void PQueue::radixSortForEntryStamp(Element** array, unsigned size){
    unsigned bitCount[2] = {0, 0};
    Element** sortedArray = new Element*[size];
    unsigned numBits = 8*sizeof(unsigned);
    for (unsigned i=0; i<numBits; ++i){
        for (unsigned j=0; j<size; ++j)
            ++bitCount[((array[j]->entryStamp)>>i)&0x1];
        bitCount[1] += bitCount[0];
        for (unsigned j=size; j>0; --j) 
            sortedArray[--bitCount[((array[j-1]->entryStamp)>>i)&0x1]] =
            array[j-1];
        for (unsigned j=0; j<size; ++j) 
            array[j] = sortedArray[j];
    }
}

