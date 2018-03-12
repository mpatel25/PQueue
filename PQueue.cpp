#include "PQueue.h"

PQueue::PQueue(unsigned size){
    heap = new Element*[size+1];
    heap[0] = NULL;
    heapSize = size;
    currentArraySize = 1;
    enqueueCount = 0;
}

PQueue::Element::Element(char d_in, unsigned p_in, unsigned e_in):
                data(d_in), priority(p_in), entryStamp(e_in){}

unsigned PQueue::enqueue (char d_in, unsigned p_in){
    if (currentArraySize == heapSize+1) return 1;
    heap[currentArraySize] = new Element(d_in, p_in, enqueueCount);
    currentArraySize++;
    enqueueCount++;
    moveUp();
}

char PQueue::dequeue (){
    if (currentArraySize == 1) return '\0';
    char out = heap[1]->data;
    delete heap[1];
    heap[1] = heap[currentArraySize-1];
    heap[currentArraySize-1] = NULL;
    currentArraySize--;
    moveDown();
    return out;
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
            break;
        }
        leftChild = current << 1;
        rightChild = leftChild + 1;
    }
}

PQueue::~PQueue(){
    for (int i = 1; i != currentArraySize; i++){
        delete heap[i];
    }
    delete[] heap;
}

void PQueue::debugPrint(){
    std::cout << '[';
    for (int i = 1; i != currentArraySize; i++){
        std::cout << heap[i]->data << ',';
    }        
    std::cout << ']' << std::endl;
}
