#include <iostream>

#ifndef PQUEUE_H
#define PQUEUE_H

class PQueue{
    public:
        PQueue(unsigned size);
        bool enqueue (char d_in, unsigned p_in);
        bool dequeue (char& out);
        void debugPrint();
        ~PQueue();
    private:
        unsigned enqueueCount;
        struct Element {
            char data;
            unsigned priority;
            unsigned entryStamp;
            Element (char d_in, unsigned p_in, unsigned e_in);
            bool operator< (Element right);
        };
        Element** heap;
        unsigned maxHeapSize;
        unsigned currentArraySize;
        void moveUp();
        void moveDown();
        void elementSwap(unsigned a, unsigned b);
        unsigned heapParent(unsigned child);
        unsigned heapChildLeft(unsigned parent);
        unsigned heapChildRight(unsigned parent);
        void restampElementsAndResetEnqueueCount();
        void radixSortForEntryStamp(Element** array, unsigned size);
};

#endif

