#include <iostream>
#include "pool.h"

int main() {
    std::cout << "Hello World!" << std::endl;
    threadpool::pool *myPool = (threadpool::pool *)std::malloc(sizeof(threadpool::pool));
    threadpool::task myTask;
    
    myPool->addTask(&myTask);
    return 0;
}
