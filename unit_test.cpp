#include <iostream>
#include "PQueue.h"

int main (int argc, char * argv[]){
    PQueue test(6);
    char temp;
    test.enqueue('a', 1);
    test.enqueue('b', 2);
    test.enqueue('c', 3);
    test.enqueue('d', 4);
    test.enqueue('e', 5);
    test.enqueue('f', 6);
    test.dequeue(temp);
    std::cout << temp << std::endl;
    test.dequeue(temp);
    std::cout << temp << std::endl;
    test.dequeue(temp);
    std::cout << temp << std::endl;
    test.dequeue(temp);
    std::cout << temp << std::endl;
    test.dequeue(temp);
    std::cout << temp << std::endl;
    test.dequeue(temp);
    std::cout << temp << std::endl;
    return 0;
}

