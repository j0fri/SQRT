#include <iostream>
#include <vector>
#include "DataGenerator.h"
#include <chrono>
#include <thread>

int main(int argc, char **argv) {
    std::cout << "Hello" << std::endl;
    auto data = DataGenerator::generateData(100000);
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(1));
    std::cout << data[100];
}
