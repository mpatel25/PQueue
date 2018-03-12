#include <cstddef>
#include <iostream>

#ifndef PQUEUE_H
#define PQUEUE_H

class PQueue{
    public:
        PQueue(unsigned size);
        unsigned enqueue (char d_in, unsigned p_in);
        char dequeue ();
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
        unsigned heapSize;
        unsigned currentArraySize;
        void moveUp();
        void moveDown();
        void elementSwap(unsigned a, unsigned b);
        void debugPrint();
};

#endif

