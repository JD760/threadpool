#include "pool.h"

#include <iostream>
#include <thread>

int threadpool::pool::addTask() {
    return 0;
}

int threadpool::pool::shutdown() {
    std::cout << "Goodbye!\n";
    return 0;
}