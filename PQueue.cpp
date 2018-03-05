#include "PQueue.h"

PQueue::PQueue(){
    heap = std::vector<Element*> (1, NULL);
    enqueueCount = 0;
}

PQueue::Element::Element(char d_in, unsigned p_in, unsigned e_in):
                data(d_in), priority(p_in), entryStamp(e_in){}

void PQueue::enqueue (char d_in, unsigned p_in){
    heap.push_back(new Element(d_in, p_in, enqueueCount));
    enqueueCount++;
    moveUp();
}

char PQueue::dequeue (){
    char out = heap.back()->data;
    heap[1] = heap.back();
    delete heap.back();
    heap.pop_back();
    moveDown();
    return out;
}

void PQueue::elementSwap(unsigned a, unsigned b){
    Element * temp;
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
    unsigned current = heap.size()-1;
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
    while (leftChild < heap.size()){
        if(*heap[leftChild] < *heap[current]){
            elementSwap(leftChild, current);
            current = leftChild;
        }else if(rightChild < heap.size() &&
            *heap[rightChild] < *heap[current]){
            elementSwap(rightChild, current);
            current = rightChild;
        }else{
            break;
        }
        leftChild = current << 1;
        rightChild = leftChild + 1;
    }
}

PQueue::~PQueue(){
    for(std::vector<Element*>::iterator i = heap.begin();
        i != heap.end(); i++){
        delete *i;
    }
}

