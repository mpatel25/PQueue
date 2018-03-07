#include <iostream>
#include "PQueue.h"

int main (int argc, char * argv[]){
    PQueue test;
    test.enqueue('a', 1);
    test.enqueue('b', 1);
    test.enqueue('c', 1);
    test.enqueue('d', 1);
    test.enqueue('e', 1);
    test.enqueue('f', 1);
    std::cout << test.dequeue() << std::endl;
    std::cout << test.dequeue() << std::endl;
    std::cout << test.dequeue() << std::endl;
    std::cout << test.dequeue() << std::endl;
    std::cout << test.dequeue() << std::endl;
    std::cout << test.dequeue() << std::endl;
    return 0;
}

