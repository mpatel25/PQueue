#include <cstddef>
#include <vector>

#ifndef PQUEUE_H
#define PQUEUE_H

class PQueue{
    public:
        PQueue();
        void enqueue (char d_in, unsigned p_in);
        char dequeue ();
    private:
        unsigned enqueueCount;
        struct Element {
            char data;
            unsigned priority;
            unsigned entryStamp;
            Element (char d_in, unsigned p_in, unsigned e_in);
            bool operator< (Element right);
        };
        std::vector<Element*> heap;
        void moveUp();
        void moveDown();
        void elementSwap(unsigned a, unsigned b);
};

#endif

